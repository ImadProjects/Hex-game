/*! \file path.h                                                                                                                            
 * \brief path compution basic functions                                                                                                                 
 *                                                                                                                                                                                                                                                                         
 * \include path.c                                                                                                                                                                                                                                               
 */
#ifndef _PATH_H_
#define _PATH_H_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "dynamic_array.h"
#include "path.h"

/**
 * @brief function thath finds the minimum distance in the array distance depending on 
 * visited vertisec in the array selected
 * 
 * @param distance 
 * @param selected 
 * @param num_vertices 
 * @return int 
 */
int find_min_distance(int *distance, int *selected, int num_vertices);

/**
 * @brief finds the intersection of two paths
 * 
 * @param p1 
 * @param p2 
 * @return struct dynamic_array* 
 */
struct dynamic_array *path_intesection(struct dynamic_array *p1, struct dynamic_array *p2);

/**
 * @brief find the union of two paths
 * 
 * @param p1 
 * @param p2 
 * @return struct dynamic_array* 
 */
struct dynamic_array *path_union(struct dynamic_array *p1, struct dynamic_array *p2);

/**
 * @brief finds the shortest path to the source src
 * 
 * @param G 
 * @param M 
 * @param src 
 * @param color 
 * @return struct dynamic_array* 
 */
struct dynamic_array *djikstra(struct graph_t *G, size_t M, int src, enum color_t color);

/**
 * @brief calculate de score of the path by verifying if the box is free
 * 
 * @param path 
 * @param G 
 * @return int 
 */
int path_score(struct dynamic_array *path, struct graph_t *G);

/**
 * @brief calculate the quality of the path as the diffrence between enemy's shortest path score
 * and the player's shortest path score 
 * 
 * @param G 
 * @param M 
 * @param color 
 * @return int 
 */
int path_quality(struct graph_t *G, int M, int color);

#endif
