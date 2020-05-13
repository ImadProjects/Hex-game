/*! \file graph.h                                                                                                                            
 * \brief graph basic functions                                                                                                                 
 *                                                                                                                                                                                                                                                                         
 * \include graph.c                                                                                                                                                                                                                                               
 */
#ifndef _HEX_GRAPH_H_
#define _HEX_GRAPH_H_
#include "move.h"

#include <stdlib.h>
#include <gsl/gsl_spmatrix.h>

/*! \brief graph structure                                                                                                        
 */
struct graph_t
{

  size_t num_vertices; // Number of vertices in the graph

  gsl_spmatrix *t; // Sparse matrix of size n*n,
                   // t[i][j] == 1 means there is an edge from i to j
  gsl_spmatrix *o; // Sparse matrix of size 2*n, one line per player
                   // o[p][i] == 1 means that the vertex i is owned by p
};
/**
 * \fn struct graph_t *new__graph_t(int n, char c)
 *\brief  create a new graph of size n and of type c
 * @param n 
 * @param c 
 * @return struct graph_t* 
 */
struct graph_t *new__graph_t(int n, char c);

/**
 * \fn void free__graph_t(struct graph_t *g)
 * @brief the function frees the graph allocated in the memory
 * 
 * @param g 
 */
void free__graph_t(struct graph_t *g);

/**
 * \fn void print__mat(const struct graph_t *g)
 * @brief the function prints the adjacence matrix of g in terminal
 * 
 * @param g 
 */
void print__mat(const struct graph_t *g);

/**
 * \fn int coloriate__graph_t(struct graph_t *g, int color, struct move_t move)
 * @brief  the function coloriate the graph with the color "color" on the position "move"
 * 
 * @param g 
 * @param color 
 * @param move 
 * @return int 
 *  1 if the graph is coloriate
 *  else 0
 */
int coloriate__graph_t(struct graph_t *g, int color, struct move_t move);

/**
 * \fn void print_graph(const struct graph_t *g, char c)
 * @brief print the board in terminal
 * @param g 
 * @param c 
 */
void print_graph(const struct graph_t *g, char c);

/**
 * \fn void print_tr(const struct graph_t *g)
 * @brief prints the triangular graph in terminal
 * 
 * @param g 
 */
void print_tr(const struct graph_t *g);

/**
 * \fn int is_winning(const struct graph_t *g, int color, struct move_t move, char c)
 * @brief  returns 1 if the player with the color "color" wins 
 *         else returns 0
 * 
 * @param g 
 * @param color 
 * @param move 
 * @param c 
 * @return int 
 */
int is_winning(const struct graph_t *g, int color, struct move_t move, char c);
#endif // _HEX_GRAPH_H_
