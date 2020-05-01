#include "resistance.h"
#include <stdio.h>
#include <stdlib.h>
#include "move.h"

#define N_SYS 4
#define N_GAUSS 2

void print_vect(float* v, int n){
  printf("(");
  for (int i = 0; i < n; i++){
    printf("%f, ", v[i]);
  }
  printf(")\n");
}

void print_m(float** mat, int n){
  for (int i = 0; i < n; i++){
    printf("(");
    for (int j = 0; j < n; j++){
      printf("%f ",  mat[i][j]);
    }
    printf(")\n");
  }
}

int test_sys(){
  int n = 2;
  int c = 0;
  struct graph_t* g = new__graph_t(n, 'c');
  //print_graph(g, 'c');
  float** mat = generate_meshes(g, 0);
  //  print_m(mat, n*n);
  c += (mat[0][0] >= 5.99 && mat[0][0] <= 6.01);
  c += (mat[1][0] >= -1.01 && mat[1][0] <= -0.99);
  c += (mat[1][1] >= 10.99 && mat[1][1] <= 11.01);
  c += (mat[2][1] >= -1.01 && mat[2][1] <= -0.99);
  free_sys(mat, 5);
  free__graph_t(g);
  return c;
}

int test_gauss(){
  int m = 2;
  int c = 0;
  float** mat = malloc(sizeof(float*) * m);
  mat[0] = malloc(sizeof(float) * m);
  mat[1] = malloc(sizeof(float) * m);
  float* b = malloc(sizeof(float) * m);
  b[0] = 4;
  b[1] = 3;
  mat[0][0] = 2;
  mat[0][1] = 1;
  mat[1][0] = 1;
  mat[1][1] = 1;
  float* x = malloc(sizeof(float) * m);
  gauss(mat, b, x, m);
  c += (x[1] > 0.99 && x[1] < 1.01);
  c += (x[0] > 1.99 && x[0] < 2.01);
    
    print_vect(x, m);
  
  free(b);
  free(x);
  free_sys(mat, 2);

  return c;
}
 
int test(){
  int n = 3;

  struct graph_t* g = new__graph_t(n, 'c');

  float* b = malloc(sizeof(float) * (n * n + 1));
  float* x = malloc(sizeof(float) * (n * n + 1));

  for (int i = 0; i < n*n + 1; i++){
    x[i] = 0.;
    b[i] = 0.;
  }

  b[n*n] = 10;

  struct move_t mv = {6, 0};
  coloriate__graph_t(g, 1, mv);
  mv.m = 10;
  coloriate__graph_t(g, 0, mv);
  float** mat = generate_meshes(g, 1);//
  gauss(mat, b, x, n*n + 1);
  print_vect(x, n*n + 1);

  print_graph(g, 'c');
  free(b);
  free(x);
  free_sys(mat, n*n + 1);
  free__graph_t(g);
}
/*
int main(){
  printf("=== tests sur la génération du système: %d/%d réussis ===\n", test_sys(), N_SYS);
  printf("=== tests sur la génération du système: %d/%d réussis ===\n", test_gauss(), N_GAUSS);
  test();
  return 0;
}
*/
