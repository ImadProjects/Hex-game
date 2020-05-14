#include "path.h"
#define INFINIT 100000

int find_min_distance(int *distance, int *selected, int num_vertices)
{
  int min = INFINIT;
  int min_index = -1;

  for (int k = 0; k < num_vertices; k++)
    if (distance[k] <= min && selected[k] == 0)
      min = distance[k], min_index = k;

  return min_index;
}

struct dynamic_array *path_intesection(struct dynamic_array *p1, struct dynamic_array *p2)
{
  struct dynamic_array *inter = empty__dynamic_array();

  for (size_t i = 0; i < p1->size; i++)
    for (size_t j = 0; j < p2->size; j++)
      if (p1->array[i] == p2->array[j])
        add__to_dynamic_array(inter, p1->array[i]);

  return inter;
}

struct dynamic_array *path_union(struct dynamic_array *p1, struct dynamic_array *p2)
{
  struct dynamic_array *unio = empty__dynamic_array();

  for (size_t i = 0; i < p1->size; i++)
    add__to_dynamic_array(unio, p1->array[i]);

  for (size_t i = 0; i < p2->size; i++)
    add__to_dynamic_array(unio, p2->array[i]);

  return unio;
}
struct dynamic_array *djikstra(struct graph_t *G, size_t M, int src, enum color_t color)
{
  size_t vertices = G->num_vertices;
  int distance[vertices];
  int parent[vertices];
  int selected[vertices];

  for (size_t i = 0; i < vertices; i++)
    parent[i] = INFINIT, distance[i] = INFINIT, selected[i] = 0;

  distance[src] = 0;
  parent[src] = -1;

  for (int count = 0; count < (int)(G->num_vertices - 1); count++)
  {
    int u = find_min_distance(distance, selected, G->num_vertices);
    selected[u] = 1;

    for (size_t v = 0; v < G->num_vertices; v++)
    {
      int d = (int)(gsl_spmatrix_get(G->t, u, v) - gsl_spmatrix_get(G->o, color, v) * gsl_spmatrix_get(G->o, color, u));
      if (!selected[v] &&
          gsl_spmatrix_get(G->t, u, v) &&
          distance[u] != INFINIT &&
          !gsl_spmatrix_get(G->o, (color + 1) % 2, v) &&
          distance[u] + d <= distance[v])
      {
        distance[v] = distance[u] + d;
        parent[v] = u;
      }
    }
  }

  struct dynamic_array *p = empty__dynamic_array();
  int i;
  if (color == BLACK)
  {
    int i = G->num_vertices - 1;
    while (i != -1)
    {
      if (distance[i] == INFINIT)
        break;
      add__to_dynamic_array(p, i);
      i = parent[i];
    }
  }
  else
  {
    int i = 2 * M + 1;
    while (i != -1)
    {
      if (distance[i] == INFINIT)
        break;
      add__to_dynamic_array(p, i);
      i = parent[i];
    }
  }
  return p;
}
int path_score(struct dynamic_array *path, struct graph_t *G)
{
  size_t score = 0, i = 0;

  for (i = 0; i < path->size; i++)
    if ((gsl_spmatrix_get(G->o, 0, path->array[i]) == 0) && ((gsl_spmatrix_get(G->o, 1, path->array[i]) == 0)))
      score++;

  return score;
}

int path_quality(struct graph_t *G, int M, int color)
{
  if (game_over(G, color))
    return -INFINIT;

  if (game_over(G, (color + 1) % 2))
    return INFINIT;

  struct dynamic_array *p_path = djikstra(G, M, color * (M + 1), color);
  struct dynamic_array *op_path = djikstra(G, M, (color + 1) % 2 * (M + 1), (color + 1) % 2);

  int d = path_score(p_path, G) - path_score(op_path, G);
  free__dynamic_array(p_path);
  free__dynamic_array(op_path);

  return d;
}
