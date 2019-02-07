#include <stdio.h>
#include <stdlib.h>

#define M 34
#define N 21



int main(int argc, char * argv[])
{
  //bord haut +
  printf("╔");
  for(int i = 0 ; i<M+2 ; ++i)
    printf("═");
  printf("╗\n");

  //bord haut
  printf("║┌");
  for(int i = 0 ; i<M ; ++i)
    printf("─");
  printf("┐║\n");




  //affichage du jeu
  for(int j = 0 ; j<N ; ++j){
    printf("║│");
    for(int i = 0; i<M; ++i)
      printf(" ");
    printf("│║\n");
  }



  //bord bas
  printf("║└");
  for(int i = 0 ; i<M ; ++i)
    printf("─");
  printf("┘║\n");

  //bord bas+
  printf("╚");
  for(int i = 0 ; i<M+2; ++i)
    printf("═");
  printf("╝\n");
}
