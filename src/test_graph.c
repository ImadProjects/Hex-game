#include <stdio.h>
#include <gsl/gsl_spmatrix.h>
#include "graph.h"
#include "pile.h"

#define N_GRAPH 9
#define N_PILE 7
#define N_PATH 6
#define N_TR 15

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

int check(int n,int att){
  return n == att;
}

int test_graph(void){
  int c = 0;
  struct graph_t* g = new__graph_t(3, 'h');
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
  //  print_tr(g);
  //  print_graph(g, 'c');
  //  print_graph(g, 'h');
  free__graph_t(g);
  return c;
}

int test_pile(void){
  int c = 0;
  struct pile* p = pile_vide();
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

int test_pathfinding(void){
  int c = 0;
  //carré
  struct graph_t* g = new__graph_t(3, 'c');
  struct move_t move  = {5};
  coloriate__graph_t(g, 1, move);
  print_graph(g, 'c');
  c += check(is_winning(g, 1, move, 'c'), 0);
  
  move.m = 6;
  coloriate__graph_t(g, 1, move);
  print_graph(g, 'c');
  c += check(is_winning(g, 1, move, 'c'), 1);
  free__graph_t(g);

  //hexa
  struct graph_t* gg = new__graph_t(5, 'h');
  move.m  = 7;
  coloriate__graph_t(gg, 0, move);
  move.m  = 8;
  coloriate__graph_t(gg, 0, move);
  move.m  = 13;
  coloriate__graph_t(gg, 1, move);
  move.m  = 19;
  coloriate__graph_t(gg, 1, move);
  move.m  = 25;
  coloriate__graph_t(gg, 0, move);
  move.m  = 14;
  coloriate__graph_t(gg, 0, move);
  print_graph(gg, 'h');

  c += check(is_winning(gg, 0, move, 'c'), 0);

  move.m = 6;
  coloriate__graph_t(gg, 0, move);


  move.m = 20;
  coloriate__graph_t(gg, 0, move); 
  c += check(is_winning(gg, 0, move, 'c'), 1);
  print_graph(gg, 'h');
  free__graph_t(gg);

  //triangle
  struct graph_t* t = new__graph_t(5, 't');
  for (int i = 0; i < 15; i++){
    move.m = 59 + i;
    coloriate__graph_t(t, 1, move);
  }
  move.m = 41;
  coloriate__graph_t(t, 0, move);
  print_graph(t, 't');
  c += check(is_winning(t, 0, move, 't'), 0);

  move.m = 58;
  coloriate__graph_t(t, 1, move);
  print_graph(t, 't');
  c += check(is_winning(t, 0, move, 't'), 0);
  free__graph_t(t);
  return c;
}

int test_tr(){
  struct graph_t* g = new__graph_t(5, 't');
  //  print_tr(g);
  int c = 0;
  c += check(g->num_vertices, 150);
  c += check(gsl_spmatrix_get(g->t, 0, 0), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 0), 1);
  c += check(gsl_spmatrix_get(g->t, 0, 1), 1);
  c += check(gsl_spmatrix_get(g->t, 1, 1), 0);
  c += check(gsl_spmatrix_get(g->t, 1, 3), 0);
  c += check(gsl_spmatrix_get(g->t, 3, 0), 0);
  c += check(gsl_spmatrix_get(g->o, 1, 2), 0);
  c += check(gsl_spmatrix_get(g->o, 0, 2), 3);
  c += check(gsl_spmatrix_get(g->o, 1, 0), 2);
  c += check(gsl_spmatrix_get(g->o, 0, 0), 0);
  c += check(gsl_spmatrix_get(g->o, 1, 149), 3);
  c += check(gsl_spmatrix_get(g->o, 0, 149), 0);
  c += check(gsl_spmatrix_get(g->o, 1, 148), 0);
  c += check(gsl_spmatrix_get(g->o, 0, 148), 2);  
  free__graph_t(g);
  return c;
}


int main(void){
  recap_test("LE GRAPHE", test_graph(), N_GRAPH);
  recap_test("LA PILE", test_pile(), N_PILE);
  recap_test("LE PATHFINDING", test_pathfinding(), N_PATH);
  recap_test("LE TRIANGLE", test_tr(), N_TR);
  return 0;
}
    
