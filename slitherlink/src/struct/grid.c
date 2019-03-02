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

  int nb_zeros = 0;
  int nb_ones = 0;
  int nb_twos = 0;
  int nb_threes = 0;

  int perc_zeros = 100;
  int perc_ones = 10;
  int perc_twos = 10;
  int perc_threes = 50;

  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      switch(my_grid->squares[i][j]){
        case '0':
          nb_zeros++;
        break;
        case '1':
          nb_ones++;
        break;
        case '2':
          nb_twos++;
        break;
        case '3':
          nb_threes++;
        break;
        default:
          assert(NULL);
        break;
      }
    }
  }

  zeros = nb_zeros * perc_zeros / 100;
  ones = nb_ones * perc_ones / 100;
  twos = nb_twos * perc_twos / 100;
  threes = nb_threes * perc_threes / 100;


  int zeros_rem = 0;
  int ones_rem = 0;
  int twos_rem = 0;
  int threes_rem = 0;

  int enc_zeros = 0;
  int enc_ones = 0;
  int enc_twos = 0;
  int enc_threes = 0;

  while(zeros_rem < zeros || ones_rem < ones || twos_rem < twos || threes_rem < threes){
    for(int i=0; i<my_grid->n; i++){
      for(int j=0; j<my_grid->m; j++){
        switch(my_grid->squares[i][j]){
          case '0':
            enc_zeros++;
            if(enc_zeros == 5 && zeros_rem < zeros){
              my_grid->squares[i][j] = 'N';
              enc_zeros = 0;
              zeros_rem++;
            }
          break;
          case '1':
            enc_ones++;
            if(enc_ones == 5 && ones_rem < ones){
              my_grid->squares[i][j] = 'N';
              enc_ones = 0;
              ones_rem++;
            }
          break;
          case '2':
            enc_twos++;
            if(enc_twos == 5 && twos_rem < twos){
              my_grid->squares[i][j] = 'N';
              enc_twos = 0;
              twos_rem++;
            }
          break;
          case '3':
            enc_threes++;
            if(enc_threes == 5 && threes_rem < threes){
              my_grid->squares[i][j] = 'N';
              enc_threes = 0;
              threes_rem++;
            }
          break;
          case 'N':
          break;
          default:
            assert(NULL);
          break;
        }
      }
    }
  }
}
