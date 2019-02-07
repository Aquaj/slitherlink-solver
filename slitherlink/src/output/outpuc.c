#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 10



int main(int argc, char * argv[])
{
  //bord haut +
  printf("╔");
  for(int i = 0 ; i<M*2+3 ; ++i)
    printf("═");
  printf("╗\n");

  //bord haut
  printf("║┌");
  for(int i = 0 ; i<M*2+1 ; ++i)
    printf("─");
  printf("┐║\n");




  //affichage du jeu
  for(int j = 0 ; j<N ; ++j){
    printf("║│ ");
    int i;
    for(i=0; i<M-1; ++i)
      printf("%d│", i);
    printf("%d", i);
    printf(" │║");
    printf("\n");
    printf("║│ ");
    for(int i = 0; i<M-1; ++i)
      printf("─.");
    printf("─");
    printf(" │║\n");

  }



  //bord bas
  printf("║└");
  for(int i = 0 ; i<M*2+1 ; ++i)
    printf("─");
  printf("┘║\n");

  //bord bas+
  printf("╚");
  for(int i = 0 ; i<M*2+3; ++i)
    printf("═");
  printf("╝\n");
}
