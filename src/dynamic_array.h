#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_
#include <stdlib.h>
#include "graph.h"
#include "move.h"
#include "graph_aux.h"

#define INFINIT 100000

struct dynamic_array
{

  size_t *array;
  size_t size;
  size_t capacity;
};

struct dynamic_array *empty__dynamic_array();
void realloc__dynamic_array(struct dynamic_array *p);
void add__to_dynamic_array(struct dynamic_array *p, size_t n);
void free__dynamic_array(struct dynamic_array *p);
#endif
