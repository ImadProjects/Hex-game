#include "path.h"

struct path *empty__path(){
  
  struct path *p = malloc(sizeof(struct path));
  p->array = malloc(sizeof(size_t));
  p->capacity = 1;
  p->size = 0;

  return path;
}


void realloc__path(struct path *p){

  if(p->capacity == 0){
    p->array = malloc(2 * sizeof(size_t));
    p->capacity = 2;
  }

  else if(p->capacity == p->size){
    p->array = realloc(p->array, 2 * p->capacity * sizeof(size_t));
    p->capacity = 2 * p->capacity;
  }
}


void add__to_path(struct path *p, size_t n){

  realloc__path(p);
  p->array[p->size] = n;
  p->size++;
}

  
void free__path(struct path *p){

  free(p->array);
  free(p);
}
