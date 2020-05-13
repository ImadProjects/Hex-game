#include <dlfcn.h>
#include "graph.h"
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include "player.h"
#include <stdlib.h>
#include <stdio.h>

static int Length = 5;
static char Shape = 'h';
static int show = 0;

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program

void parse_opts(int argc, char *argv[])
{
  int opt;
  while ((opt = getopt(argc, argv, "m:t:p:")) != -1)
  {
    switch (opt)
    {
    case 'm':
      Length = atoi(optarg);
      break;
    case 't':
      Shape = optarg[0];
      break;
    case 'p':
      show = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-m Length] \n ",
              argv[0]);
      fprintf(stderr, "Usage: %s [-t Shape] \n ",
              argv[0]);
      fprintf(stderr, "Usage: %s [-p show] = 1 to show \n ",
              argv[0]);
    }
  }
}

int is_move_possible(struct graph_t *g, int color, struct move_t move)
{
  int n = (int)move.m;
  if (n != -1 && (gsl_spmatrix_get(g->o, color, n) == 0) && (gsl_spmatrix_get(g->o, 1 - color, n) == 0))
  {
    return 1;
  }
  return 0;
}

struct player_server
{

  char const *name;
  enum color_t color;
  char const *(*get_player_name)();
  struct move_t (*propose_opening)();
  int (*accept_opening)(const struct move_t opening);
  void (*initialize_color)(enum color_t id);
  void (*initialize_graph)(struct graph_t *graph);
  struct move_t (*play)(struct move_t previous_move);
  void (*finalize)();
};

struct player_server *compute_next_player(struct player_server *p1, struct player_server *p2, struct move_t *last_move)
{

  if (last_move->c == p2->color)
  {
    return p1;
  }
  return p2;
}

void moves_player(struct graph_t *graph, int *t, int *size, struct player_server *p)
{
  int m = graph->num_vertices;
  for (int i = 0; i < m; i++)
  {
    if ((gsl_spmatrix_get(graph->o, 1 - p->color, i) == 0 && gsl_spmatrix_get(graph->o, p->color, i) == 1) || (gsl_spmatrix_get(graph->o, 1 - p->color, i) == 0 && gsl_spmatrix_get(graph->o, p->color, i)))
    {
      t[size[0]] = i;
      size[0]++;
    }
  }
}

int main(int argc, char *argv[])
{
  printf("*********paramètres du jeu**********");
  parse_opts(argc, argv);
  printf("\nLength : %d\n", Length);
  printf("shape : %c\n", Shape);
  printf("***********************************\n");

  //-------------------------------------------
  struct graph_t *graph = new__graph_t(Length, Shape);

  void *player1 = dlopen(argv[argc - 2], RTLD_NOW);
  void *player2 = dlopen(argv[argc - 1], RTLD_NOW);

  struct player_server *p1 = malloc(sizeof(struct player_server));

  p1->get_player_name = dlsym(player1, "get_player_name");
  p1->propose_opening = dlsym(player1, "propose_opening");
  p1->accept_opening = dlsym(player1, "accept_opening");
  p1->initialize_color = dlsym(player1, "initialize_color");
  p1->initialize_graph = dlsym(player1, "initialize_graph");
  p1->play = dlsym(player1, "play");
  p1->finalize = dlsym(player1, "finalize");
  p1->initialize_graph(copy_graph(graph));

  struct player_server *p2 = malloc(sizeof(struct player_server));

  p2->get_player_name = dlsym(player2, "get_player_name");
  p2->propose_opening = dlsym(player2, "propose_opening");
  p2->accept_opening = dlsym(player2, "accept_opening");
  p2->initialize_color = dlsym(player2, "initialize_color");
  p2->initialize_graph = dlsym(player2, "initialize_graph");
  p2->play = dlsym(player2, "play");
  p2->finalize = dlsym(player2, "finalize");
  p2->initialize_graph(copy_graph(graph));
  p2->get_player_name = dlsym(player2, "get_player_name");

  struct move_t move = p1->propose_opening();
  int accept = p2->accept_opening(move);

  p1->initialize_color(1 - accept);
  p1->color = 1 - accept;
  p1->name = p1->get_player_name();

  p2->initialize_color(accept);
  p2->color = accept;
  p2->name = p2->get_player_name();

  if (!accept)
    move = p2->propose_opening();

  size_t count = width__graph_t(graph) * 4 - 4;
  struct player_server *p;
  int equal = 0;

  while (1)
  {
    srand(time(NULL));

    if ((Shape == 'c' || Shape == 't') && count == size__graph_t(graph))
    {
      equal = 1;
      break;
    }

    p = compute_next_player(p1, p2, &move);
    move = p->play(move);

    if (is_move_possible(graph, p->color, move))
    {
      if (is_winning(graph, p->color, move, Shape))
      {
        coloriate__graph_t(graph, p->color, move);
        printf("The winner is %s\n", p->name);
        break;
      }

      else
        coloriate__graph_t(graph, p->color, move);
    }

    else
    {
      printf("The winner is player %d, player %d chose a wrong move\n", 1 - p->color, p->color);
      break;
    }

    count++;

    if (show)
    {
      print_graph(graph, Shape);
      //sleep(1);
      printf("\033[%dA", Length + 3);
      printf("\033[10B"); // Move down X lines;
    }
  }

  if (show)
    print_graph(graph, Shape);
  else if (equal)
    printf("Equality between players\n");

  // draw the game on html page. Works just for m=3. Use the option -m=3 and open the html file to see the drawn game.
  // It is also possible to draw the game with option -p1. Works fine for every m.
  char ch;
  FILE *fp;
  FILE *fptr;

  fp = fopen("src/game.js", "r");   // read mode
  fptr = fopen("src/draw.js", "w"); // read mode

  if (fp == NULL || fptr == NULL)
  {
    perror("Error while opening the file.\n");
    exit(EXIT_FAILURE);
  }

  fprintf(fptr, "var p = new Object();\np.color = %d;\np.move = [", p1->color);
  int *tableau1 = malloc(sizeof(int) * Length * Length);
  int size[1];
  size[0] = 0;
  moves_player(graph, tableau1, size, p1);

  int *tableau2 = malloc(sizeof(int) * Length * Length);
  int size2[1];
  size2[0] = 0;
  printf("\n");
  moves_player(graph, tableau2, size2, p2);

  for (int k = 0; k < size[0] - 1; k++)
    fprintf(fptr, "%d,", tableau1[k]);
  fprintf(fptr, "%d];\n", tableau1[size[0] - 1]);

  fprintf(fptr, "var pl = new Object();\npl.color = %d;\npl.move = [", p2->color); //[4,1],[3,2],[3,3],[3,4],[3,5],[3,6]];\n");
  for (int k = 0; k < size2[0] - 1; k++)
    fprintf(fptr, "%d,", tableau2[k]);
  fprintf(fptr, "%d];\n", tableau2[size2[0] - 1]);
  fprintf(fptr, "var size =  %d;\n", Length); //[4,1],[3,2],[3,3],[3,4],[3,5],[3,6]];\n");
  while ((ch = fgetc(fp)) != EOF)
    fputc(ch, fptr);

  p1->finalize();
  p2->finalize();
  free__graph_t(graph);
  dlclose(player1);
  dlclose(player2);
  free(p1);
  free(p2);
  free(tableau2);
  free(tableau1);
  fclose(fp);
  dlclose(player1);
  dlclose(player2);

  return 0;
}
