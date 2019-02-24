#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "map.h"

struct grid* grid_init(int n, int m){
  struct grid* my_grid = malloc(sizeof(struct grid));
  my_grid->squares = malloc((n)*sizeof(char*));
  for(int i=0; i<m; i++){
    my_grid->squares[i] = calloc((m),sizeof(char));
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      my_grid->squares[i][j] = 'N';
    }
  }

  my_grid->n = n;
  my_grid->m = m;

  return my_grid;
}

void grid_fill(struct map* my_map, struct grid* my_grid){
  struct coord north_edge;
  struct coord east_edge;
  struct coord south_edge;
  struct coord west_edge;
  struct coord my_square;
  int value = 0;
  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      my_square.x = i;
      my_square.y = j;
      north_edge = get_edge(my_square, NORTH);
      east_edge = get_edge(my_square, EAST);
      south_edge = get_edge(my_square, SOUTH);
      west_edge = get_edge(my_square, WEST);
      value = is_edge_drawn(my_map, north_edge, 1) + is_edge_drawn(my_map, east_edge, 0) + is_edge_drawn(my_map, south_edge, 1) + is_edge_drawn(my_map, west_edge, 0);
      sprintf(&my_grid->squares[i][j], "%d", value);
    }
  }
}


// Change to characters
void grid_remove_values(struct grid* my_grid){
  assert(my_grid);
  int zeros = 0;
  int ones = 0;
  int twos = 0;
  int threes = 0;

  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      switch(my_grid->squares[i][j]){
        case '0':
          zeros++;
          if(zeros == 6){
            my_grid->squares[i][j] = 'N';
          }
          else if(zeros > 3){
            zeros = 0;
          }
        break;
        case '1':
          ones++;
          if(ones == 3){
            my_grid->squares[i][j] = 'N';
          }
          else if(ones > 3){
            ones = 0;
          }
        break;
        case '2':
          twos++;
          if(twos == 2){
            my_grid->squares[i][j] = 'N';
          }
          else if(twos > 2){
            twos = 0;
          }
        break;
        case '3':
          threes++;
          if(threes == 4){
            my_grid->squares[i][j] = 'N';
          }
          else if(threes > 4){
            threes = 0;
          }
        break;
        default:
          assert(NULL);
        break;
      }
    }
  }
}
