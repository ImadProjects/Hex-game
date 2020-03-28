#include <stddef.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>
#include <math.h>
#include "move.h"
#include "pile.h"
#include "graph_aux.h"

void color_print(const gsl_spmatrix* o, int n){
  int s = (int) gsl_spmatrix_get(o, 0, n);
  int ss = (int) gsl_spmatrix_get(o, 1, n);
  if (s > ss){
    printf("\033[0;31m");
  }
  if (s < ss){
    printf("\033[0;32m");
  } 
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
  int i;
  int ligne = 0;
  int nb_elem = 2*n + 1;//décroit le long d'une ligne
  int nb_elem2 = 2*n + 1;//constant le long d'une ligne
  int checkp = !(n==1) * 1;
  int inc = 2;
  for (i = 0; i < 6*n*n; i++){
    //    printf("%d, %d, %d, %d\n", ligne, nb_elem, i, inc);
    if (nb_elem != nb_elem2){
      gsl_spmatrix_set(t, i, i-1, 1);
    }

    if (nb_elem > 1){
      gsl_spmatrix_set(t, i, i+1, 1);
    }

    if ((((nb_elem % 2) && (i < 3*n*n)) ||
	 ((!(nb_elem % 2)) && ( i >= 3*n*n)))
	&& (ligne < 2*n - 1)){
	
      //      printf("1\n");
      gsl_spmatrix_set(t, i, i + nb_elem2 - (i >= 3*n*n), 1);
    }

    if ((((!(nb_elem % 2)) && (i < 3*n*n)) ||
	((nb_elem % 2) && (i >= 3*n*n)))
	&& (ligne > 0)){
  
      //      printf("2\n");
      gsl_spmatrix_set(t, i, i - nb_elem2 + (i < 3*n*n), 1);
    }
    
    
    nb_elem--;
    if (nb_elem == 0){
      ligne++;
      if (ligne == n - 1){
	checkp = 0;
	inc = -2;
	nb_elem2 += 2;
      }
      else{
	if (checkp == 0){
	  checkp = 1;
	}
	else{
	  nb_elem2 += inc;
	}
      }
      nb_elem = nb_elem2;
    }
  }
}

void assign_colors(gsl_spmatrix* o, int n){
  int m = n;
  for (int i = 0; i < m-1; i++){
    gsl_spmatrix_set(o, 0, i, 3);
    gsl_spmatrix_set(o, 1, m*(i+1), 2);
    gsl_spmatrix_set(o, 1, m*(i+1)-1, 3);
    gsl_spmatrix_set(o, 0, n*n - i - 1, 2);
  }
}

void assign_colors_tr(gsl_spmatrix* o, int n){
  int max = 6 * n*n;
  int m = 2*n + 1;
  int last = m;
  int s = 0;
  for (int i = 1; i < m; i++){
    gsl_spmatrix_set(o, 0, i, 3);
    gsl_spmatrix_set(o, 0, max - i - 1, 2);
  }
  for (int i = 0; i < n; i++){
    gsl_spmatrix_set(o, 1, s, 2);
    if (i){
      gsl_spmatrix_set(o, 1, s+1, 2);
    }
    s += last;
    //gsl_spmatrix_set(o, 0, s - 1, 3);
      last += 2;
  }
}
