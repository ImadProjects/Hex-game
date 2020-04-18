#include <stddef.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>
#include <math.h>
#include "move.h"
#include "pile.h"

void assign_links(gsl_spmatrix* t, char c, int n);
void assign_tr(gsl_spmatrix* t, char c, int n);
void assign_colors(gsl_spmatrix* o, int n);
void assign_colors_tr(gsl_spmatrix* o, int n);
void color_print(const gsl_spmatrix* o, int n);
struct graph_t *copy_graph(struct graph_t *graph);
