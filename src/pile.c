#include "pile.h"
#include <stdlib.h>

struct pile* pile_vide(int n){
  struct pile* p = malloc(sizeof(struct pile));
  int* tab = malloc(sizeof(int) * (n + 1));
  p->t = tab;
  p->size = 0;
  return p;
}
  
void pile_free(struct pile* p){
  free(p->t);
  free(p);
}

void empiler(struct pile* p, int n){
  p->t[p->size] = n;
  p->size++;
}    
  
int depiler(struct pile* p){
  if (p->size == 0){
    return -1;
  }
  p->size--;
  int res = p->t[p->size];
  return res;
}

int est_vide(struct pile* p){
  return p->size == 0;
}



//////////////////////////////// graph part //////////////////////////

size_t size__graph_t(struct graph_t *graph){

  return graph->num_vertices;

}


size_t width__graph_t(struct graph_t *graph){
  
  size_t n = size__graph_t(graph);
  float m = sqrt(n);
  
  if (m == (float)floor(m))

    return m;

  return sqrt(n/6);

}


char type__graph_t(struct graph_t *graph){

  int n = size__graph_t(graph);
  int d = width__graph_t(graph);
  int m = floor(n / 2);
  printf("n = %d\n", n);
  printf("d = %d\n", d);
  printf("m = %d\n", m);
  if(gsl_spmatrix_get(graph->t, m, m + 1) && gsl_spmatrix_get(graph->t, m, m - 1) && gsl_spmatrix_get(graph->t, m, m + d) && gsl_spmatrix_get(graph->t, m, m - d))

     return 'c';

  else if(gsl_spmatrix_get(graph->t, m, m + 1) &&
	  gsl_spmatrix_get(graph->t, m, m - 1)
	  && (gsl_spmatrix_get(graph->t, m, m + d) + gsl_spmatrix_get(graph->t, m, m - d) == 1))

    return 't';

  return 'h';

}
