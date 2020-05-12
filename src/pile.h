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

//creates an empty stack
struct pile *pile_vide();

//liberates the stack
void pile_free(struct pile *p);

//adds an element on the top of the stack
void empiler(struct pile *p, int n);

//removes and returns the element on the top of the stack
int depiler(struct pile *p);

//returns 1 if the stack is empty, 0 otherwise
int est_vide(struct pile *p);

////// graph part //////

size_t size__graph_t(const struct graph_t *graph);

size_t width__graph_t(const struct graph_t *graph);

char type__graph_t(const struct graph_t *graph);

#endif // PILE_H
