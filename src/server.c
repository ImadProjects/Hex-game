#include <dlfcn.h>
#include "graph.h"
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include "player.h"
#include <stdlib.h>
#include <stdio.h>

// Global seed for the random number generator
static int Length = 6;
static char Shape = 'h';
static int show = 0;

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "m:t:p:")) != -1) {
    switch (opt) {
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

int is_move_possible(struct graph_t* g, int color, struct move_t move){
  int n = (int) move.m;
  if (move.m != -1 && (gsl_spmatrix_get(g->o, 0, n) == 0) && (gsl_spmatrix_get(g->o, 1, n) == 0)){
    return 1;
  }
  return 0;
}


struct player{
  
  char const *name;
  struct graph_t *graph;
  enum color_t color;
  char const* (*get_player_name)();
  struct move_t (*propose_opening)();
  int (*accept_opening)(const struct move_t opening);
  void (*initialize_color)(enum color_t id);
  void (*initialize_graph)(struct graph_t* graph);
  struct move_t (*play)(struct move_t previous_move);
  void (*finalize)();
  
};


struct player * compute_next_player(struct player *p1, struct player *p2, struct move_t *last_move)
{
  
  if(last_move->c == 0){
    return p2;
  }
  return p1;
  
}


int main(int argc,  char* argv[]){
  
    //printf("*********paramètres du jeu**********");
 parse_opts(argc, argv);
  //printf("\nLength : %d\n", Length);
  //printf("shape : %d\n", Shape);
//-------------------------------------------
  struct graph_t *graph = new__graph_t(Length, Shape); 
  char *v = argv[argc-2];
  void * player1 = dlopen(argv[argc-2],RTLD_NOW);
  void * player2 = dlopen(argv[argc-1],RTLD_NOW);
  
  struct player * p1 =malloc(sizeof(struct player));

  p1->get_player_name = dlsym(player1,"get_player_name");
  p1->propose_opening = dlsym(player1,"propose_opening");
  p1->accept_opening = dlsym(player1,"accept_opening");
  p1->initialize_color = dlsym(player1,"initialize_color");
  p1->initialize_graph = dlsym(player1,"initialize_graph");
  p1->play = dlsym(player1,"play");
  p1->finalize = dlsym(player1,"finalize");
  p1->initialize_graph(graph);

  struct player * p2 =malloc(sizeof(struct player));

  p2->get_player_name = dlsym(player2,"get_player_name");
  p2->propose_opening = dlsym(player2,"propose_opening");
  p2->accept_opening = dlsym(player2,"accept_opening");
  p2->initialize_color = dlsym(player2,"initialize_color");
  p2->initialize_graph = dlsym(player2,"initialize_graph");
  p2->play = dlsym(player2,"play");
  p2->finalize = dlsym(player2,"finalize");
  p2->initialize_graph(graph);
    p2->get_player_name = dlsym(player2,"get_player_name");


  struct move_t move = p1->propose_opening();

  p1->initialize_color(1 - p2->accept_opening(move));
  p1->color = 1 - p2->accept_opening(move);
  p1->name = p1->get_player_name();
  p2->initialize_color(p2->accept_opening(move));
    p2->color = p2->accept_opening(move);
  p2->name = p2->get_player_name();


  int count = width__graph_t(graph) * 4 - 4;

  struct move_t last_move = {.c = 1 - p1->color, .m = move.m};
  struct player *p;
  int winner = 0;
  int equal = 0;
  int tab_moves_player1[10] = {22,10,11,18,13,26};
  int tab_moves_player2[10] = {19,10,11,25,21,14};


  while (1){
    
   if (show){
     
     //print_graph(graph, Shape);
    //sleep(1);
    printf("\033[%dA",Length+3);
     printf("\033[10B"); // Move down X lines;
  }
   
    srand(time(NULL));

    if((Shape == 'c' || Shape == 't') && count == size__graph_t(graph)){
      equal = 1;
      break;
      
    }

    
    p = compute_next_player(p1, p2, &last_move);
    move = p->play(move);

    printf("Turn : player %s plays the box %ld\n", p->name, move.m);

    if(is_move_possible(graph, p->color, move)){
      
      if (is_winning(graph, p->color, move, Shape)){

  coloriate__graph_t(graph, p->color, move);
  winner=1;
  printf("The winner is %s\n", p->name);
        
  break;}

      else

      coloriate__graph_t(graph, p->color, move);
      
      //print_graph(graph, Shape);
      
    }
    
    else{
    
      printf("The winner is player %d, player %d chose a wrong move\n", 1 - p->color, p->color);
      break;
    }
    
    last_move = move;
    count++;

    
  }

  //print_graph(graph, Shape);  
  /*if (winner)
  printf("The winner is");
  else
    if (equal)
      printf("Equality between players\n");

  */

   free__graph_t(graph);
   dlclose(player1);
   dlclose(player2);
   free(p1);
   free(p2);

   return 0;
}
