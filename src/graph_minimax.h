#ifndef _GRAPH_mini_a_bMAX_H
#define _GRAPH_mini_a_bMAX_H
#include "path.h"

struct dynamic_array *neighbours(struct graph_t *graph, int position);

int max_a_b(int a, int b);

int min_a_b(int a, int b);

int minimax(struct graph_t *G, struct graph_t *graph_player, int maxminplayer, int depth, int alpha, int beta, enum color_t id, int M);

struct move_t best_move(struct graph_t *graph_player, enum color_t id, int M, struct dynamic_array *inter);
#endif
