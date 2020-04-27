#ifndef _RESISTANCE_H_
#define _RESISTANCE_H_

#include <stdlib.h>
#include "move.h"
#include "pile.h"
#include "graph.h"

float get_resistance(struct graph_t* g, int color, int n);

float** generate_meshes(struct graph_t* g, int color);

void free_sys(float** mat, int n);

void gauss(float** mat, float* b, float* x, int n);

float get_ratio(const struct graph_t* g, struct move mec);

#endif
