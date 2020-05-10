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

void compute_path(struct dynamic_array *path, int *previous, enum color_t color, int num_vertices)
{
  int k;
  if (color == 0)
    k = num_vertices - 1;
  else
    k = 2 * (num_vertices - 1) * (num_vertices - 1);
  while (k != -1)
  {
    add__to_dynamic_array(path, k);
    k = previous[k];
  }
}


struct dynamic_array *djikstra(struct graph_t *G, int position, enum color_t color)
{
  int V = G->num_vertices;
  int dist[V];// The output array.  dist[i] will hold the shortest 
  // distance from src to i 
  int parent[V];
  int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
  // path tree or shortest distance from src to i is finalized 
  
  // Initialize all distances as INFINITE and stpSet[] as false 
  for (int i = 0; i < V; i++) 
    dist[i] = INFINIT, sptSet[i] = 0, parent[i] = INFINIT; 
  
  // Distance of source vertex from itself is always 0 
  dist[position] = 0;
  parent[position] = -1;
  
  // Find shortest path for all vertices 
  for (int count = 0; count < V - 1; count++) { 
    // Pick the minimum distance vertex from the set of vertices not 
    // yet processed. u is always equal to src in the first iteration. 
    int u = find_min_distance(dist, sptSet, V);
    
    // Mark the picked vertex as processed 
    sptSet[u] = 1; 
  
    // Update dist value of the adjacent vertices of the picked vertex. 
    for (int v = 0; v < V; v++) {
  
      // Update dist[v] only if is not in sptSet, there is an edge from 
      // u to v, and total weight of path from src to  v through u is 
      // smaller than current value of dist[v]
      int d = (int)(gsl_spmatrix_get(G->t,u,v)-gsl_spmatrix_get(G->o,color,v)*gsl_spmatrix_get(G->o,color,u));
      if (!sptSet[v] &&
	  gsl_spmatrix_get(G->t,u,v)  &&
	  dist[u] != INFINIT &&
	  dist[u] + d < dist[v]) {
	dist[v] = dist[u] + d;
	parent[v] = u;
      }
    }
  }
  
  int M = width__graph_t(G);
    struct dynamic_array* p= empty__dynamic_array();
    if(color==BLACK){
      int i=G->num_vertices-1;
      while(i!=-1){
	// if(i==INT_MA)
	// break;
	add__to_dynamic_array(p,i);
	
	i=parent[i];
      }
    }
    else if(color==WHITE){
      int i=2*M+1;
      while(i!=-1){
	//if(i==INT_MA)
        //break;
	add__to_dynamic_array(p,i);
	
	i=parent[i];
      }
    }
    //printSolution(dist,parent,G->num_vertices); 
    return p;
    // print the constructed distance array 
}





struct dynamic_array *djikstra2(struct graph_t *graph, int position, enum color_t color)
{
  int distance[graph->num_vertices];
  int previous[graph->num_vertices];
  int selected[graph->num_vertices];

  for (int k = 0; k < graph->num_vertices; k++)
  {
    distance[k] = INFINIT;
    previous[k] = INFINIT;
    selected[k] = 0;
  }

  distance[position] = 0;
  previous[position] = -1;

  for (int i = 0; i < graph->num_vertices - 1; i++)
  {
    int min_vertex = find_min_distance(distance, selected, graph->num_vertices);
    selected[min_vertex] = 1;

    int vertex = 0;
    int weight1_2 = gsl_spmatrix_get(graph->t, min_vertex, vertex) - gsl_spmatrix_get(graph->o, color, vertex);
    int d1 = distance[min_vertex];
    int d2 = distance[vertex];

    for (vertex = 0; vertex < graph->num_vertices; vertex++)
    {
      if (d2 > d1 + weight1_2 && gsl_spmatrix_get(graph->t, min_vertex, vertex) && gsl_spmatrix_get(graph->o, color, vertex) && d1 != INFINIT)
      {
        distance[vertex] = d1 + weight1_2;
        selected[vertex] = min_vertex;
      }
    }
  }
  struct dynamic_array *path = empty__dynamic_array();
  compute_path(path, previous, color, graph->num_vertices);
  return path;
}

struct graph_t *copy_new_graph(struct graph_t *graph, struct move_t move, enum color_t color)
{
  struct graph_t *new_graph = malloc(sizeof(struct graph_t));
  *new_graph = *graph;
  new_graph->t = gsl_spmatrix_alloc(graph->num_vertices, graph->num_vertices);
  new_graph->o = gsl_spmatrix_alloc(2, graph->num_vertices);
  coloriate__graph_t(new_graph, color, move);
  return new_graph;
}

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

