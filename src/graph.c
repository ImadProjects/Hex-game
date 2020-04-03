 #include <stddef.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>
#include <math.h>
#include "move.h"
#include "pile.h"
#include "graph_aux.h"

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

void print_graph(const struct graph_t* g, char c){//pour tout graphe
  int m = sqrt(g->num_vertices);
  printf("\n");
  char* s;
  char* ss;
  if (c == 't'){
    print_tr(g);
  }
  else{
  if (c == 'h'){
    s = malloc(sizeof(char) * (2*m+5));
    ss = s + 2*m + 3;
    ss[0] = '\n';
    ss[1] = '\0';
  }

  char* str;
  if (c == 'h'){
    str = " ⬡ ";
  }
  else{
    str = " o ";
  }
  for (int i = 0; i < m; i++){
    if (c == 'h'){
      if (i != 0){
	ss -= 2;
	ss[2] = ' ';
	ss[1] = ' ';
	ss[0] = '\n';
      }
    }
    if (c == 'h'){
      printf("%s", ss);
    }
    else{
      printf("\n");
    }
    for (int j = 0; j < m; j++){
      color_print(g->o, j + i*m);
      printf("%s", str);
      printf("\033[0m");
    }
  }
  if (c == 'h'){
    free(s);
  }
  printf("\n");
  }
}


int is_winning(const struct graph_t* g, int color, struct move_t move, char c){
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

void print_tr(const struct graph_t* g){
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
	color_print(g->o, c2);
	c2 += 2;
       	printf(" ▽ ");
	printf("\033[0m");
      }
    }
    nb_elem2++;
    printf("\n%s", s);
    
    for (int j = 0; j < nb_elem2; j++){
      if (!(j%2)){
	color_print(g->o, c1);
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
	color_print(g->o, c2);
	c2 += 2;
	printf(" ▽ ");
	printf("\033[0m");
      }
    }
    nb_elem2--;
    
    printf("\n%s", s);
    
    for (int j = 0; j < nb_elem2 && c1 < g->num_vertices; j++){
      if (j%2){
	color_print(g->o, c1);
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
  
