#include <dlfcn.h>
#include "graph.h"


int main()
{
  void * player1 = dlopen("install/player1.so",RTLD_NOW);
  return 0;
}
