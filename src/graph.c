#include <gsl/gsl_spmatrix.h>
#include <stddef.h>
#include "graph.h"
#include <stdio.h>

void assign_links(gsl_spmatrix* t, char c, int n);
void assign_tr(gsl_spmatrix* t, char c, int n);

struct graph_t* new__graph_t(int n, char c){
  struct graph_t* g = malloc(sizeof(struct graph_t));
  g->num_vertices = n * n * (1 + 5 * (c == 't'));//n² sauf si triangulaire auquel cas on a 6n²
  g->t = gsl_spmatrix_alloc(g->num_vertices, g->num_vertices);
  g->o = gsl_spmatrix_alloc(2, g->num_vertices);
  if (c != 't'){
    assign_links(g->t, c, n);
  }
  else{
    assign_tr(g->t, c, n);
  }
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

void assign_links(gsl_spmatrix* t, char c, int n){//initialise la matrice t pour un graphe no triangulaire
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      int N = i*n + j;
      if (i > 0){
	gsl_spmatrix_set(t, N, N-n, 1);//carré, hex
      }
      if (i < n - 1){
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

void assign_tr(gsl_spmatrix* t, char c, int n){//initialise la matrice t pour un graphe triangulaire
  int i = 0;
  int ligne = 0;
  int nb_elem = 2*n + 1;//décroit le long d'une ligne
  int nb_elem2 = 2*n + 1;//constant le long d'une ligne
  int check = (n==1) - 1;
  for (i; i < 6*n*n; i++){
    printf("%d, %d, %d\n", ligne, nb_elem, i);
    if (nb_elem != nb_elem2){
      gsl_spmatrix_set(t, i, i-1, 1);
    }
    if (nb_elem > 1){
      gsl_spmatrix_set(t, i, i+1, 1);
    }
    if (nb_elem % 2 && ligne < 2*n - 1){
      gsl_spmatrix_set(t, i, i + nb_elem2 + check, 1);
    }
    if (nb_elem % 2 && ligne > 0){
       gsl_spmatrix_set(t, i, i - nb_elem2 - check, 1);
    }
    nb_elem--;
    if (nb_elem == 0){
      ligne++;
      if (i < 3*n - 1){
	nb_elem2 += 2;
	check = 1;
      }
      else{
	if (i == 3*n - 1){
	  check = 0;
	}
	else{
	  nb_elem2 -= 2;
	  check = 1;
	}
      }
      nb_elem = nb_elem2;
    }
  }
}


    
