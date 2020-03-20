#include <stdio.h>
#include <gsl/gsl_spmatrix.h>
#include "graph.h"
#include "pile.h"

#define N_GRAPH 9
#define N_PILE 7

int check(int n,int att){
  return n == att;
}

int test_graph(void){
  int c = 0;
  struct graph_t* g = new__graph_t(3, 'c');//graphe triangulaire
  //en vrai j'ai vérifié toutes les matrices a la main a coté pour etre sur
  c += check(g->num_vertices, 16);
  c += check(gsl_spmatrix_get(g->t, 0, 0), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 0), 1);
  c += check(gsl_spmatrix_get(g->t, 0, 1), 1);
  c += check(gsl_spmatrix_get(g->t, 1, 1), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 3), 0);
  c += check(gsl_spmatrix_get(g->t, 3, 0), 0);
  c += check(gsl_spmatrix_get(g->o, 1, 2), 0);
  c += check(gsl_spmatrix_get(g->o, 0, 2), 3);
  //  print__mat(g);
  print_graph(g, 'c');
  print_graph(g, 'h');
  free__graph_t(g);
  return c;
}

int test_pile(void){
  int c = 0;
  struct pile* p = pile_vide(10);
    c += check(p->size, 0);    //
  for (int i = 0; i < 10; i++){
    empiler(p, i);
  }
  c += check(p->size, 10); //
  for (int i = 0; i < 8; i++){
    depiler(p);
  }
  c += check(p->size, 2);//
  c += check(depiler(p), 1);//
  c += check(depiler(p), 0);//
  c += check(p->size, 0);
  c += check(depiler(p), -1);
  pile_free(p);
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
  recap_test("LA PILE",   test_pile(), N_PILE);
  return 0;
}
    
