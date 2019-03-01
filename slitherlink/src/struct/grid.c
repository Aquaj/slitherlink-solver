#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "map.h"

struct grid* grid_init(int n, int m){
  struct grid* my_grid = malloc(sizeof(struct grid));
  my_grid->squares = malloc((n)*sizeof(char*));
  for(int i=0; i<n; i++){
    my_grid->squares[i] = calloc((m),sizeof(char));
  }

  my_grid->n = n;
  my_grid->m = m;

  grid_clear(my_grid);

  return my_grid;
}

void grid_free(struct grid* my_grid){
  int n = my_grid->n;
  int m = my_grid->m;

  for(int i=0; i<n; i++){
    free(my_grid->squares[i]);
  }
  free(my_grid->squares);

  free(my_grid);
}

void grid_clear(struct grid* my_grid){
  int n = my_grid->n;
  int m = my_grid->m;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      my_grid->squares[i][j] = 'N';
    }
  }
}

void grid_copy(struct grid* dest, struct grid* src){
  assert(dest);
  assert(src);
  dest->n = src->n;
  dest->m = src->m;

  for(int i=0; i<src->n; i++){
    for(int j=0; j<src->m; j++){
      dest->squares[i][j] = src->squares[i][j];
    }
  }
}

char square_value(struct map* my_map, struct coord my_square){
  struct coord north_edge = get_edge(my_square, NORTH);
  struct coord east_edge = get_edge(my_square, EAST);
  struct coord south_edge = get_edge(my_square, SOUTH);
  struct coord west_edge = get_edge(my_square, WEST);

  int value = is_edge_drawn(my_map, north_edge, 1) + is_edge_drawn(my_map, east_edge, 0) + is_edge_drawn(my_map, south_edge, 1) + is_edge_drawn(my_map, west_edge, 0);
  return value + '0';
}

void grid_fill(struct map* my_map, struct grid* my_grid){
  struct coord my_square;

  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      my_square.x = i;
      my_square.y = j;
      my_grid->squares[i][j] = square_value(my_map, my_square);
    }
  }
}

void grid_remove_values(struct grid* my_grid){
  assert(my_grid);

  int n = my_grid->n;
  int m = my_grid->m;

  int zeros = 0;
  int ones = 0;
  int twos = 0;
  int threes = 0;

  int max_zeros = 2;//n*m
  int max_ones = 2;//n/6;
  int max_twos = 2;//n/8;
  int max_threes = 2;//n/4;


  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      switch(my_grid->squares[i][j]){
        case '0':
          zeros++;
          if(zeros < max_zeros){
            my_grid->squares[i][j] = 'N';
          }
          else{
            zeros=0;
          }
        break;
        case '1':
          ones++;
          if(ones < max_ones){
            my_grid->squares[i][j] = 'N';
          }
          else{
            ones = 0;
          }
        break;
        case '2':
          twos++;
          if(twos < max_twos){
            my_grid->squares[i][j] = 'N';
          }
          else{
            twos=0;
          }
        break;
        case '3':
          threes++;
          if(threes < max_threes){
            my_grid->squares[i][j] = 'N';
          }
          else{
            threes=0;
          }
        break;
        default:
          assert(NULL);
        break;
      }
    }
  }
}
