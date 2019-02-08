#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define M 10
#define N 10
#define VERSION 0.1

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

//option -g[NxM],--generate[=NxM]
//generate a grid of size NxM (default:8x8)
void generate_grid(int NN, int MM, bool unique){
  //TODO
}

// option -a,--all
// search for all possible solutions
void search_all_possible_solutions(){
  //TODO
}

// option -u,--unique
// generate a grid with unique solution
void generate_grid_unique(){
  //TODO
}

// option -o FILE,--output FILE
// write result to FILE
void write_result_to_file(){
  //TODO
}
// option -v,--verbose
// verbose output
void verbose_output(){
  //TODO
}

void show_version(){
  printf("Version : %f\n", VERSION);
}



int main(int argc, char ** argv)
{

  for(int i=0; i<argc; ++i){
    if(!strcmp(argv[i], "-h")) show_help();

 if(!strcmp(argv[i], "-V") || !strcmp(argv[i], "--version")){
   show_version();
   }
  }


  if(N<1 || M<1){
    printf("The size of the grid must be over 1x1.\n");
    return 1;
  }

}
