#include <string.h>
#include "player.h"
#include "graph_minimax.h"
#define MAX_STRING 20


struct player{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
  
};

struct player killer = {.name = "Killer"};

char const *get_player_name(){

  return killer.name;
}

struct move_t propose_opening(){

  struct move_t opening = {.m = 0, .c = 0};
  gsl_spmatrix *o = killer.graph->o;
  size_t vertices = size__graph_t(killer.graph);
  
  for(size_t i = 0; i < vertices; i++){

    if((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0)){
      
      opening.m = i;
      break;
    }
  }

  killer.last_move = opening;
  
  return opening;
}

int accept_opening(const struct move_t opening){

  killer.last_move = opening;
  return 0;
}


void initialize_graph(struct graph_t *graph){

  //Copy is made by the server for this player
  killer.graph = graph;
}

void initialize_color(enum color_t id){

  killer.color = id;
  coloriate__graph_t(killer.graph, 0, killer.last_move);
  
}

struct move_t play(struct move_t previous_move){

  coloriate__graph_t(killer.graph, 1 - killer.color, previous_move);

  struct dynamic_array *possible_moves = get__possible_moves(killer.graph);
  int n = possible_moves->size;
  int values[n];

  for(int i = 0; i < n; i++)
    values[i] = minimax(killer.graph, possible_moves->array[i], 1, 4, -INFINIT, INFINIT, killer.color);

  struct move_t next ={.c = killer.color, .m =  best_move(possible_moves, values)};
  free__dynamic_array(possible_moves);
		       
  coloriate__graph_t(killer.graph, killer.color, next);
  
  return next;
}

void finalize(){

  free__graph_t(killer.graph);
}
