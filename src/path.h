#ifndef _PATH_H_
#define _PATH_H_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "dynamic_array.h"
#include "path.h"


int find_min_distance(int *distance, int *selected, int num_vertices);

void compute_path(struct dynamic_array *path, int *previous, enum color_t color, int num_vertices);

struct dynamic_array *djikstra(struct graph_t *graph, int position, enum color_t color);

struct graph_t *copy_new_graph(struct graph_t *graph, struct move_t move, enum color_t color);

struct dynamic_array *neighbours(struct graph_t *graph, int position);

#endif
