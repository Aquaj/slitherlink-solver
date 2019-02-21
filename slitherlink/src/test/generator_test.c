#include <stdio.h>

#include "../generator/generator.h"

int main(){
  struct map* my_map = map_init(20,20);
  struct grid* my_grid = grid_init(20,20);

  draw_loop(my_map, my_grid);

  draw_all_values(my_map, my_grid);

  print_grid(my_map, my_grid, 1);
}
