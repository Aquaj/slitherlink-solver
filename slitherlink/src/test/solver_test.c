#include <stdio.h>
#include <assert.h>

#include "../solver/solver.h"

int main(){
  struct map* my_map = map_init(4,4);
  struct grid* my_grid = grid_init(4,4);

  draw_loop(my_map, my_grid);

  draw_all_values(my_map, my_grid);

  print_grid(my_map, my_grid, 1);

  struct coord my_point;
  my_point.x = 0;
  my_point.y = 2;
  set_empty_point(my_map, my_point, EAST);
  set_drawn_point(my_map, my_point, SOUTH);
  my_point.x = 1;
  my_point.y = 2;
  set_drawn_point(my_map, my_point, SOUTH);
  my_point.x = 1;
  my_point.y = 3;
  set_drawn_point(my_map, my_point, NORTH);
  set_drawn_point(my_map, my_point, SOUTH);
  my_point.x = 2;
  my_point.y = 2;
  set_drawn_point(my_map, my_point, EAST);
  print_grid(my_map, my_grid, 1);
  draw_all_values(my_map, my_grid);
  print_grid(my_map, my_grid, 1);

  //remove_values(my_grid);

  solve(my_map, my_grid);
  print_grid(my_map, my_grid, 1);
/*
  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      printf("Point %d %d :", i,j);
      print_bit(my_map->points[i][j]);
    }
  }

  char mask = 0x03;
  print_bit(~mask);
*/
}
