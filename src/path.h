#ifndef _PATH_H_
#define _PATH_H_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "dynamic_array.h"
#include "path.h"

int find_min_distance(int *distance, int *selected, int num_vertices);

struct dynamic_array *path_intesection(struct dynamic_array *p1, struct dynamic_array *p2);

struct dynamic_array *path_union(struct dynamic_array *p1, struct dynamic_array *p2);

struct dynamic_array *djikstra(struct graph_t *G, size_t M, int src, enum color_t color);

int path_score(struct dynamic_array *path, struct graph_t *G);

int path_quality(struct graph_t *G, int M, int color);

#endif
