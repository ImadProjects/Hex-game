#ifndef _HEX_GRAPH_H_
#define _HEX_GRAPH_H_
#include "move.h"

#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>

struct graph_t {
  size_t num_vertices;  // Number of vertices in the graph
  gsl_spmatrix* t;      // Sparse matrix of size n*n,
                        // t[i][j] == 1 means there is an edge from i to j
  gsl_spmatrix* o;      // Sparse matrix of size 2*n, one line per player
                        // o[p][i] == 1 means that the vertex i is owned by p
};

//ne marche pas bien pour les graphes triangulaires
struct graph_t* new__graph_t(int n, char c);

void free__graph_t(struct graph_t* g);

void print__mat(const struct graph_t* g);

//renvoie 0 si la case est libre, 1 sinon
int coloriate__graph_t(struct graph_t* g, int color, struct move_t move);

//pour graphe carré ou hexa
void print_graph(struct graph_t* g, char c);

int is_winning(struct graph_t* g, int color, struct move_t move);
#endif // _HEX_GRAPH_H_
