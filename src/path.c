#include "path.h"
#define INFINIT 100000

int find_min_distance(int *distance, int *selected, int num_vertices)
{
  int min = INFINIT;
  int vertex = -1;
  for (int k = 0; k < num_vertices; k++)
  {
    if (distance[k] <= min && selected[k] == 0)
    {
      min = distance[k];
      vertex = k;
    }
  }
  return vertex;
}

void compute_path(struct dynamic_array *path, int *previous, enum color_t color, int num_vertices)
{
  int k;
  if (color == 0)
    k = num_vertices - 1;
  else
    k = 2 * (num_vertices - 1) * (num_vertices - 1);
  while (k != -1)
  {
    add__to_dynamic_array(path, k);
    k = previous[k];
  }
}
struct dynamic_array *djikstra(struct graph_t *graph, int position, enum color_t color)
{
  int distance[graph->num_vertices];
  int previous[graph->num_vertices];
  int selected[graph->num_vertices];

  for (int k = 0; k < graph->num_vertices; k++)
  {
    distance[k] = INFINIT;
    previous[k] = INFINIT;
    selected[k] = 0;
  }

  distance[position] = 0;
  previous[position] = -1;

  for (int i = 0; i < graph->num_vertices - 1; i++)
  {
    int min_vertex = find_min_distance(distance, selected, graph->num_vertices);
    selected[min_vertex] = 1;

    int vertex = 0;
    int weight1_2 = gsl_spmatrix_get(graph->t, min_vertex, vertex) - gsl_spmatrix_get(graph->o, color, vertex);
    int d1 = distance[min_vertex];
    int d2 = distance[vertex];

    for (vertex = 0; vertex < graph->num_vertices; vertex++)
    {
      if (d2 > d1 + weight1_2 && gsl_spmatrix_get(graph->t, min_vertex, vertex) && gsl_spmatrix_get(graph->o, color, vertex) && d1 != INFINIT)
      {
        distance[vertex] = d1 + weight1_2;
        selected[vertex] = min_vertex;
      }
    }
  }
  struct dynamic_array *path = empty__dynamic_array();
  compute_path(path, previous, color, graph->num_vertices);
  return path;
}

struct graph_t *copy_new_graph(struct graph_t *graph, struct move_t move, enum color_t color)
{
  struct graph_t *new_graph = malloc(sizeof(struct graph_t));
  *new_graph = *graph;
  coloriate__graph_t(new_graph, color, move);
  return new_graph;
}
int main()
{
  int distance[4] = {10, 7, 6, 10};
  int previous[4] = {0, 0, 1, 0};
  int r = find_min_distance(distance, previous, 4);
  printf("%d \n", r);
  return 0;
}