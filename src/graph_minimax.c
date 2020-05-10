#include "graph_minimax.h"
#include "path.h"
#include "graph_aux.h"

int DFSutil(struct graph_t* G,size_t n,size_t* visited,enum color_t id){
  size_t M=(int)sqrt(G->num_vertices)-1;
  //mark the current vertex as visited
  visited[n]=1;
  struct dynamic_array* nb=neighbours(G,n);
  //recur for all the adjacent vertices of n
  for(size_t i=0;i<nb->size;i++){
    if(gsl_spmatrix_get(G->o,id,nb->array[i])==1 && !visited[nb->array[i]]){
      if((id==BLACK && nb->array[i]>=G->num_vertices-M) || (id==WHITE && nb->array[i]%(M+1)==M)){
        //there's a winner
        free__dynamic_array(nb);
        return 1;
      }
      else{
        if(DFSutil(G,nb->array[i],visited,id)){
          //there's a winner
          free__dynamic_array(nb);
          return 1;
        }
      }
    }
  }
  //it's a draw
  free__dynamic_array(nb);
  return 0;
}


int over(struct graph_t* G,enum color_t id){
  size_t M=(int)sqrt(G->num_vertices)-1;
  size_t* visited=malloc(G->num_vertices*sizeof(size_t));
  // Mark all the vertices as not visited
  for(size_t i=0;i<G->num_vertices;i++){
    visited[i]=0;
  }
  //Determine the start vertex of the DFS
  int a=0,b=0;
  if(id==BLACK){
    a=DFSutil(G,0,visited,id);
  }else if(id==WHITE){
    b=DFSutil(G,M+1,visited,id);
  }
  free(visited);
  if(a==1 || b==1)
    return 1;
  else
    return 0;
}



struct dynamic_array* get__possible_moves(struct graph_t *G){

  size_t vertices = size__graph_t(G);
  struct dynamic_array *p = empty__dynamic_array();
  
  for(size_t i = 0; i < vertices; i++)
    if(! is_taken(G->o, i))
      add__to_dynamic_array(p, i);


  return p;

}


size_t best_move(struct dynamic_array *moves, int values[]){

  int n = moves->size;
  int min = INFINIT;
  size_t min_index = -1;

  for(int i = 0; i < n; i++)
    if(values[i] <= min)
      min = values[i], min_index = moves->array[i];

  return min_index;

}


int min(int a, int b){

  return (a <= b) ? a: b;

}


int max(int a, int b){

  return (a >= b) ? a: b;

}


void change_value(int *a, int b){

  *a = b;

}


int path_score(struct graph_t *G, struct dynamic_array *p){

  int score = 0;

  for(int i = 0; i < p->size; i++)
    if(is_taken(G->o, p->array[i]))
      score++;

  return score;

}


int how__good_is(struct graph_t *G, int move, enum color_t color){

  if(over(G, color))
    return -INFINIT;

  else if(over(G, 1 - color))
    return INFINIT;

  struct dynamic_array *p1 = djikstra(G, move, color);
  struct dynamic_array *p2 = djikstra(G, move, 1 - color);

  int d = path_score(G, p1) - path_score(G, p2);
  free__dynamic_array(p1);
  free__dynamic_array(p2);

  return d;

}


int minimax(struct graph_t *G, int move, int MaxMin, int depth, int alpha, int beta, enum color_t color){

  if(depth == 0 || over(G, color) || over(G, 1 - color))
    return how__good_is(G, move, color);

  else if(MaxMin){
    int maxvalue = - INFINIT;
    struct dynamic_array *p = neighbours(G, move);
    for(int i = 0; i < p->size; i++){
      struct move_t new_move = {.c = color, .m = p->array[i]};
      struct graph_t *G1 = copy_new_graph(G, new_move, color);
      int value = minimax(G1, new_move.m, 1 - MaxMin, depth - 1, alpha, beta, color);
      maxvalue = max(maxvalue, value);
      change_value(&alpha, max(alpha, value));
      free__graph_t(G1);
      if(beta <= alpha)
	break;
    }

    free__dynamic_array(p);
    return maxvalue;
  }

  else{

    int minvalue = INFINIT;
    struct dynamic_array *p2 = neighbours(G, move);
    for(int i = 0; i < p2->size; i++){
      struct move_t new_move2 = {.c = color, .m = p2->array[i]};
      struct graph_t *G2 = copy_new_graph(G, new_move2, color);
      int value2 = minimax(G2, new_move2.m, MaxMin, depth - 1, alpha, beta, color);
      minvalue = min(minvalue, value2);
      change_value(&beta, min(beta, value2));
      free__graph_t(G2);
      if(beta <= alpha)
	break;
    }

    free__dynamic_array(p2);
    return minvalue;
  }
}
