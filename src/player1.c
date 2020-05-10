#include <string.h>
#include "player.h"
#define MAX_STRING 20

///////////////////// DONT TOUCH THIS FILE //////////////

struct player
{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
};

struct player player1 = {.name = "Random"};

char const *get_player_name()
{

  return player1.name;
}

struct move_t propose_opening()
{

  struct move_t opening = {.m = 0, .c = 0};
  gsl_spmatrix *o = player1.graph->o;
  size_t vertices = size__graph_t(player1.graph);

  for (size_t i = 0; i < vertices; i++)
  {

    if ((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0))
    {

      opening.m = i;
      break;
    }
  }

  player1.last_move = opening;

  return opening;
}

int accept_opening(const struct move_t opening)
{

  player1.last_move = opening;
  return 0;
}

void initialize_graph(struct graph_t *graph)
{

  //Copy is made by the server for this player
  player1.graph = graph;
}

void initialize_color(enum color_t id)
{

  player1.color = id;
  coloriate__graph_t(player1.graph, 0, player1.last_move);
}

struct move_t play(struct move_t previous_move)
{

  coloriate__graph_t(player1.graph, 1 - player1.color, previous_move);
  struct move_t next;
  int id = player1.color;
  gsl_spmatrix *o = player1.graph->o;
  size_t vertices = size__graph_t(player1.graph);
  size_t width = width__graph_t(player1.graph);
  size_t ran[vertices];
  int a = 0;

  for (size_t i = 0; i < vertices; i++)
  {

    if ((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0))
    {

      ran[a] = i;
      a++;
    }
  }

  if (a == 0)

    next.m = -1;

  else
  {

    int r = rand() % a;
    next.m = ran[r];
  }

  next.c = id;
  coloriate__graph_t(player1.graph, player1.color, next);

  return next;
}

void finalize()
{

  free__graph_t(player1.graph);
}
