#include <stdio.h>
#include <assert.h>

#include "../solver/solver.h"

int main(){
  int n=6;
  int m=6;
  struct map* my_map = map_init(n,m);
  struct grid* my_grid = grid_init(n,m);

  draw_loop(my_map, my_grid, 10);

  draw_all_values(my_map, my_grid);

  remove_values(my_grid);

  print_grid(my_map, my_grid, 1);

  map_free(my_map);
  my_map = map_init(n,m);

  solve(my_map, my_grid);

  map_free(my_map);
  grid_free(my_grid);
}
