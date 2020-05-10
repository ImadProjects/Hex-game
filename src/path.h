#ifndef _PATH_H_
#define _PATH_H_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "dynamic_array.h"
#include "path.h"

int find_min_distance(int *distance, int *selected, int num_vertices);

struct dynamic_array *djikstra(struct graph_t *G, size_t M, int src, enum color_t id);

struct graph_t *copy_new_graph(struct graph_t *graph, struct move_t move);

struct dynamic_array *neighbours(struct graph_t *graph, int position);

#endif
