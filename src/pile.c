#include "pile.h"
#include <stdlib.h>

struct pile* pile_vide(int n){
  struct pile* p = malloc(sizeof(struct pile));
  int* tab = malloc(sizeof(int) * (n + 1));
  p->t = tab;
  p->size = 0;
  return p;
}
  
void pile_free(struct pile* p){
  free(p->t);
  free(p);
}

void empiler(struct pile* p, int n){
  p->t[p->size] = n;
  p->size++;
}    
  
int depiler(struct pile* p){
  if (p->size == 0){
    return -1;
  }
  p->size--;
  int res = p->t[p->size];
  return res;
}

int est_vide(struct pile* p){
  return p->size == 0;
}
