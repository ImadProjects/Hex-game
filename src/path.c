#include "path.h"
#define INFINIT 100000

int find_min_distance(int *distance, int *selected, int num_vertices)
{
  int min = INFINIT;
  int vertex = -1;
  for (int k = 0; k < num_vertices; k++)
  {
    if (distance[k] <= min && selected[k] == 0)
    {
      min = distance[k];
      vertex = k;
    }
  }
  return vertex;
}



struct dynamic_array* djikstra(struct graph_t* G,size_t M, int src,enum color_t id){
  int dist[G->num_vertices]; 

  int parent[G->num_vertices];
   for(size_t i=0;i<G->num_vertices;i++){
    parent[i]=INFINIT;
  }

  int sptSet[G->num_vertices]; 
  for (size_t i = 0; i < G->num_vertices; i++)
    dist[i] = INFINIT, sptSet[i] = 0;

  dist[src] = 0;
  parent[src]=-1;

  for (int count = 0; count < (int)(G->num_vertices - 1); count++) {

    int u = find_min_distance(dist, sptSet,G->num_vertices);

    sptSet[u] = 1;

    for (size_t v = 0; v < G->num_vertices; v++){

      if (!sptSet[v] && gsl_spmatrix_get(G->t,u,v)  && dist[u] != INFINIT 
        && !gsl_spmatrix_get(G->o,(id+1)%2,v) && dist[u] + (int)(gsl_spmatrix_get(G->t,u,v)-gsl_spmatrix_get(G->o,id,v)*gsl_spmatrix_get(G->o,id,u)) <= dist[v]){ 
        dist[v] = dist[u] + (int)(gsl_spmatrix_get(G->t,u,v)-gsl_spmatrix_get(G->o,id,v)*gsl_spmatrix_get(G->o,id,u));
        parent[v]=u;
        }
    }
  }
  
  struct dynamic_array* p= empty__dynamic_array();
  int i;
  if(id==BLACK)
    i=G->num_vertices-1;
  else
     i=2*M+1;
  
    while(i!=-1){
      add__to_dynamic_array(p,i);
      i=parent[i];
    }
  
  return p;
}


int path_score(struct dynamic_array* path,struct graph_t* G)
{
  size_t score = 0,i=0;
  for(i=0; i<path->size; i++)
    {
      if((gsl_spmatrix_get(G->o, 0, path->array[i]) == 0) && ((gsl_spmatrix_get(G->o, 1, path->array[i]) == 0)))
        score++;
    }
    return score;
}


int path_quality(struct graph_t* G,int M,int color){
  if(game_over(G,color))
    return -INFINIT;
  if(game_over(G,(color+1)%2))
    return INFINIT;
  struct dynamic_array* p_path=djikstra(G,M,color*(M+1),color);
  struct dynamic_array* op_path=djikstra(G,M,(color+1)%2*(M+1),(color+1)%2);
  int p_score=path_score(p_path,G);
  int op_score=path_score(op_path,G);
  free__dynamic_array(p_path);
  free__dynamic_array(op_path);
  return p_score-op_score;
}

