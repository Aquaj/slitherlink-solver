#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 0

//METTRE UN GENERATEUR AU PIF POUR TESTER

int main(int argc, char * argv[])
{
  if(N<1 || M<1){
    printf("The size of the grid must be over 1x1.\n");
    return 1;
  }
  //bord haut +
  printf("╔");
  for(int i = 0 ; i<M*2+5 ; ++i)
    printf("═");
  printf("╗\n");

  //bord haut
  printf("║┌");
  for(int i = 0 ; i<M*2+3 ; ++i)
    printf("─");
  printf("┐║\n");




  //affichage du jeu
  printf("║│ .");
  for(int i = 0; i<M; ++i)
    printf("─.");
  printf(" │║\n");

  for(int j = 0 ; j<N ; ++j){
    printf("║│ ");
    int i;
    printf("│");
    for(i=0; i<M; ++i)
      printf("%d│", i);
    printf(" │║");
    printf("\n");
    printf("║│ .");
    for(int i = 0; i<M; ++i)
      printf("─.");
    printf(" │║\n");

  }



  //bord bas
  printf("║└");
  for(int i = 0 ; i<M*2+3 ; ++i)
    printf("─");
  printf("┘║\n");

  //bord bas+
  printf("╚");
  for(int i = 0 ; i<M*2+5; ++i)
    printf("═");
  printf("╝\n");
}
