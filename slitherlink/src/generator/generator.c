#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

void draw_loop(struct map* my_map, struct grid* my_grid){
  map_loop_init(my_map);
  map_loop_distortion(my_map, my_grid, 200);
}

void draw_all_values(struct map* my_map, struct grid* my_grid){
  grid_fill(my_map, my_grid);
}

void remove_values(struct grid* my_grid){
  grid_remove_values(my_grid);
}
