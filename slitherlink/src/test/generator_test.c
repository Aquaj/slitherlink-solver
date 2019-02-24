#include <stdio.h>

#include "../generator/generator.h"

int main(){
  int n=5;
  int m=5;
  struct map* my_map = map_init(n,m);
  struct grid* my_grid = grid_init(n,m);

  draw_loop(my_map, my_grid, 10);

  draw_all_values(my_map, my_grid);

  print_grid(my_map, my_grid, 1);
}
