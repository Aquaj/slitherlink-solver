  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  #include "../generator/generator.h"
  #include "../struct/map.h"

  #define M 5
  #define N 5
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
  void generate_grid(int _verbose){
    struct map* my_map = generate_map(N,M);
    struct graph* my_graph = graph_init();
    draw_loop(my_map, my_graph);
    draw_all_values(my_map, my_graph);
    for(int i=0 ; i<N ; ++i){
      for(int j=0 ; j<M ; ++j){
          if(my_map->edges_h[i][j].state==DRAWN){
            printf("\x1b[7m %d \x1b[0m", my_map->squares[i][j].value);
          }else{
            printf(" %d ", my_map->squares[i][j].value);
          }

          if(my_map->squares[i][j].value==-1){}
            printf(" _ ");

      }
      printf("\n");

    }
    //printf("\n\nValeur du point (%d, %d) = %d\n", my_graph->start->x, my_graph->start->y,  my_map->squares[i][j].value);
    //printf("\n\nValeur du point (%d, %d) = %d\n", i, j,  my_map->squares[i][j].value);


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



  void show_board(){

  }




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

    /* if (!strcmp(argv[i], "-g[NxM]") || !strcmp(argv[i], "--version")){
      generate_grid();
      return EXIT_SUCCESS;
    } */





          /* AFFICHAGE */
          show_board();





            if (N<1 || M<1){
                    printf("The size of the grid must be over 1x1.\n");
                    return 1;
            }
  }
