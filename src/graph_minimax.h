/*! \file graph_minimax.h                                                                                                                            
 * \brief auxiliar functions for minimax functions                                                                                                              
 *                                                                                                                                                                                                                                                                         
 * \include graph_minimax.c                                                                                                                                                                                                                                               
 */
#ifndef _GRAPH_mini_a_bMAX_H
#define _GRAPH_mini_a_bMAX_H
#include "path.h"

/**
 * @brief returns the neighbours of a box in a position
 * @param graph 
 * @param position 
 * @return struct dynamic_array* 
 */
struct dynamic_array *neighbours(struct graph_t *graph, int position);

/**
 * @brief returns the greater number between a and b
 * @param a 
 * @param b 
 * @return int 
 */
int max_a_b(int a, int b);

/**
 * @brief return the lower number between a and b 
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int min_a_b(int a, int b);

/**
 * @brief a function that implements the min max algorithm. It decides
 * whether the player is winning or not
 * 
 * @param G 
 * @param graph_player 
 * @param maxminplayer 
 * @param depth 
 * @param alpha 
 * @param beta 
 * @param id 
 * @param M 
 * @return int 
 */
int minimax(struct graph_t *G, struct graph_t *graph_player, int maxminplayer, int depth, int alpha, int beta, enum color_t id, int M);

/**
 * @brief Compute the best move possible for a graph configuration
 * 
 * @param graph_player 
 * @param id 
 * @param M 
 * @param inter 
 * @return struct move_t 
 */
struct move_t best_move(struct graph_t *graph_player, enum color_t id, int M, struct dynamic_array *inter);
#endif
