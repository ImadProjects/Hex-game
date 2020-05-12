#include "path.h"
#include "graph_minimax.h"
#include <stdio.h>
#include <stdlib.h>

int test_empty_array()
{
  struct dynamic_array *array = empty__dynamic_array();
  if (array->capacity == 1 && array->size == 0)
  {
    free__dynamic_array(array);
    return 1;
  }
  free__dynamic_array(array);
  return 0;
}

int test_array_realloc()
{
  struct dynamic_array *array = empty__dynamic_array();
  array->size++;
  realloc__dynamic_array(array);
  if (array->capacity == 2)
  {
      free__dynamic_array(array);
      return 1;
    }
  free__dynamic_array(array);
  return 0;
}

int test_add_to_array()
{
  struct dynamic_array *array = empty__dynamic_array();
  add__to_dynamic_array(array, 1);
  if (array->size == 1 && array->array[0] == 1)
  {
    free__dynamic_array(array);
    return 1;
  }
  add__to_dynamic_array(array, 2);
  if (array->capacity == 2 && array->size == 2 && array->array[0] == 1 && array->array[1] == 2)
  {
    free__dynamic_array(array);
    return 1;
  }
  free__dynamic_array(array);
  return 0;
}

int test_all_array()
{
  if (test_add_to_array() && test_empty_array() && test_array_realloc())
    return 3;
  else if ((test_add_to_array() && test_empty_array() == 0 && test_array_realloc()) || (test_add_to_array() == 0 && test_empty_array() && test_array_realloc()) || (test_add_to_array() && test_empty_array() && test_array_realloc() == 0))
    return 2;
  else if ((test_add_to_array() == 0 && test_empty_array() == 0 && test_array_realloc()) || (test_add_to_array() == 0 && test_empty_array() && test_array_realloc() == 0) || (test_add_to_array() && test_empty_array() == 0 && test_array_realloc() == 0))
    return 1;
  return 0;
}