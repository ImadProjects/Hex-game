#include <gsl/gsl_spmatrix.h>
#include <stddef.h>
#include "graph.h"

void assign_links(gsl_spmatrix* t, char c, int n){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      int N = i*n + j;
      if (i > 0){
	gsl_spmatrix_set(t, N, N-n, 1);//carré, hex
      }
      if (i < n*n - 1){
	gsl_spmatrix_set(t, N, N+n, 1);//carré, hex
      }
      if (j > 0){
	gsl_spmatrix_set(t, N, N-1, 1);//carré, hex
      }
      if (j < n - 1){
	gsl_spmatrix_set(t, N, N+1, 1);//carré, hex      
      }
      if (i < n - 1 && c == 'h' && j > 0){
	gsl_spmatrix_set(t, N, N + n - 1, 1);//hex
      }
      if (i > 0 && c == 'h' && j < n-1){
	gsl_spmatrix_set(t, N, N - n + 1, 1);//hex
      }
    }
  } 
}
    
/*ne fait que des graphes carrés pour l'instant*/
struct graph_t* new__graph_t(int n, char c){
  struct graph_t* g = malloc(sizeof(struct graph_t));
  g->num_vertices = n * n * (1 + 5 * (c == 't'));//n² sauf si triangulaire auquel cas on a 6n²
  g->t = gsl_spmatrix_alloc(g->num_vertices, g->num_vertices);
  g->o = gsl_spmatrix_alloc(2, g->num_vertices);
  assign_links(g->t, c, n);
  return g;
}

void free__graph_t(struct graph_t* g){
  gsl_spmatrix_free(g->o);
  gsl_spmatrix_free(g->t);
  free(g);
}
    
void print__mat(const struct graph_t* g){
  int n = g->num_vertices;
  for (int i = 0; i < n; i++){
    printf("(");
    for (int j = 0; j < n; j++){
      int s = (int) gsl_spmatrix_get(g->t, i, j);
	if (s != 0){
	  printf("\033[0;33m");
	}
      printf("%d ", s);
      printf("\033[0m");
    }
    printf(")\n");
  }
}

void coloriate__graph_t(struct graph_t* g, int color, int n){
  gsl_spmatrix_set(g->o, color, n, 1);
}
