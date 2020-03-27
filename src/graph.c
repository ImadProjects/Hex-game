#include <stddef.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>
#include <math.h>
#include "move.h"
#include "pile.h"

void assign_links(gsl_spmatrix* t, char c, int n);
void assign_tr(gsl_spmatrix* t, char c, int n);
void assign_colors(gsl_spmatrix* o, int n);
void assign_colors_tr(gsl_spmatrix* o, int n);

struct graph_t* new__graph_t(int n, char c){
  if (c != 't'){
    n++;
  }
  struct graph_t* g = malloc(sizeof(struct graph_t));
  g->num_vertices = n*n * (1 + 5 * (c == 't'));//n² sauf si triangulaire auquel cas on a 6n²
  g->t = gsl_spmatrix_alloc(g->num_vertices, g->num_vertices);
  g->o = gsl_spmatrix_alloc(2, g->num_vertices);
  if (c != 't'){
    assign_links(g->t, c, n);
  }
  else{
    assign_tr(g->t, c, n);
  }
  //    printf("sortie1\n");
  if (c != 't'){
    assign_colors(g->o, n);
  }
  else{
    assign_colors_tr(g->o, n);
  }
  //  printf("sortie2\n");
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
    printf(") %d\n", i);
  }
}


int coloriate__graph_t(struct graph_t* g, int color, struct move_t move){
  int n = (int) move.m;
  if ((gsl_spmatrix_get(g->o, 0, n)==0) && (gsl_spmatrix_get(g->o, 1, n) == 0)){
    gsl_spmatrix_set(g->o, color, n, 1);
    return 0;
  }
  return 1;
}

void print_graph(struct graph_t* g, char c){//pour graphe hexa ou carré
  printf("\n");
  int m = sqrt(g->num_vertices);
  char* s = malloc(sizeof(char) * (2*m+5));
  char* ss = s + 2*m + 3;
  ss[0] = '\n';
  ss[1] = '\0';
  for (int i = 0; i < m; i++){
    if (i != 0){
      ss -= 2;
      ss[2] = ' ';
      ss[1] = ' ';
      ss[0] = '\n';
    }
    if (c == 'h'){
      printf("%s", ss);
    }
    else{
      printf("\n");
    }
    if (c == 'h')
    {
    for (int j = 0; j < m; j++){
      int s = (int) gsl_spmatrix_get(g->o, 0, j + i*m);
      int ss = (int) gsl_spmatrix_get(g->o, 1, j + i*m);
      if (s > ss){
  printf("\033[0;31m");
      }
      if (s < ss){
  printf("\033[0;32m");
      }
      printf(" ⬡ ");
      printf("\033[0m");
    }
    //printf(")");
  }

  if (c == 'c')
  {
    for (int j = 0; j < m; j++){
      int s = (int) gsl_spmatrix_get(g->o, 0, j + i*m);
      int ss = (int) gsl_spmatrix_get(g->o, 1, j + i*m);
      if (s > ss){
  printf("\033[0;31m");
      }
      if (s < ss){
  printf("\033[0;32m");
      }
      printf("  o ");
      printf("\033[0m");
    }
    //printf(")");
  }
}
  printf("\n");
  free(s);
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

int is_winning(struct graph_t* g, int color, struct move_t move, char c){
  struct pile* p = pile_vide(g->num_vertices);
  char* tab = malloc(sizeof(char) * g->num_vertices); // indique si on a dejà visité un sommet
  int cond1 = 0;
  int cond2 = 0;
  int s = (int) move.m;
  for (int i = 0; i < g->num_vertices; i++){
    tab[i] = 0;
  }
  tab[s] = 1;
  empiler(p, s);
  
  while (!est_vide(p)){
    s = depiler(p);
    if (gsl_spmatrix_get(g->o, color, s) == 3){//bord 1
      cond1 = 1;
    }
    if (gsl_spmatrix_get(g->o, color, s) == 2){//bord 2
      cond2 = 1;
    }
    if (cond1 && cond2){
      pile_free(p);
      free(tab);
      return 1;
    }
    for (int i = 0; i < g->num_vertices; i++){
      if((gsl_spmatrix_get(g->o, color, i) > 0) && (gsl_spmatrix_get(g->t, s, i)) && tab[i] == 0){
	empiler(p, i);
	tab[i] = 1;
      }
    }
  }
  pile_free(p);
  free(tab);
  return 0;
}

void print_tr(struct graph_t* g){
  int m = sqrt(g->num_vertices / 6);
  char* s = malloc(sizeof(char) * (2*m+5));
  char* ss = s;
  int ligne = 0;
  int nb_elem2 = 2*m + 1;
  int c1 = 0;
  int c2 = 1;
  int c;
  for (int i = 0; i < m; i++){
    s[i] = ' ';
  }
  s[m] = '\0';
  for (int i = 0; i < m; i++){
      printf("\n%s", s);
      s += 1;
      
    for (int j = 0; j < nb_elem2; j++){
      if (j%2){
	int n = (int) gsl_spmatrix_get(g->o, 0, c2);
	int nn = (int) gsl_spmatrix_get(g->o, 1, c2);

	if (n > nn){
	  printf("\033[0;31m");
	}
	if (n < nn){
	  printf("\033[0;32m");
	}
	c2 += 2;
	printf(" ▽ ");
	printf("\033[0m");
      }
    }
    nb_elem2++;
    printf("\n%s", s);
    
    for (int j = 0; j < nb_elem2; j++){
      if (!(j%2)){
	int n = (int) gsl_spmatrix_get(g->o, 0, c1);
	int nn = (int) gsl_spmatrix_get(g->o, 1, c1);
	if (n > nn){
	  printf("\033[0;31m");
	}
	if (n < nn){
	  printf("\033[0;32m");
	}
	c1 += 2;
	printf(" △ ");
	printf("\033[0m");
      }
    }
    nb_elem2++;
    ligne++;
    c = c1;
    c1 = c2;
    c2 = c;
  }
  nb_elem2 -= 1;
  c1 = m*m * 3 + 1;
  c2 = m*m * 3;
  ///////////////////////////////////////////////////////////
  for (int i = 0; i < m; i++){
      printf("\n%s", s);
      s -= 1;
      
    for (int j = 0; j < nb_elem2 && c2 < g->num_vertices; j++){
      if (!(j%2)){

	int n = (int) gsl_spmatrix_get(g->o, 0, c2);
	int nn = (int) gsl_spmatrix_get(g->o, 1, c2);
	if (n > nn){
	  printf("\033[0;31m");
	  //	  printf("c2 %d\n", c2);
	}
	if (n < nn){
	  printf("\033[0;32m");
	}
	c2 += 2;
	printf(" ▽ ");
	printf("\033[0m");
      }
    }
    nb_elem2--;
    
    printf("\n%s", s);
    
    for (int j = 0; j < nb_elem2 && c1 < g->num_vertices; j++){
      if (j%2){

	int n = (int) gsl_spmatrix_get(g->o, 0, c1);
	int nn = (int) gsl_spmatrix_get(g->o, 1, c1);
	if (n > nn){
	  printf("\033[0;31m");
	  //	  printf("%d\n", c1);
	}
	if (n < nn){
	  printf("\033[0;32m");
	}
	c1 += 2;
	printf(" △ ");
	printf("\033[0m");
      }
    }
    ligne++;
    c = c1;
    c1 = c2;
    c2 = c;
    nb_elem2--;
  }  
    
    
    
  printf("\n");
  free(ss);
}
  
