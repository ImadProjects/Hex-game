/*! \file dynamic_array.h                                                                                                                            
 * \brief data structure implementation for a dynamic array                                                                                                               
 *                                                                                                                                                                                                                                                                         
 * \include dynamic_array.c                                                                                                                                                                                                                                               
 */
#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "graph_aux.h"

#define INFINIT 100000

/**
 * @brief dynamic array data structure
 * 
 */
struct dynamic_array
{

  size_t *array;
  size_t size;
  size_t capacity;
};

/**
 * @brief allocates an empty array data structure
 * 
 * @return struct dynamic_array* 
 */
struct dynamic_array *empty__dynamic_array();

/**
 * @brief realloc dynamic structure if size == capacity
 * 
 */
void realloc__dynamic_array(struct dynamic_array *p);

/**
 * @brief add number to dynamic array
 * 
 * @param p 
 * @param n 
 */
void add__to_dynamic_array(struct dynamic_array *p, size_t n);

/**
 * @brief frees the dynamic array allocated in the
 * memory
 * 
 * @param p 
 */
void free__dynamic_array(struct dynamic_array *p);
#endif
