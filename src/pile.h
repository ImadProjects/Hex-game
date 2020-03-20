#ifndef PILE_H
#define PILE_H

#include <stdio.h>

struct pile{
  int size;
  int* t;
};

struct pile* pile_vide(int n);

void pile_free(struct pile* p);

void empiler(struct pile* p, int n);

int depiler(struct pile* p);

#endif // PILE_H
