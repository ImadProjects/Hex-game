#include "alltests.h"
#include <stdio.h>

#define N_GRAPH 9
#define N_PILE 7
#define N_PATH 6
#define N_TR 15
#define N_SYS 6
#define N_GAUSS 2
#define N_RES 2
#define N_JOUEUR 2

void recap_test(char *s, int n, int expected)
{
  if (n == expected)
  {
    printf("\033[0;32m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n", s, n, expected);
    printf("\033[0m");
  }
  else
  {
    printf("\033[0;31m");
    printf("========TESTS SUR %s: %d/%d REUSSIS=======\n", s, n, expected);
    printf("\033[0m");
  }
}

int main(void)
{
  recap_test("LE GRAPHE", test_graph(), N_GRAPH);
  recap_test("LA PILE", test_pile(), N_PILE);
  recap_test("IS_WINNING", test_pathfinding(), N_PATH);
  recap_test("LES GRAPHES TRIANGULAIRES", test_tr(), N_TR);
  recap_test("LA GENERATION DU SYSTEME DE RESISTANCES", test_sys(), N_SYS);
  recap_test("LES PIVOTS DE GAUSS", test_gauss(), N_GAUSS);
  recap_test("DES CALCULS D'INTENSITES POUR UN GRAPHE GAGNANT/PERDANT", test_res(), N_RES);
  recap_test("LE CHOIX DE LA BONNE CASE", test_joueur_resistances(), N_JOUEUR);
  recap_test("test de path add realloc empty", test_all_array(), 3);
  recap_test("test de minimax", test_minimax(), 3);
  recap_test("test de path score", test_path_score(), 1);
  recap_test("test de graph minimax", test_graph_minimax(), 3);

  //  test_hexa();
  return 0;
}
//  printf("\033[00m");
// printf("\033[36m");
