#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10
#define N 10

//METTRE UN GENERATEUR AU PIF POUR TESTER

void show_help(){
  printf("Usage: slitherlink [-a|-o FILE|-v|-V|-h] FILE...\n");
  printf("       slitherlink -g[SIZE] [-u|-o FILE|-v|-V|-h] \n");
  printf("Solve or generate slitherlink grids of variable size \n\n");
  printf(" -g[NxM],--generate[=NxM] generate a grid of size NxM (default:8x8) \n");
  printf(" -a,--all                 search for all possible solutions \n");
  printf(" -u,--unique              generate a grid with unique solution \n");
  printf(" -o FILE,--output FILE    write result to FILE \n");
  printf(" -v,--verbose             verbose output \n");
  printf(" -V,--version             display version and exit \n");
  printf(" -h,--help                display this help\n\n");
}

void generate_grid(int NN, int MM){
  printf("to do\n");
}

int main(int argc, char ** argv)
{

  for(int i=0; i<argc; ++i){
    if(strcmp (argv[i], "-h")){
      show_help();
    }
  }


  if(N<1 || M<1){
    printf("The size of the grid must be over 1x1.\n");
    return 1;
  }

}
