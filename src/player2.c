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

struct player player2 = {.name = "-player2-"};


void initialize_player_functions(struct player* player){
  
  player->player_propose_opening = propose_opening;
  player->player_accept_opening = accept_opening;
  player->player_initialize_graph = initialize_graph;
  player->player_initialize_color = initialize_color;
  player->player_play = play;
  
}




struct player get_player(){
  
  initialize_player_functions(&player2);
  player2.name = "player2";
  
  return player2;
  
}

char const* get_player_name(){
  
  return player2.name;
  
}


struct move_t propose_opening(){
  
    size_t vertices = size__graph_t(player2.graph);
    size_t width =  width__graph_t(player2.graph);
    gsl_spmatrix *o = player2.graph->o;
    size_t mv = rand()%(vertices - 2*width) + width;
    
    size_t ran[vertices];
    int a = 0;
  
    for(size_t i = width - 1; i <= vertices - width; i++){
      
      if((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0)){
	
	ran[a] = i;
	a++;
      }
      
    }

    struct move_t opening = {.c = player2.color };

    if(a == 0)

      opening.m = -1;

    else{
      
      int r = rand()%a;
      opening.m = ran[r];
    }
    
    
    return opening;
    
}



int accept_opening(const struct move_t opening){
  
    (void)opening;
    return 1;
    
}

void initialize_graph(struct graph_t* graph){
  
    //Copy is made by the server for this player
    player2.graph = graph;
    
}

void initialize_color(enum color_t id){
  
    player2.color = id;
}

struct move_t play__c(struct move_t previous_move){

  
  struct move_t next;
  int id = player2.color;
  gsl_spmatrix *o = player2.graph->o;
  size_t vertices = size__graph_t(player2.graph);
  size_t width = width__graph_t(player2.graph);
  
  size_t move = previous_move.m;
  size_t side = (id == 1) ;
  
  if(move >= 2 * width && (gsl_spmatrix_get(o, 0, move - width * side - (1 - side)) == 0 &&
			   gsl_spmatrix_get(o, 1, move - width * side - (1 - side)) == 0))
    
    next.m = move - width * side - (1 - side) ;

  else if(move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + width * side + (1 - side)) == 0 &&
					  gsl_spmatrix_get(o, 1, move + width * side + (1 - side)) == 0))

    next.m = move + width * side + (1 - side);

  else if((move - 1) % width != 0 && (gsl_spmatrix_get(o, 0, move - side - width * (1 - side)) == 0 &&
				      gsl_spmatrix_get(o, 1, move - side - width * (1 - side)) == 0))

    next.m = move - side - width * (1 - side);

  else if((move + 2) % width != 0 && (gsl_spmatrix_get(o, 0, move + side + width * (1 - side)) == 0 &&
				      gsl_spmatrix_get(o, 1, move + side + width * (1 - side)) == 0))

    next.m = move + side + width * (1 - side);

  else{

    size_t ran[vertices];
    int a = 0;
    
    for(size_t i = 0; i< vertices; i++){
      
      if((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0)){
	
	ran[a] = i;
	a++;}
      
    }
    
    if(a == 0)
      
      next.m = -1;
    
    else{
      
      int r = rand()%a;
      next.m = ran[r];
      
    }
  
  }

  next.c = player2.color;

  return next;

}


struct move_t play__h(struct move_t previous_move){

  
  struct move_t next;
  int id = player2.color;
  gsl_spmatrix *o = player2.graph->o;
  size_t vertices = size__graph_t(player2.graph);
  size_t width = width__graph_t(player2.graph);
  
  size_t move = previous_move.m;
  size_t side = (id == 1) ;

  
  if(move >= 2 * width && (gsl_spmatrix_get(o, 0, move - (width - 1) * side - (1 - side)) == 0 &&
			   gsl_spmatrix_get(o, 1, move - (width - 1)* side - (1 - side)) == 0))

    next.m = move - (width - 1) * side - (1 - side);
  
  else if(move >= 2 * width && (gsl_spmatrix_get(o, 0, move - width * side - (1 - side)) == 0 &&
			   gsl_spmatrix_get(o, 1, move - width * side - (1 - side)) == 0))
    
    next.m = move - width * side - (1 - side) ;

  else if(move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + width * side + (1 - side)) == 0 &&
					  gsl_spmatrix_get(o, 1, move + width * side + (1 - side)) == 0))

    next.m = move + width * side + (1 - side);

  else if(move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + (width - 1) * side + (1 - side)) == 0 &&
					  gsl_spmatrix_get(o, 1, move + (width - 1) * side + (1 - side)) == 0))

    next.m = move + (width - 1) * side + (1 - side);

  
  else if((move - 1) % width != 0 && (gsl_spmatrix_get(o, 0, move - side - width * (1 - side)) == 0 &&
				      gsl_spmatrix_get(o, 1, move - side - width * (1 - side)) == 0))

    next.m = move - side - width * (1 - side);

  else if((move + 2) % width != 0 && (gsl_spmatrix_get(o, 0, move + side + width * (1 - side)) == 0 &&
				      gsl_spmatrix_get(o, 1, move + side + width * (1 - side)) == 0))

    next.m = move + side + width * (1 - side);

  else{

    size_t ran[vertices];
    int a = 0;
    
    for(size_t i = 0; i< vertices; i++){
      
      if((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0)){
	
	ran[a] = i;
	a++;}
      
    }
    
    if(a == 0)
      
      next.m = -1;
    
    else{
      
      int r = rand()%a;
      next.m = ran[r];
      
    }
  
      

  }

  next.c = player2.color;

  return next;

}


struct move_t play(struct move_t previous_move){

  char c = type__graph_t(player2.graph);

  if(c == 'h')

    return play__h(previous_move);

  return play__c(previous_move);

}


void finalize(){
  
  free__graph_t(player2.graph);
  
}
