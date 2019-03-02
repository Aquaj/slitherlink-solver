#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generator/generator.h"
#include "struct/map.h"
#include "solver/solver.h"







/* to be done, had to leave cremi*/
int * pouet(int argc, char ** argv){
  static int array [2];
  array[0] = 7;
  array[1] = 7;
  return array;
  }








  // char _short_option = argv[1][1];
  // char _long_option = argv[1][2];
  // if (_short_option == 'g' || (_short_option == '-' && _long_option == 'g'))
  //   return EXIT_SUCCESS;

int main(int argc, char ** argv){
  int _verbose = 0;

  /* for verbose*/
  for (int i = 0; i<argc;++i){
    if  (!strcmp(argv[i], "-v") || !strcmp(argv[i], "--verbose"))
      _verbose = 1;
  }

  /* outputs help */
  if (argc==1 || !strcmp(argv[1], "-h")){
    show_help();
    return EXIT_SUCCESS;
  }

  /* outputs version*/
  if (!strcmp(argv[1], "-V") || !strcmp(argv[1], "--version")){
    show_version();
    return EXIT_SUCCESS;
  }

  /* outputs all possible solutions*/
  if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--all")){
    search_all_possible_solutions(_verbose);
    return EXIT_SUCCESS;
  }

  /* ouputs grid*/
  if (!strcmp(argv[1], "-u") || !strcmp(argv[1], "--unique")){
    generate_grid_unique(_verbose);
    return EXIT_SUCCESS;
  }

  if (!strcmp(argv[1], "-g")){
    int N;
    int M;
    if (argc > 2) {
      N = atoi(argv[2]);
      M = atoi(argv[3]);
    } else {
      N = 10;
      M = 10;
    }


    if (N<2 || M<2){
      printf("The size of the grid must be over 1x1.\n");
      return 1;
    }
    struct map* my_map = map_init(N,M);
    struct grid* my_grid = grid_init(N,M);

    draw_loop(my_map, my_grid, 15);

    //removed_square_all_values(my_map, my_grid);

    for(int i=0; i<my_map->n+1; i++){
      for(int j=0; j<my_map->m+1; j++){
        printf("Point %d %d :", i,j);
        print_bit(my_map->points[i][j]);
      }
    }
    //remove_values(my_grid);
    print_grid(my_map, my_grid, 1);


    return EXIT_SUCCESS;
  }

}
