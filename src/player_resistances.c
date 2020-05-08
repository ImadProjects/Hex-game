#include "player.h"
#include "resistance.h"

int is_move_possible(struct graph_t* g, int color, struct move_t move);

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

static int init = 0;

void initialize_player_functions(struct player* player){
  player->player_propose_opening = propose_opening;
  player->player_accept_opening = accept_opening;
  player->player_initialize_graph = initialize_graph;
  player->player_initialize_color = initialize_color;
  player->player_play = play;
}

struct player jeremy = {.name ="Xx_JérémY_xX"};

struct player get_player(){  
  initialize_player_functions(&jeremy);
  jeremy.name = "Jeremy";
  return jeremy;  
}


void initialize_color(enum color_t id){
  if (!init){
    get_player(&jeremy);
    init = 1;
  }

  jeremy.color = id;

}


void initialize_graph(struct graph_t* graph){
  if (!init){
    get_player(&jeremy);
    init = 1;
  }


  jeremy.graph = graph;   
}

//struct move_t play(struct move_t previous_move){


int accept_opening(const struct move_t opening){
  if (!init){
    get_player(&jeremy);
    init = 1;
  }


  if(0){
    printf("%zu\n", opening.m);
  }
  return 1;
}

void finalize(){
  if (!init){
    get_player(&jeremy);
    init = 1;
  }


  free__graph_t(jeremy.graph);
}


struct move_t propose_opening(){//temporaire
  if (!init){
    get_player(&jeremy);
    init = 1;
  }


  struct move_t opening;
  opening.c = jeremy.color;
  opening.m = size__graph_t(jeremy.graph) / 2;
  return opening;
}

struct move_t play(struct move_t previous_move){
  if (!init){
    get_player(&jeremy);
    init = 1;
  }


  struct move_t mec;
  mec.c = jeremy.color;
  int best = -1;
  double sign = 1. - 2. * (mec.c == 1);
  double best_ratio = (double) sign * 2000000000.;
  for (int i = 0; i < (jeremy.graph)->num_vertices; i++){
    mec.m = i;
    if (is_move_possible(jeremy.graph, mec.c, mec)){
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
    mec.m = best;
    return mec;
  }
  mec.m = best;
  return mec;
}


