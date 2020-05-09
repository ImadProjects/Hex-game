#include "player.h"
#include "resistance.h"

int is_possible(struct graph_t* g, int color, struct move_t move){
  return (gsl_spmatrix_get(g->o, 0, (int) move.m) == 0 && gsl_spmatrix_get(g->o, 1, (int) move.m) == 0);
}

struct player{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
  
};

struct player jeremy = {.name ="Jérémy"};
char const *get_player_name(){
  return jeremy.name;
}

void initialize_color(enum color_t id){
  jeremy.color = id;
  coloriate__graph_t(jeremy.graph, 0, jeremy.last_move);
}


void initialize_graph(struct graph_t* graph){
  jeremy.graph = graph;   
}

//struct move_t play(struct move_t previous_move){


int accept_opening(const struct move_t opening){
    jeremy.last_move = opening;

  return 1;
}

void finalize(){

  free__graph_t(jeremy.graph);
}


struct move_t propose_opening(){//temporaire

  struct move_t opening;
  opening.c = jeremy.color;
  opening.m = 6; // sqrt(jeremy.graph->num_vertices) + 2;
  return opening;
}

struct move_t play(struct move_t previous_move){
  coloriate__graph_t(jeremy.graph, jeremy.color == 0, previous_move);
  struct move_t mec;
  mec.c = jeremy.color;
  int best = -1;
  double sign = 1. - 2. * (mec.c == 1);
  double best_ratio = (double) sign * 2000000000.;
  for (int i = 0; i < (jeremy.graph)->num_vertices; i++){
    mec.m = i;
    if (is_possible(jeremy.graph, mec.c, mec)){
      double ratio = get_ratio(jeremy.graph, mec);
      if (!mec.c){
	if ((ratio < best_ratio) && (ratio >= 0)){
	  best = i;
	  best_ratio = ratio;
	}
      }
      else
	{
	  if ((ratio > best_ratio) && (ratio >= 0)){
	    best = i;
	    best_ratio = ratio;
	  }	  
	}
    }
  }
  if (best < 0){
    printf("=== error, jeremy can't find a proper place to play ===\n");
    mec.m = sqrt(jeremy.graph->num_vertices) + 1;
    return mec;
  }
  mec.m = best;
  coloriate__graph_t(jeremy.graph, jeremy.color, mec);
  return mec;
}


