#include <stdio.h>
#include <assert.h>

#include "../solver/solver.h"
#include "../parser/parser.h"

int main(){
  int n=10;
  int m=10;
/*
  struct grid* my_grid = parse();
  n = my_grid->n;
  m = my_grid->m;
*/
  struct map* my_map = map_init(n,m);
  struct grid* my_grid = grid_init(n,m);

  draw_loop(my_map, my_grid, 50);

  draw_all_values(my_map, my_grid);

  remove_values(my_grid);

  print_grid(my_map, my_grid, 1);

  map_free(my_map);
  my_map = map_init(n,m);

  solve(my_map, my_grid);

  map_free(my_map);
  grid_free(my_grid);
}
