#ifndef _RESISTANCE_H_
#define _RESISTANCE_H_

#include <stdlib.h>
#include "move.h"
#include "pile.h"
#include "graph.h"
#include "graph_aux.h"

//returns the value of the resistance between two neighboors vertices
double get_resistance(const struct graph_t *g, int color, int i, int j);

//fills a matrix with a system consisting of meshes equations
double **generate_meshes(const struct graph_t *g, int color);

//liberates a matrix
void free_sys(double **mat, int n);

//gauss pivots method to solve a linear system
void gauss(double **mat, double *b, double *x, int n);

//returns the quotient of the total resistances of each player
double get_ratio(const struct graph_t *g, struct move_t mec);

#endif
