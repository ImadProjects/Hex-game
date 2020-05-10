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

struct pile *pile_vide();

void pile_free(struct pile *p);

void empiler(struct pile *p, int n);

int depiler(struct pile *p);

int est_vide(struct pile *p);

////// graph part //////

size_t size__graph_t(const struct graph_t *graph);

size_t width__graph_t(const struct graph_t *graph);

char type__graph_t(const struct graph_t *graph);

#endif // PILE_H
