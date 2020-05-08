#include "path.h"
#define INFINIT 100000

struct path *empty__path()
{

  struct path *p = malloc(sizeof(struct path));
  p->array = malloc(sizeof(size_t));
  p->capacity = 1;
  p->size = 0;

  return p;
}

void realloc__path(struct path *p)
{

  if (p->capacity == 0)
  {
    p->array = malloc(2 * sizeof(size_t));
    p->capacity = 2;
  }

  else if (p->capacity == p->size)
  {
    p->array = realloc(p->array, 2 * p->capacity * sizeof(size_t));
    p->capacity = 2 * p->capacity;
  }
}

void add__to_path(struct path *p, size_t n)
{

  realloc__path(p);
  p->array[p->size] = n;
  p->size++;
}

void free__path(struct path *p)
{

  free(p->array);
  free(p);
}

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

void compute_path(struct path *path, int *previous, enum color_t color, int num_vertices)
{
  int k;
  if (color == 0)
    k = num_vertices - 1;
  else
    k = 2 * (num_vertices - 1) * (num_vertices - 1);
  while (k != -1)
  {
    add__to_path(path, k);
    k = previous[k];
  }
}
struct path *djikstra(struct graph_t *graph, int position, enum color_t color)
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
  struct path *path = empty__path();
  compute_path(path, previous, color, graph->num_vertices);
  return path;
}

int main()
{
  int distance[4] = {10, 7, 6, 10};
  int previous[4] = {0, 0, 1, 0};
  int r = find_min_distance(distance, previous, 4);
  printf("%d \n", r);
  return 0;
}