#include <gsl/gsl_spmatrix.h>
#include <stddef.h>
#include "graph.h"

void assign_links(gsl_spmatrix* t, char c, int n){
  for (int i = 0; i < n*n; i++){
    for (int j = 0; j < n*n; j++){
      int N = i*n + j;
      if (i > 0){
	gsl_spmatrix_set(t, N, N-n, 1);
      }
      if (i < n*n - 1){
	gsl_spmatrix_set(t, N, N+n, 1);
      }
      if (j > 0){
	gsl_spmatrix_set(t, N, N-1, 1);
      }
      if (i < n*n - 1){
	gsl_spmatrix_set(t, N, N+1, 1);
      }
    }
  } 
}
    
/*ne fait que des graphes carrés pour l'instant*/
struct graph_t* new__graph_t(int n, char c){
struct graph_t* g = malloc(sizeof(struct graph_t));
g->num_vertices = n * n;
g->t = gsl_spmatrix_alloc(n*n, n*n);
g->o = gsl_spmatrix_alloc(2, n*n);
assign_links(g->t, c, n);
return g;
}

void free__graph_t(struct graph_t* g){
gsl_spmatrix_free(g->o);
gsl_spmatrix_free(g->t);
free(g);
}
    
void print__mat(struct graph_t* g){
int n = g->num_vertices;
for (int i = 0; i < n; i++){
printf("(");
for (int j = 0; j < n; j++){
printf("%d ", (int) gsl_spmatrix_get(g->t, i, j));
}
printf(")\n");
}
}
