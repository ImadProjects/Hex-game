#ifndef _GRAPH_mini_a_bMAX_H
#define _GRAPH_mini_a_bMAX_H
#include "path.h"



int path_score(struct dynamic_array* path,struct graph_t* G);


int path_quality(struct graph_t* G,int M,int color);
//int path_quality(struct graph_t *G, int move, enum color_t color);


int max_a_b(int a,int b);

int min_a_b(int a,int b);

struct dynamic_array* path_intesection(struct dynamic_array* p1,struct dynamic_array* p2);

struct dynamic_array* path_union(struct dynamic_array* p1,struct dynamic_array* p2);

int mini_a_bmax(struct graph_t* G, struct graph_t *graph_player, int maxminplayer, int depth, int alpha, int beta,enum color_t id,int M);

struct move_t best_move(struct graph_t *graph_player,enum color_t id, int M,struct dynamic_array* inter);

#endif
