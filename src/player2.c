#include <string.h>
#include "player.h"
#define MAX_STRING 20

////////////////////// DON'T TOUCH THIS FILE /////////////////

struct player
{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
};

struct player player2 = {.name = "Nesmo"};

char const *get_player_name()
{

  return player2.name;
}

struct move_t propose_opening()
{

  struct move_t opening = {.m = 0, .c = 0};
  gsl_spmatrix *o = player2.graph->o;
  size_t vertices = size__graph_t(player2.graph);

  for (size_t i = 0; i < vertices; i++)
  {

    if ((gsl_spmatrix_get(o, 0, i) == 0) && (gsl_spmatrix_get(o, 1, i) == 0))
    {

      opening.m = i;
      break;
    }
  }

  player2.last_move = opening;

  return opening;
}

int accept_opening(const struct move_t opening)
{

  player2.last_move = opening;
  coloriate__graph_t(player2.graph, 0, player2.last_move);
  return 0;
}

void initialize_graph(struct graph_t *graph)
{

  //Copy is made by the server for this player
  player2.graph = graph;
}

void initialize_color(enum color_t id)
{
  player2.color = id;
}

struct move_t play__c(struct move_t previous_move)
{

  struct move_t next;
  int id = player2.color;
  gsl_spmatrix *o = player2.graph->o;
  size_t vertices = size__graph_t(player2.graph);
  size_t width = width__graph_t(player2.graph);

  size_t move = previous_move.m;
  size_t side = (id == 1);

  if (move >= 2 * width && (gsl_spmatrix_get(o, 0, move - width * side - (1 - side)) == 0 &&
                            gsl_spmatrix_get(o, 1, move - width * side - (1 - side)) == 0))

    next.m = move - width * side - (1 - side);

  else if (move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + width * side + (1 - side)) == 0 &&
                                           gsl_spmatrix_get(o, 1, move + width * side + (1 - side)) == 0))

    next.m = move + width * side + (1 - side);

  else if ((move - 1) % width != 0 && (gsl_spmatrix_get(o, 0, move - side - width * (1 - side)) == 0 &&
                                       gsl_spmatrix_get(o, 1, move - side - width * (1 - side)) == 0))

    next.m = move - side - width * (1 - side);

  else if ((move + 2) % width != 0 && (gsl_spmatrix_get(o, 0, move + side + width * (1 - side)) == 0 &&
                                       gsl_spmatrix_get(o, 1, move + side + width * (1 - side)) == 0))

    next.m = move + side + width * (1 - side);

  else
  {

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
  }

  next.c = player2.color;
  coloriate__graph_t(player2.graph, player2.color, next);

  return next;
}

struct move_t play__h(struct move_t previous_move)
{

  struct move_t next;
  int id = player2.color;
  gsl_spmatrix *o = player2.graph->o;
  size_t vertices = size__graph_t(player2.graph);
  size_t width = width__graph_t(player2.graph);

  size_t move = previous_move.m;
  size_t side = (id == 1);

  if (move >= 2 * width && (gsl_spmatrix_get(o, 0, move - (width)*side - (1 - side)) == 0 &&
                            gsl_spmatrix_get(o, 1, move - (width)*side - (1 - side)) == 0))

    next.m = move - (width)*side - (1 - side);

  else if (move >= 2 * width && (gsl_spmatrix_get(o, 0, move - (width - 1) * side - (1 - side)) == 0 &&
                                 gsl_spmatrix_get(o, 1, move - (width - 1) * side - (1 - side)) == 0))

    next.m = move - (width - 1) * side - (1 - side);

  else if (move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + width * side + (1 - side)) == 0 &&
                                           gsl_spmatrix_get(o, 1, move + width * side + (1 - side)) == 0))

    next.m = move + width * side + (1 - side);

  else if (move < vertices - 2 * width && (gsl_spmatrix_get(o, 0, move + (width - 1) * side + (1 - side)) == 0 &&
                                           gsl_spmatrix_get(o, 1, move + (width - 1) * side + (1 - side)) == 0))

    next.m = move + (width - 1) * side + (1 - side);

  else if ((move - 1) % width != 0 && (gsl_spmatrix_get(o, 0, move - side - width * (1 - side)) == 0 &&
                                       gsl_spmatrix_get(o, 1, move - side - width * (1 - side)) == 0))

    next.m = move - side - width * (1 - side);

  else if ((move + 2) % width != 0 && (gsl_spmatrix_get(o, 0, move + side + width * (1 - side)) == 0 &&
                                       gsl_spmatrix_get(o, 1, move + side + width * (1 - side)) == 0))

    next.m = move + side + width * (1 - side);

  else
  {

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
  }

  next.c = player2.color;
  coloriate__graph_t(player2.graph, player2.color, next);

  return next;
}

struct move_t play__t(struct move_t previous_move)
{

  struct move_t next;
  int id = player2.color;
  gsl_spmatrix *o = player2.graph->o;
  gsl_spmatrix *t = player2.graph->t;
  size_t vertices = size__graph_t(player2.graph);
  size_t width = width__graph_t(player2.graph);

  size_t move = previous_move.m;
  size_t side = (id == 1);


  
  size_t ran[vertices];
  int a = 0;

    next.c = player2.color;
  for (size_t i = 0; i < vertices && a < 1; i++)
  {

    if (gsl_spmatrix_get(t, move, i) &&
        i != move &&
        i != move + 1 &&
        i != move - 1)
    {

      ran[a] = i;
      a++;
    }
  }

  if (side)
  {

    if ((!gsl_spmatrix_get(o, 0, ran[0])) &&
        (!gsl_spmatrix_get(o, 1, ran[0])))
    {

      next.m = ran[0];
      return next;
    }

    else if ((!gsl_spmatrix_get(o, 0, move + 1)) &&
             (!gsl_spmatrix_get(o, 1, move + 1)))
    {

      next.m = move + 1;
      return next;
    }

    else if ((!gsl_spmatrix_get(o, 0, move - 1)) &&
             (!gsl_spmatrix_get(o, 1, move - 1)))
    {

      next.m = move - 1;
      return next;
    }
  }

  else
  {

    if ((!gsl_spmatrix_get(o, 0, move + 1)) &&
        (!gsl_spmatrix_get(o, 1, move + 1)))
    {

      next.m = move + 1;
      return next;
    }

    else if ((!gsl_spmatrix_get(o, 0, move - 1)) &&
             (!gsl_spmatrix_get(o, 1, move - 1)))
    {

      next.m = move - 1;
      return next;
    }

    else if ((!gsl_spmatrix_get(o, 0, ran[0])) &&
             (!gsl_spmatrix_get(o, 1, ran[0])))
    {

      next.m = ran[0];
      return next;
    }
  }

  a = 0;
  for (size_t i = 0; i < vertices; i++)
  {

    if ((gsl_spmatrix_get(o, 0, i) == 0) &&
        (gsl_spmatrix_get(o, 1, i) == 0))
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

  coloriate__graph_t(player2.graph, player2.color, next);
  return next;
}

struct move_t play(struct move_t previous_move)
{

  coloriate__graph_t(player2.graph, 1 - player2.color, previous_move);
  char c = type__graph_t(player2.graph);

  if (c == 'h')

    return play__h(previous_move);

  else if (c == 'c')

    return play__c(previous_move);

  return play__t(previous_move);
}

void finalize()
{

  free__graph_t(player2.graph);
}
