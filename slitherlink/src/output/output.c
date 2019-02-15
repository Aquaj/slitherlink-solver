#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "output.h"

#define VERSION 0.01012


/* option -h
show the help section */
void show_help(){
  printf("Usage: slitherlink [-a|-o FILE|-v|-V|-h] FILE...\n");
  printf("       slitherlink -g[SIZE] [-u|-o FILE|-v|-V|-h] \n");
  printf("Solve or generate slitherlink grids of variable size \n\n");
  printf(" -g[NxM],--generate[=NxM] ");
  printf("generate a grid of size NxM (default:8x8) \n");
  printf(" -a,--all                 ");
  printf("search for all possible solutions \n");
  printf(" -u,--unique              ");
  printf("generate a grid with unique solution \n");
  printf(" -o FILE,--output FILE    write result to FILE \n");
  printf(" -v,--verbose             verbose output \n");
  printf(" -V,--version             display version and exit \n");
  printf(" -h,--help                display this help\n\n");
}

/* option -g[NxM],--generate[=NxM]
generate a grid of size NxM (default:8x8) */

void print_grid(struct map* my_map, struct grid* my_grid, int _verbose){
  int cpt = 0;

  printf("╔");
  for(int i = 0 ; i<my_grid->n*4+1 ; i++)
    printf("═");
  printf("╗\n");

  printf("║┌");
  for(int i = 0 ; i<my_grid->n*4-1 ; i++)
    printf("─");
  printf("┐║\n");


  for(int i=0 ; i<my_grid->n ; i++){
    printf("║");
    for(int j=0 ; j<my_grid->m+1 ; j++){

      struct coord my_edge;
      my_edge.x = i;
      my_edge.y = j;
      if(is_edge_drawn(my_map, my_edge, 0)){
        cpt++;
      }
      if(j!=my_grid->m){
        printf("│");
        if(my_grid->squares[i][j] == 'N'){
          if(cpt%2 == 1)
            printf("\x1b[7m _ \x1b[0m");
          if(cpt%2 == 0)
            printf(" _ ");
        } else {
          if(cpt%2 == 1)
            printf("\x1b[7m %c \x1b[0m", my_grid->squares[i][j]);
          if(cpt%2 == 0)
            printf(" %c ", my_grid->squares[i][j]);
        }


      }



    }

      printf("│║");

      printf("\n");
      printf("║├");
      for(int k = 0; k < my_grid->n*5-6 ; k++){
        if(k!=0 && k%4==0 && k != my_grid->n*5-6 )
          printf("┼");
        else if (k!=0)
          printf("─");
        }
      printf("─┤║");
      printf("\n");




  }

  printf("║└");
  for(int i = 0 ; i<my_grid->n*4-1 ; i++)
  if(i%4==0 && i!=0)
    printf("┴");
  else if (i!=0)
    printf("─");
  printf("─┘║\n");


  printf("╚");
  for(int i = 0 ; i<my_grid->n*4+1 ; i++)
    printf("═");
  printf("╝\n");




  if(_verbose == 1){
    //printf("┌");

struct coord my_square;

    for(int i = 0 ; i<my_grid->n+1 ; ++i){
      for(int j = 0 ; j<my_grid->m ; ++j){
        my_square.x = i;
        my_square.y = j;

        /* horizontal edges */
        if(is_edge_drawn(my_map, my_square, 1)){
          printf("    _ ");
        }else if(is_edge_crossed(my_map, my_square, 1)){
            printf("    x ");
        }else{
          printf("      ");
        }

      }
      printf("\n");
      for(int k = 0 ; k < my_grid->m+1 ; k++){
        my_square.y = k;

        if(i!=my_grid->m){
          /* vertical edges */
          if(is_edge_drawn(my_map, my_square, 0)){
            printf(" | ");
          }else if(is_edge_crossed(my_map, my_square, 0)){
              printf(" x ");
          }else{
            printf("   ");
          }
          /* calue of the square */
          printf(" %c ", my_grid->squares[i][k]);

        }

      }
      printf("\n");
    }
    //printf("┐\n");
  }


}

/* option -a,--all
search for all possible solutions */
void search_all_possible_solutions(int _verbose){
  //TODO
}

/* option -u,--unique
generate a grid with unique solution*/
void generate_grid_unique(int _verbose){
  //TODO
}

/* option -o FILE,--output FILE
write result to FILE */
void write_result_to_file(){
  //TODO
}
/* option -v,--verbose
verbose output */
void verbose_output(){
  //TODO
}

void show_version(){
  printf("Version : %f\n", VERSION);
}



/* A FAIRE

void show_board(){

}*/


// Completer .h
// Move main to output_test.c
/*
int main(int argc, char ** argv){
  int _verbose = 0;

  for (int i = 0; i<argc;++i){
    if  (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose")){
      _verbose = 1;
    }

    if (argc==1 || !strcmp(argv[1], "-h")){
      show_help();
      return EXIT_SUCCESS;
    }

    if (!strcmp(argv[1], "-V") || !strcmp(argv[1], "--version")){
      show_version();
      return EXIT_SUCCESS;
    }
    if (argc != 1){
      char _short_option = argv[1][1];
      char _long_option = argv[1][2];
      if (_short_option == 'g' ||
      (_short_option == '-' && _long_option == 'g')){
        generate_grid(_verbose);
        return EXIT_SUCCESS;
      }

      if (!strcmp(argv[1], "-a") ||
      !strcmp(argv[1], "--all")){
        search_all_possible_solutions(_verbose);
        return EXIT_SUCCESS;
      }

      if (!strcmp(argv[1], "-u") ||
      !strcmp(argv[1], "--unique")){
        generate_grid_unique(_verbose);
        return EXIT_SUCCESS;
      }






    }

  }

   if (!strcmp(argv[i], "-g[NxM]") || !strcmp(argv[i], "--version")){
  generate_grid();
  return EXIT_SUCCESS;
}




if (N<1 || M<1){
  printf("The size of the grid must be over 1x1.\n");
  return 1;
}
}
*/
