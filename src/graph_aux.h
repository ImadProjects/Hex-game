/*! \file graph_aux.h                                                                                                                            
 * \brief auxiliar functions for graph functions                                                                                                              
 *                                                                                                                                                                                                                                                                         
 * \include graph_aux.c                                                                                                                                                                                                                                               
 */
#include <stddef.h>
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>
#include <math.h>
#include "move.h"
#include "pile.h"
/**
 * @brief initialises the adjacency matrix of a non triangular graph_t
 * 
 * @param t 
 * @param c 
 * @param n 
 */
void assign_links(gsl_spmatrix *t, char c, int n);

/**
 * @brief initialises the adjacency matrix of a triangular graph_t
 * 
 * @param t 
 * @param c 
 * @param n 
 */

void assign_tr(gsl_spmatrix *t, char c, int n);

/**
 * @brief initialises the color matrix of a non triangular graph_t
 * 
 * @param o 
 * @param n 
 */

void assign_colors(gsl_spmatrix *o, int n);

/**
 * @brief initialises the color matrix of a triangular graph_t
 * 
 * @param o 
 * @param n 
 */
void assign_colors_tr(gsl_spmatrix *o, int n);

/**
 * @brief serves display purposes
 * 
 * @param o 
 * @param n 
 */
void color_print(const gsl_spmatrix *o, int n);

/**
 * @brief decides whether a box is taken or not
 * 
 * @param o 
 * @param n 
 * @return int 
 */
int is_taken(const gsl_spmatrix *o, int n);

/**
 * @brief decides if the game is over for a certain player color
 * 
 * @param g 
 * @param color 
 * @return int 
 */
int game_over(const struct graph_t *g, int color);

/**
 * @brief copies the graph into a new one
 * the graph must be freed after use
 * @param graph 
 * @return struct graph_t* 
 */
struct graph_t *copy_graph(const struct graph_t *graph);

/**
 * @brief copies a graph with and add the move on it and
 * returns it
 * the graph must be freed after use
 * @param graph 
 * @param move 
 * @return struct graph_t* 
 */
struct graph_t *copy_new_graph(struct graph_t *graph, struct move_t move);
