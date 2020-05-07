#ifndef _PATH_H_
#define _PATH_H_


struct path{

  size_t *array;
  size_t size;
  size_t capacity;
};


struct path *empty__path();

void realloc__path(struct path *p);

void add__to_path(struct path *p, size_t n);

void free__path(struct path *p);

#endif
