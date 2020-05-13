#include "../tst/alltests.h"
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

  recap_test("LE CHOIX DE LA BONNE CASE", test_joueur_resistances(), N_JOUEUR);
  //  test_hexa();
  test_ratio_hex();
  return 0;
}
//  printf("\033[00m");
// printf("\033[36m");
