#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 10

int addHorizontalEdge(char left, char middle, char right){
  printf("%c", left);
  for(int i = 0 ; i<M-2 ; ++i)
    printf("%c", middle);
  printf("%c\n", right);
}

int main(int argc, char * argv[])
{
  //bord haut +
  // /!\ VERIFIER POURQUOI CA MARCHE PAS SI ON RENTRE LE CODE ASCII
  addHorizontalEdge(╔, ═, ╗);

  //bord haut
  printf("┌");
  for(int i = 0 ; i<M-2 ; ++i)
    printf("─");
  printf("┐\n");

  //affichage du jeu


  //bord bas
  printf("└");
  for(int i = 0 ; i<M-2 ; ++i)
    printf("─");
  printf("┘\n");

  //bord bas+
  printf("╚");
  for(int i = 0 ; i<M-2 ; ++i)
    printf("═");
  printf("╝\n");

/*
  for(int i =100 ; i < 300 ; ++i){
    printf("%d = %c\n", i, i);
  }
  PREUVE QUE CA MARCHE PAS SUR LE TERMINAL
  */
}
