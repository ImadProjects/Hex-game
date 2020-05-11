#include "player.h"
#include "resistance.h"

int is_possible(struct graph_t *g, int color, struct move_t move)
{
  return (gsl_spmatrix_get(g->o, 0, (int)move.m) == 0 && gsl_spmatrix_get(g->o, 1, (int)move.m) == 0);
}

int* voisins(struct graph_t* g, int i, char type){
  if (type == 'c'){
    int* l = malloc(4 * sizeof(int));
    l[0] = i - 1;
    l[1] = i+1;
    int n = sqrt(g->num_vertices);
    l[2] = i - n;
    l[3] = i + n;
    return l;
  }
  int* l = malloc(6 * sizeof(int));
  int n = sqrt(g->num_vertices);
  l[0] = i - 1;
  l[1] = i + 1;
  l[2] = i - n;
  l[3] = i - n + 1;
  l[4] = i + n;
  l[5] = i + n - 1;
  return l;
}
  

struct player
{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
};

struct player jeremy = {.name = "Jean Moulin"};
char const *get_player_name()
{
  return jeremy.name;
}

void initialize_color(enum color_t id)
{
  jeremy.color = id;
  coloriate__graph_t(jeremy.graph, 0, jeremy.last_move);
}

void initialize_graph(struct graph_t *graph)
{
  jeremy.graph = graph;
}

//struct move_t play(struct move_t previous_move){

int accept_opening(const struct move_t opening)
{
  jeremy.last_move = opening;

  return 1;
}

void finalize()
{

  free__graph_t(jeremy.graph);
}

struct move_t propose_opening()
{ //temporaire

  struct move_t opening;
  opening.c = jeremy.color;
  opening.m = sqrt(jeremy.graph->num_vertices) + 1;
  printf("opening\n");
  return opening;
}

struct move_t play(struct move_t previous_move)
{
  char type = type__graph_t(jeremy.graph);
  if (type == 't'){
    struct move_t mec = {-1, jeremy.color};
    return mec;
  }
  
  coloriate__graph_t(jeremy.graph, jeremy.color == 0, previous_move);
  struct move_t mec;
  mec.c = jeremy.color;
  int best = -1;
  double sign = 1. - 2. * (mec.c == 1);
  double best_ratio = (double)sign * 2000000000.;
  int* voisin = voisins(jeremy.graph , previous_move.m, type);
    printf("previous: %ld\n", previous_move.m);
  
  for (int i = 0; i < 4 + 2*(type == 'h'); i++) { //cases proches
    mec.m = voisin[i];
    printf("%d -> %d\n", voisin[i], is_possible(jeremy.graph, mec.c, mec));
    if (is_possible(jeremy.graph, mec.c, mec)){
      double ratio = get_ratio(jeremy.graph, mec);
      if (!mec.c){
	if ((ratio < best_ratio) && (ratio >= 0)){
          best = voisin[i];
          best_ratio = ratio;
	  
        }
      }
      else{
        if ((ratio > best_ratio) && (ratio >= 0)){
	  best = voisin[i];
	  best_ratio = ratio;
        }
      }
    }
  }
  free(voisin);

  if (best >= 0){
    mec.m = best;
    coloriate__graph_t(jeremy.graph, jeremy.color, mec);
    printf("move: %ld\n", mec.m);
    return mec;
  }
  if (best < 0){    //autres cases
    for (int i = 0; i < jeremy.graph->num_vertices; i++) { //cases lointaines
      mec.m = i;
      if (is_possible(jeremy.graph, mec.c, mec)){
	double ratio = get_ratio(jeremy.graph, mec);
	if (!mec.c){
	  if ((ratio < best_ratio) && (ratio >= 0)){
	    coloriate__graph_t(jeremy.graph, jeremy.color, mec);
	    printf("move: %ld\n", mec.m);
	    return mec;
	  }
	}
	else{
	  if ((ratio > best_ratio) && (ratio >= 0)){
	    coloriate__graph_t(jeremy.graph, jeremy.color, mec);
	    printf("move: %ld\n", mec.m);
	    return mec;
	  }
	}
      }
    }
  }
         
  printf("=== error, jeremy can't find a proper place to play ===\n");
  mec.m = sqrt(jeremy.graph->num_vertices) + 1;
  coloriate__graph_t(jeremy.graph, jeremy.color, mec);
  printf("move: %ld\n", mec.m);
  return mec;
}
