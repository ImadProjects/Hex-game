#include "alltests.h"
#include <stdio.h>

#define N_GRAPH 9
#define N_PILE 7
#define N_PATH 6
#define N_TR 15
#define N_SYS 4
#define N_GAUSS 2
#define N_RES 2

void recap_test(char* s, int n, int expected){
  if (n == expected){
    printf("\033[0;32m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n",s, n , expected);
    printf("\033[0m");
  }
  else{
    printf("\033[0;31m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n",s, n , expected);
    printf("\033[0m");
  }
}


int main(void){
  recap_test("LE GRAPHE", test_graph(), N_GRAPH);
  recap_test("LA PILE", test_pile(), N_PILE);
  recap_test("LE PATHFINDING", test_pathfinding(), N_PATH);
  recap_test("LE TRIANGLE", test_tr(), N_TR);
  recap_test("LA GENERATION DU SYSTEME", test_sys(), N_SYS);
  printf("\033[36m");
  printf("(promis je vais mettre ce test à jour)\n");
  printf("\033[00m");
  recap_test("LA RESOLUTION DU SYSTEME", test_gauss(), N_GAUSS);
  recap_test("CALCUL D'INTENSITE POUR UN GRAPHE GAGNANT/PERDANT", test_res(), N_RES);
  
  return 0;
}
