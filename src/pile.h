/*! \file pile.h                                                                                                                            
 * \brief data structure to fill and empty an array from one side                                                                                                                 
 *                                                                                                                                                                                                                                                                         
 * \include pile.c                                                                                                                                                                                                                                               
 */
#ifndef PILE_H
#define PILE_H

#include "graph.h"
#include <stdio.h>

struct pile
{
  int size;
  int *t;
  int capacity;
};

/**
 * @brief creates an empty stack
 * 
 * @return struct pile* 
 */

struct pile *pile_vide();

/**
 * @brief liberates the stack
 * 
 * @param p 
 */
void pile_free(struct pile *p);

/**
 * @brief adds an element on the top of the stack
 * 
 * @param p 
 * @param n 
 */
void empiler(struct pile *p, int n);

/**
 * @brief emoves and returns the element on the top of the stack
 * 
 * @param p 
 * @return int 
 */
int depiler(struct pile *p);

/**
 * @brief returns 1 if the stack is empty, 0 otherwise
 * 
 * @param p 
 * @return int 
 */
int est_vide(struct pile *p);

/**
 * @brief returns the size of the graph
 * 
 * @param graph 
 * @return size_t 
 */
size_t size__graph_t(const struct graph_t *graph);

/**
 * @brief returns the width of the graph
 * 
 * @param graph 
 * @return size_t 
 */
size_t width__graph_t(const struct graph_t *graph);

/**
 * @brief returns the type of the graph
 * 
 * @param graph 
 * @return char 
 */
char type__graph_t(const struct graph_t *graph);

#endif // PILE_H
