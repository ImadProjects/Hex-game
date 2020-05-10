#include <string.h>
#include "player.h"
#include "graph_minimax.h"

struct player
{

  char *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t last_move;
};

struct player player1 = {.name = "serial_killer"};

char const *get_player_name()
{
  return player1.name;
}

struct move_t propose_opening()
{
  size_t M = (int)sqrt(player1.graph->num_vertices) - 1;
  struct move_t opening;

  do
  {
    opening.m = rand() % ((M + 1) * (M - 1)) + M + 1;
  } while (opening.m % (M + 1) == 0 || opening.m % (M + 1) == M);
  opening.c = BLACK;
  player1.last_move = opening;

  return opening;
}

int accept_opening(const struct move_t opening)
{
  size_t M = (int)sqrt(player1.graph->num_vertices) - 1;
  if (opening.m < (size_t)(M + 1) * (M + 1))
  {
    int a = rand() % 2;
    if (a == 1)
      return 1;
    else
    {
      struct move_t m = opening;
      m.c = BLACK;
      gsl_spmatrix_set(player1.graph->o, m.c, m.m, 1);
      return 0;
    }
  }
  else
    return 0;
}

void initialize_graph(struct graph_t *graph)
{
  player1.graph = graph;
}

void initialize_color(enum color_t id)
{
  player1.color = id;
  gsl_spmatrix_set(player1.graph->o, player1.last_move.c, player1.last_move.m, 1);
}

struct move_t play(struct move_t last_move)
{
  struct move_t m;
  gsl_spmatrix_set(player1.graph->o, last_move.c, last_move.m, 1);
  int M = sqrt(size__graph_t(player1.graph)) - 1;
  struct dynamic_array *player_path = djikstra(player1.graph, M, player1.color * (M + 1), player1.color);
  struct dynamic_array *enemy_path = djikstra(player1.graph, M, (1 - player1.color) * (M + 1), (1 - player1.color));
  struct dynamic_array *un = path_union(player_path, enemy_path);
  struct dynamic_array *nb = neighbours(player1.graph, last_move.m);
  struct dynamic_array *p = empty__dynamic_array();
  for (size_t i = 0; i < nb->size; i++)
  {
    add__to_dynamic_array(p, nb->array[i]);
  }
  free__dynamic_array(nb);
  struct dynamic_array *uni = path_union(un, p);
  free__dynamic_array(p);

  m = best_move(player1.graph, player1.color, M, uni);
  free__dynamic_array(player_path);
  free__dynamic_array(enemy_path);

  gsl_spmatrix_set(player1.graph->o, player1.color, m.m, 1);
  return m;
}

void finalize()
{
  free__graph_t(player1.graph);
}
