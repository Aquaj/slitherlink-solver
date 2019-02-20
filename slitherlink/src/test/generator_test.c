#include <stdio.h>

#include "../generator/generator.h"

int main(){
  struct map* my_map = map_init(4,4);
  struct grid* my_grid = grid_init(4,4);

  draw_loop(my_map);

  draw_all_values(my_map, my_grid);

  print_grid(my_map, my_grid, 1);
}
