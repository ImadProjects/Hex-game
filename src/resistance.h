#ifndef _RESISTANCE_H_
#define _RESISTANCE_H_

#include <stdlib.h>
#include "move.h"
#include "pile.h"
#include "graph.h"
#include "graph_aux.h"

double get_resistance(const struct graph_t* g, int color, int i, int j);

double** generate_meshes(const struct graph_t* g, int color);

void free_sys(double** mat, int n);

void gauss(double** mat, double* b, double* x, int n);

double get_ratio(const struct graph_t* g, struct move_t mec);

#endif
