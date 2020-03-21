
#include <dlfcn.h>
#include "graph.h"



struct player{
  char const *name;
  struct move_t move;
  enum color_t color;
  struct move_t (*player_propose_opening)();
  int (*player_accept_opening)(const struct move_t opening);
  void (*player_initialize_color)(enum color_t id);
  void (*player_initialize_graph)(struct graph_t* graph);
  struct move_t (*player_play)(struct move_t previous_move);
};

int main()
{
  void * player1 = dlopen("install/player1.so",RTLD_NOW);
  char const* (*f)() = dlsym(player1,"get_player_name");
  struct player (*f1)() = dlsym(player1,"get_player");
  struct player p1 = f1();
  printf("%s\n",p1.name);
  dlclose(player1);
  return 0;
}
