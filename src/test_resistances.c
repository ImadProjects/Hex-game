#include "resistance.h"
#include <stdio.h>
#include <stdlib.h>
#include "move.h"

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
  struct graph_t* g = new__graph_t(n, 'c');
  print_graph(g, 'c');
  float** mat = generate_meshes(g, 0);
  print_m(mat, n*n);
  free_sys(mat, n*n);
  free__graph_t(g);
  return 0;
}

int test_gauss(){
  /*  int m = 2;
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
  print_vect(x, m);
  free(b);
  free(x);
  free(b);*/

  int n = 3;
  struct graph_t* g = new__graph_t(n, 'c');
  float* b = malloc(sizeof(float) * n * n);
  float* x = malloc(sizeof(float) * n * n);
  for (int i = 0; i < n*n; i++){
    x[i] = 0.;
    b[i] = 0.;
  }
  b[0] = 10;
  b[n*n - 1] = 10;
  struct move_t mv = {6, 0};
  coloriate__graph_t(g, 0, mv);
  mv.m = 10;
  //  coloriate__graph_t(g, 0, mv);
  float** mat = generate_meshes(g, 1);//
  gauss(mat, b, x, n*n);
  print_vect(x, n*n);
  print_graph(g, 'c');
  free(b);
  free(x);
  free_sys(mat, n*n);
  free__graph_t(g);
}
 

int main(){
  test_sys();
  test_gauss();
  return 0;
}
