#include "dynamic_array.h"

struct dynamic_array *empty__dynamic_array()
{

  struct dynamic_array *p = malloc(sizeof(struct dynamic_array));
  p->array = malloc(sizeof(size_t));
  p->capacity = 1;
  p->size = 0;

  return p;
}

void realloc__dynamic_array(struct dynamic_array *p)
{

  if (p->capacity == 0)
  {
    p->array = malloc(2 * sizeof(size_t));
    p->capacity = 2;
  }

  else if (p->capacity == p->size)
  {
    p->array = realloc(p->array, 2 * p->capacity * sizeof(size_t));
    p->capacity = 2 * p->capacity;
  }
}

void add__to_dynamic_array(struct dynamic_array *p, size_t n)
{

  realloc__dynamic_array(p);
  p->array[p->size] = n;
  p->size++;
}

void free__dynamic_array(struct dynamic_array *p)
{

  free(p->array);
  free(p);
}

