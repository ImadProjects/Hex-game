#ifndef _GRAPH_MINIMAX_H
#define _GRAPH_MINIMAX_H
#include "path.h"

struct dynamic_array* get__possible_moves(struct graph_t *G);
size_t best_move(struct dynamic_array *moves, int values[]);
int minimax(struct graph_t *G, int  move, int MaxMin, int depth, int alpha, int beta, enum color_t color);





#endif
