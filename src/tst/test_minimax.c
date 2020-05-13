#include "../path.h"
#include "../graph_minimax.h"
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

int test_find_min_distance()
{
  int distance[4] = {4, 5, 3, 2};
  int selected[4] = {0, 1, 0, 1};
  if (find_min_distance(distance, selected, 4) == 2)
    return 1;
  return 0;
}

int test_path_union()
{
  struct dynamic_array *a1 = empty__dynamic_array();
  add__to_dynamic_array(a1, 1);
  add__to_dynamic_array(a1, 2);
  add__to_dynamic_array(a1, 3);
  struct dynamic_array *a2 = empty__dynamic_array();
  add__to_dynamic_array(a2, 4);
  add__to_dynamic_array(a2, 5);
  add__to_dynamic_array(a2, 6);
  struct dynamic_array *b = path_union(a1, a2);
  for (size_t k = 0; k < 6; k++)
  {
    if (b->array[k] != k + 1)
    {
      free__dynamic_array(a1);
      free__dynamic_array(a2);
      free__dynamic_array(b);
      return 0;
    }
  }
  free__dynamic_array(a1);
  free__dynamic_array(a2);
  free__dynamic_array(b);
  return 1;
}

int test_path_intersection()
{
  struct dynamic_array *a1 = empty__dynamic_array();
  add__to_dynamic_array(a1, 1);
  add__to_dynamic_array(a1, 2);
  add__to_dynamic_array(a1, 3);
  add__to_dynamic_array(a1, 4);

  struct dynamic_array *a2 = empty__dynamic_array();
  add__to_dynamic_array(a2, 1);
  add__to_dynamic_array(a2, 2);
  add__to_dynamic_array(a2, 3);
  struct dynamic_array *b = path_intesection(a1, a2);
  for (size_t k = 0; k < 3; k++)
  {
    if (b->array[k] != k + 1)
    {
      free__dynamic_array(a1);
      free__dynamic_array(a2);
      free__dynamic_array(b);
      return 0;
    }
  }
  free__dynamic_array(a1);
  free__dynamic_array(a2);
  free__dynamic_array(b);
  return 1;
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

int test_path_score()
{
  struct graph_t *g = new__graph_t(4, 'h');
  struct dynamic_array *path = empty__dynamic_array();
  add__to_dynamic_array(path, 8);
  add__to_dynamic_array(path, 12);
  add__to_dynamic_array(path, 16);
  gsl_spmatrix_set(g->o, 1, 6, 1);
  gsl_spmatrix_set(g->o, 1, 7, 1);
  int sc = path_score(path, g);
  if (sc == 3)
  {
    free__graph_t(g);
    free__dynamic_array(path);
    return 1;
  }

  return 0;
  free__graph_t(g);
  free__dynamic_array(path);
}

int test_neighbours()
{
  struct graph_t *g = new__graph_t(4, 'h');
  gsl_spmatrix_set(g->o, 1, 6, 1);
  gsl_spmatrix_set(g->o, 1, 7, 1);
  struct dynamic_array *path = neighbours(g, 8);
  if (path->array[0] == 13 && path->array[1] == 12)
  {
    free__dynamic_array(path);
    free__graph_t(g);

    return 1;
  }
  free__dynamic_array(path);
  free__graph_t(g);
  return 0;
}

int test_max_a_b()
{
  int a = 1;
  int b = 2;
  if (max_a_b(a, b) == 2)
    return 1;
  return 0;
}

int test_min_a_b()
{
  int a = 1;
  int b = 2;
  if (min_a_b(a, b) == 1)
    return 1;
  return 0;
}

int test_minimax()
{
  if (test_path_union() && test_find_min_distance() && test_path_intersection())
    return 3;
  else if ((test_path_union() && test_find_min_distance() == 0 && test_path_intersection()) || (test_path_union() == 0 && test_find_min_distance() && test_path_intersection()) || (test_path_union() && test_find_min_distance() && test_path_intersection() == 0))
    return 2;
  else if ((test_path_union() == 0 && test_find_min_distance() == 0 && test_path_intersection()) || (test_path_union() == 0 && test_find_min_distance() && test_path_intersection() == 0) || (test_path_union() && test_find_min_distance() == 0 && test_path_intersection() == 0))
    return 1;
  return 0;
}

int test_graph_minimax()
{
  if (test_max_a_b() && test_neighbours() && test_min_a_b())
    return 3;
  else if ((test_max_a_b() && test_neighbours() == 0 && test_min_a_b()) || (test_max_a_b() == 0 && test_neighbours() && test_min_a_b()) || (test_max_a_b() && test_neighbours() && test_min_a_b() == 0))
    return 2;
  else if ((test_max_a_b() == 0 && test_neighbours() == 0 && test_min_a_b()) || (test_max_a_b() == 0 && test_neighbours() && test_min_a_b() == 0) || (test_max_a_b() && test_neighbours() == 0 && test_min_a_b() == 0))
    return 1;
  return 0;
}
