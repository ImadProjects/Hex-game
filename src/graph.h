#ifndef _HEX_GRAPH_H_
#define _HEX_GRAPH_H_
#include "move.h"

#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>

struct graph_t
{

  size_t num_vertices; // Number of vertices in the graph

  gsl_spmatrix *t; // Sparse matrix of size n*n,
                   // t[i][j] == 1 means there is an edge from i to j
  gsl_spmatrix *o; // Sparse matrix of size 2*n, one line per player
                   // o[p][i] == 1 means that the vertex i is owned by p
};

//creates a new graph_t and returns its adress
struct graph_t *new__graph_t(int n, char c);

//frees a graph_t
void free__graph_t(struct graph_t *g);

//prints the adjacancy matrix of a graph_t
void print__mat(const struct graph_t *g);

//coloriates the graph_t according to a move. returns 1 if the location is already colored
int coloriate__graph_t(struct graph_t *g, int color, struct move_t move);

//prints the board
void print_graph(const struct graph_t *g, char c);

//prefer the use of print_graph
void print_tr(const struct graph_t *g);

//returns 1 if the player wins with his last move
int is_winning(const struct graph_t *g, int color, struct move_t move, char c);
#endif // _HEX_GRAPH_H_
