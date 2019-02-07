#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 10



int main(int argc, char * argv[])
{
  //bord haut +
  printf("╔");
  for(int i = 0 ; i<M-2 ; ++i)
    printf("═");
  printf("╗\n");

  //bord haut
  printf("║┌");
  for(int i = 0 ; i<M-4 ; ++i)
    printf("─");
  printf("┐║\n");




  //affichage du jeu






  //bord bas
  printf("║└");
  for(int i = 0 ; i<M-4 ; ++i)
    printf("─");
  printf("┘║\n");

  //bord bas+
  printf("╚");
  for(int i = 0 ; i<M-2 ; ++i)
    printf("═");
  printf("╝\n");
}
