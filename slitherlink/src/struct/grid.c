#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "map.h"

struct grid* grid_init(int n, int m){
  struct grid* my_grid = malloc(sizeof(struct grid));
  my_grid->squares = malloc((n)*sizeof(char*));
  for(int i=0; i<m; i++){
    my_grid->squares[i] = calloc((m),sizeof(char));
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
  int value = 0;
  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      north_edge.x = i;
      north_edge.y = j;
      east_edge.x = i;
      east_edge.y = j+1;
      south_edge.x = i+1;
      south_edge.y = j;
      west_edge.x = i;
      west_edge.y = j;
      value = is_edge_drawn(my_map, north_edge, 1) + is_edge_drawn(my_map, east_edge, 0) + is_edge_drawn(my_map, south_edge, 1) + is_edge_drawn(my_map, west_edge, 0);
      sprintf(&my_grid->squares[i][j], "%d", value);
    }
  }
}


// Change to characters
void grid_remove_values(struct grid* my_grid){
  assert(my_grid);
  int ones = 0;
  int twos = 0;
  int threes = 0;

  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      switch(my_grid->squares[i][j]){
        case 0:
          my_grid->squares[i][j] = 'N';
        break;
        case 1:
          ones++;
          if(ones < 3){
            my_grid->squares[i][j] = 'N';
          }
          else{
            ones = 0;
          }
        break;
        case 2:
          twos++;
          if(twos < 2){
            my_grid->squares[i][j] = 'N';
          }
          else{
            twos = 0;
          }
        break;
        case 3:
          threes++;
          if(threes < 4){
            my_grid->squares[i][j] = 'N';
          }
          else{
            threes = 0;
          }
        break;
      }
    }
  }
}
