#include "graph_minimax.h"
#include "path.h"
#include "graph_aux.h"



struct dynamic_array *neighbours(struct graph_t *graph, int position)
{
  struct dynamic_array *neighbours = empty__dynamic_array();
  for (int k = 0; k < graph->num_vertices; k++)
  {
    if (gsl_spmatrix_get(graph->t, position, graph->num_vertices - k - 1) == 1)
      add__to_dynamic_array(neighbours, graph->num_vertices - k - 1);
  }
  return neighbours;
}



int max_a_b(int a,int b){
  if(a>=b)
    return a;
  else
    return b;
}

int min_a_b(int a,int b){
  if(a<=b)
    return a;
  else
    return b;
}



struct dynamic_array* path_intesection(struct dynamic_array* p1,struct dynamic_array* p2){
  struct dynamic_array* inter=empty__dynamic_array();
  size_t i=0;
  if(p1->size<p2->size){
    for(i=0;i<p1->size;i++){
      for(size_t j=0;j<p2->size;j++){
        if(p1->array[i]==p2->array[j]){
          add__to_dynamic_array(inter,p1->array[i]);
          continue;
        }
      }
    }
  }
  else{
    for(i=0;i<p2->size;i++){
      for(size_t j=0;j<p1->size;j++){
        if(p2->array[i]==p1->array[j]){
          add__to_dynamic_array(inter,p2->array[i]);
          continue;
        }
      }
    }
  }
  return inter;
}


struct dynamic_array* path_union(struct dynamic_array* p1,struct dynamic_array* p2){
  for(size_t i=0;i<p2->size;i++){
    add__to_dynamic_array(p1,p2->array[i]);
  }
  return p1;
}


int minimax(struct graph_t* G, struct graph_t *graph_player, int maxminplayer, int depth, int alpha, int beta,enum color_t id,int M){
  struct dynamic_array* player_path=djikstra(graph_player,M,(1-id)*(M+1),(1-id));
  struct dynamic_array* enemy_path=djikstra(graph_player,M,((1-id)+1)%2*(M+1),((1-id)+1)%2);
  struct dynamic_array* intersection=path_intesection(player_path,enemy_path);
  if(depth==0 || intersection->size==0 || game_over(G,id) || game_over(G,1-id) ){
    int h=path_quality(G,M,(1-id)); 
    return h;
  }

  else if(maxminplayer){
    struct dynamic_array* player_path=djikstra(graph_player,M,(1-id)*(M+1),(1-id));
    struct dynamic_array* enemy_path=djikstra(graph_player,M,((1-id)+1)%2*(M+1),((1-id)+1)%2);
    struct dynamic_array* intersection=path_intesection(player_path,enemy_path);
    int max=-INFINIT,count=0;
    for(size_t i=0;i<intersection->size;i++){
      if(!is_taken(G->o,intersection->array[i]) ){
          count++;
          struct move_t move;
          move.m=intersection->array[i];
          move.c=id;
          struct graph_t*copy=copy_new_graph(G,move);
          max=max_a_b(max,minimax(copy,graph_player,0,depth-1,alpha,beta,1-id,M));
          free__graph_t(copy);
          alpha=max_a_b(alpha,max);
          if(beta <= alpha)
            break;
      }
    }
    free__dynamic_array(player_path);
    free__dynamic_array(enemy_path);
    free__dynamic_array(intersection);
    return max;
  }
  else{
    struct dynamic_array* player_path=djikstra(graph_player,M,(1-id)*(M+1),(1-id));
    struct dynamic_array* enemy_path=djikstra(graph_player,M,((1-id)+1)%2*(M+1),((1-id)+1)%2);
    struct dynamic_array* intersection=path_intesection(player_path,enemy_path);
    int min=INFINIT,count2=0;
    for(size_t i=0;i<intersection->size;i++){
      if(!is_taken(G->o,intersection->array[i])){
        count2++;
        struct move_t move;
        move.m=intersection->array[i];
        move.c=id;
        struct graph_t*copy=copy_new_graph(G,move);
        min=min_a_b(min,minimax(copy,graph_player,1,depth-1,alpha,beta,1-id,M));
        free__graph_t(copy);
        beta=min_a_b(beta,min);
        if(beta <= alpha)
          break;
      }
    }
    free__dynamic_array(player_path);
    free__dynamic_array(enemy_path);
    free__dynamic_array(intersection);
    return min;
  }
}


struct move_t best_move(struct graph_t *graph_player,enum color_t id, int M,struct dynamic_array* inter){
  int bestval=INFINIT;
  struct move_t m;
  m.c=id;

  for(size_t i=0;i<inter->size;i++){
      if(!is_taken(graph_player->o,inter->array[i])){
          struct move_t move;
          move.m=inter->array[i];
          move.c=id;
          struct graph_t*copy=copy_new_graph(graph_player,move);
          int val=minimax(copy,graph_player,1,50,-INFINIT,INFINIT,1-id,M);
          free__graph_t(copy);
          if(val<bestval){
            bestval=val;
            m.m=inter->array[i];
          }

      }
    }
  return m;
}
