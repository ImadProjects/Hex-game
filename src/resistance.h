/*! \file resistance.h                                                                                                                            
 * \brief function that calculates resistance and solve equations                                                                                                                
 *                                                                                                                                                                                                                                                                         
 * \include resistance.c                                                                                                                                                                                                                                               
 */
#ifndef _RESISTANCE_H_
#define _RESISTANCE_H_

#include <stdlib.h>
#include "move.h"
#include "pile.h"
#include "graph.h"
#include "graph_aux.h"
/**
 * @brief returns the value of the resistance between two neighboors vertices
 * 
 * @param g 
 * @param color 
 * @param i 
 * @param j 
 * @return double 
 */
double get_resistance(const struct graph_t *g, int color, int i, int j);
/**
 * @brief fills a matrix with a system consisting of meshes equations
 * 
 * @param g 
 * @param color 
 * @return double** 
 */
double **generate_meshes(const struct graph_t *g, int color);

/**
 * @brief liberates a matrix
 * 
 * @param mat 
 * @param n 
 */
void free_sys(double **mat, int n);

/**
 * @brief gauss pivots method to solve a linear system
 * 
 * @param mat 
 * @param b 
 * @param x 
 * @param n 
 */
void gauss(double **mat, double *b, double *x, int n);

/**
 * @brief returns the quotient of the total resistances of each player
 * 
 * @param g 
 * @param mec 
 * @return double 
 */
double get_ratio(const struct graph_t *g, struct move_t mec);

#endif
