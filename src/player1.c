#include <string.h>
#include "player.h"
#define MAX_STRING 20

struct player{
  
  char* name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t (*player_propose_opening)();
  int (*player_accept_opening)(const struct move_t opening);
  void (*player_initialize_color)(enum color_t id);
  void (*player_initialize_graph)(struct graph_t* graph);
  struct move_t (*player_play)(struct move_t previous_move);
  void (*finalize)();
  
};

struct player player1;


void initialize_player_functions(struct player* player){
  
  player->player_propose_opening = propose_opening;
  player->player_accept_opening = accept_opening;
  player->player_initialize_graph = initialize_graph;
  player->player_initialize_color = initialize_color;
  player->player_play = play;
  
}




struct player get_player(){
  
  initialize_player_functions(&player1);
  player1.name = "player1";
  
  return player1;
  
}

char const* get_player_name(){
  
  return player1.name;
  
}


struct move_t propose_opening(){
  
    size_t vertices = size__graph_t(player1.graph);
    size_t width =  width__graph_t(player1.graph);
    gsl_spmatrix *o = player1.graph->o;
    size_t mv = rand()%(vertices - 2*width) + width;
    
    while((gsl_spmatrix_get(o, 0, mv) == 1) || (gsl_spmatrix_get(o, 1, mv) == 1))
      
	mv = rand()%(vertices - 2*width) + width;
     
    struct move_t opening = {mv};
    
    return opening;
    
}


int accept_opening(const struct move_t opening){
  
    (void)opening;
    return 1;
    
}

void initialize_graph(struct graph_t* graph){
  
    //Copy is made by the server for this player
    player1.graph = graph;
    
}

void initialize_color(enum color_t id){
  
    player1.color = id;
}

struct move_t play(struct move_t previous_move)
{
  struct move_t next;
  int id = player1.color;
  gsl_spmatrix *o = player1.graph->o;
  size_t vertices = size__graph_t(player1.graph);
  size_t width = width__graph_t(player1.graph);
  size_t move = rand()%(vertices - 2*width) + width;
  
  while((gsl_spmatrix_get(o, 0, move) == 1) || (gsl_spmatrix_get(o, 1, move) == 1))
	
    move = rand()%(vertices - 2*width) + width;
    

  next.m = move;
  next.c = id;
  return next;
  
}

void finalize(){
  
  free__graph_t(player1.graph);
  
}
