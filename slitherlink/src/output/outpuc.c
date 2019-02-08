#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 5



int main(int argc, char * argv[])
{
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
