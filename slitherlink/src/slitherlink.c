#include <stdio.h>
#include <stdlib.h>

#include "generator/generator.h"
#include "struct/map.h"
#include "generator/loop.h"
#include "solver/solver.h"

int main(){
  int N = 7;
  int M = 7;
  struct map* my_map = map_init(N,M);
  struct grid* my_grid = grid_init(N,M);

  draw_loop(my_map);

  draw_all_values(my_map, my_grid);

  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      printf("Point %d %d :", i,j);
      print_bit(my_map->points[i][j]);
    }
  }

  //remove_values(my_grid);

  print_grid(my_map, my_grid, 1);

}

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
