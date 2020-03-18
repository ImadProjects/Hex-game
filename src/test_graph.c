#include <stdio.h>
#include <gsl/gsl_spmatrix.h>
#include "graph.h"

#define N_GRAPH 8

int check(int n,int att){
  return n == att;
}

int test_graph(void){
  int c = 0;
  struct graph_t* g = new__graph_t(2, 'h');//graphe hexa
  c += check(g->num_vertices, 4);
  c += check(gsl_spmatrix_get(g->t, 0, 0), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 0), 1);
  c += check(gsl_spmatrix_get(g->t, 0, 1), 1);
  c += check(gsl_spmatrix_get(g->t, 1, 1), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 3), 1);
  c += check(gsl_spmatrix_get(g->t, 3, 1), 1);
  c += check(gsl_spmatrix_get(g->o, 0, 2), 0);
  coloriate__graph_t(g, 0, 6);
  c += check(gsl_spmatrix_get(g->o, 0, 2), 1);
  print__mat(g);
  printf("%d\n", g->num_vertices);
  free__graph_t(g);
  return c;
}
    
void recap_test(char* s, int n, int expected){
  if (n == expected){
    printf("\033[0;32m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n",s, n , expected);
    printf("\033[0m");
  }
  else{
    printf("\033[0;31m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n",s, n , expected);
    printf("\033[0m");
  }
}

int main(void){
  int n = test_graph();
  recap_test("LE GRAPHE", n, N_GRAPH);
  return 0;
}
    
