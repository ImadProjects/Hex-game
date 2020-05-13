#include "../resistance.h"
#include <stdio.h>
#include <stdlib.h>
#include "../move.h"

void print_m(double **mat, int n);
void print_vect(double *v, int n);

int test_sys()
{
  int n = 2;
  int c = 0;
  struct graph_t *g = new__graph_t(n, 'c');
  double **mat = generate_meshes(g, 0);
  c += (mat[0][0] >= 1.9);
  c += (abs(mat[4][0]) < 0.6);
  c += (mat[2][0] <= 2.1);
  c += (mat[3][3] >= 1.9);
  c += (mat[3][2] <= -1 && mat[3][2] >= -2);
  c += (mat[4][4] >= 1.9);
  free_sys(mat, 5);
  free__graph_t(g);

  struct graph_t *gg = new__graph_t(n, 'h');
  double **matt = generate_meshes(gg, 0);
  free_sys(matt, 9);
  free__graph_t(gg);

  return c;
}

int test_gauss()
{
  int m = 2;
  int c = 0;
  double **mat = malloc(sizeof(double *) * m);
  mat[0] = malloc(sizeof(double) * m);
  mat[1] = malloc(sizeof(double) * m);
  double *b = malloc(sizeof(double) * m);
  b[0] = 4;
  b[1] = 3;
  mat[0][0] = 2;
  mat[0][1] = 1;
  mat[1][0] = 1;
  mat[1][1] = 1;
  double *x = malloc(sizeof(double) * m);
  gauss(mat, b, x, m);
  c += (x[0] > 0.99 && x[0] < 1.01);
  c += (x[1] > 1.99 && x[1] < 2.01);
  free(b);
  free(x);
  free_sys(mat, 2);
  return c;
}

int test_res()
{
  int n = 2;
  int c = 0;
  struct graph_t *g = new__graph_t(n, 'c');
  double *b = malloc(sizeof(double) * (n * n + 1));
  double *x = malloc(sizeof(double) * (n * n + 1));
  for (int i = 0; i < n * n + 1; i++)
  {
    x[i] = 0.;
    b[i] = 0.;
  }
  b[n * n] = 10;

  struct move_t mv = {4, 0};
  coloriate__graph_t(g, 0, mv);
  double **mat = generate_meshes(g, 1);
  gauss(mat, b, x, n * n + 1);
  double tmp = x[n * n];
  free_sys(mat, n * n + 1);

  for (int i = 0; i < n * n + 1; i++)
  {
    x[i] = 0.;
    b[i] = 0.;
  }
  b[n * n] = 10;
  double **matt = generate_meshes(g, 0);
  gauss(matt, b, x, n * n + 1);
  c += x[n * n] > tmp;
  free_sys(matt, n * n + 1);
  free(b);
  free(x);
  free__graph_t(g);

  int size = 2 * n * n;
  struct graph_t *gg = new__graph_t(n, 'h');
  double *bb = malloc(sizeof(double) * (size + 1));
  double *xx = malloc(sizeof(double) * (size + 1));
  for (int i = 0; i < size + 1; i++)
  {
    xx[i] = 0.;
    bb[i] = 0.;
  }
  bb[size] = 10;

  coloriate__graph_t(gg, 0, mv);
  double **math = generate_meshes(gg, 1);
  gauss(math, bb, xx, size + 1);
  tmp = xx[size];
  free_sys(math, size + 1);

  for (int i = 0; i < size + 1; i++)
  {
    xx[i] = 0.;
    bb[i] = 0.;
  }
  bb[size] = 10;
  double **matth = generate_meshes(gg, 0);
  gauss(matth, bb, xx, size + 1);
  c += xx[size] < tmp;
  free_sys(matth, size + 1);
  free(bb);
  free(xx);
  free__graph_t(gg);
  return c;
}

int is_move_possible(struct graph_t *g, struct move_t move)
{
  return (gsl_spmatrix_get(g->o, 0, (int)move.m) == 0 && gsl_spmatrix_get(g->o, 1, (int)move.m) == 0);
}

struct move_t play(struct move_t previous_move, struct graph_t *g)
{
  struct move_t mec;
  mec.c = (previous_move.c == 0);
  int best = -1;
  double sign = 1. - 2. * (mec.c == 1);
  double best_ratio = (double)sign * 2000000000.;
  for (int i = 0; i < (int)g->num_vertices; i++)
  {
    mec.m = i;
    if (is_move_possible(g, mec))
    {
      double ratio = get_ratio(g, mec);
      if (!mec.c)
      {
        if (ratio < best_ratio && ratio >= 0)
        {
          best = i;
          best_ratio = ratio;
        }
      }
      else
      {
        if ((ratio > best_ratio) && (ratio >= 0))
        {
          best = i;
          best_ratio = ratio;
        }
      }
    }
  }
  if (best < 0)
  {
    mec.m = best;
    return mec;
  }
  mec.m = best;
  return mec;
}

int test_joueur_resistances()
{
  int c = 0;

  int n = 2;
  struct move_t mv = {4, 0};
  struct graph_t *g = new__graph_t(n, 'c');
  coloriate__graph_t(g, 0, mv);
  struct graph_t *g_copy = copy_graph(g);
  c += ((int)play(mv, g_copy).m == -1);
  free__graph_t(g_copy);
  free__graph_t(g);

  n = 3;
  struct graph_t *gg = new__graph_t(n, 'c');
  mv.m = 6;
  coloriate__graph_t(gg, 0, mv);
  struct graph_t *gg_copy = copy_graph(gg);
  size_t tmp = play(mv, gg_copy).m;
  c += (tmp == 10);
  free__graph_t(gg_copy);
  free__graph_t(gg);

  return c;
}
