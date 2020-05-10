#include "pile.h"
#include <stdlib.h>

#define N_INIT 10

void inc(struct pile *p);

struct pile *pile_vide()
{
  struct pile *p = malloc(sizeof(struct pile));
  int *tab = malloc(sizeof(int) * (N_INIT));
  p->t = tab;
  p->size = 0;
  p->capacity = N_INIT;
  return p;
}

void pile_free(struct pile *p)
{
  free(p->t);
  free(p);
}

void empiler(struct pile *p, int n)
{
  if (p->capacity == p->size)
  {
    inc(p);
  }
  p->t[p->size] = n;
  p->size++;
}

int depiler(struct pile *p)
{
  if (p->size == 0)
  {
    return -1;
  }
  p->size--;
  int res = p->t[p->size];
  return res;
}

int est_vide(struct pile *p)
{
  return p->size == 0;
}

void inc(struct pile *p)
{
  p->capacity = p->capacity * 2 + 1;
  p->t = realloc(p->t, sizeof(int) * p->capacity * 2);
}

//////////////////////////////// graph part //////////////////////////

size_t size__graph_t(const struct graph_t *graph)
{

  return graph->num_vertices;
}

size_t width__graph_t(const struct graph_t *graph)
{

  size_t n = size__graph_t(graph);
  float m = sqrt(n);

  if (m == (float)floor(m))

    return m;

  return sqrt(n / 6);
}

char type__graph_t(const struct graph_t *graph)
{

  int d = width__graph_t(graph);
  int m = floor((d * 2) - (d / 2)) - 1;

  if (gsl_spmatrix_get(graph->t, m, m + 1) &&
      gsl_spmatrix_get(graph->t, m, m - 1) &&
      gsl_spmatrix_get(graph->t, m, m - d) &&
      gsl_spmatrix_get(graph->t, m, m + d) &&
      gsl_spmatrix_get(graph->t, m, m - d + 1) &&
      gsl_spmatrix_get(graph->t, m, m + d - 1))

    return 'h';

  else if (gsl_spmatrix_get(graph->t, m, m + 1) && gsl_spmatrix_get(graph->t, m, m - 1) && gsl_spmatrix_get(graph->t, m, m + d) && gsl_spmatrix_get(graph->t, m, m - d))

    return 'c';

  return 't';
}
