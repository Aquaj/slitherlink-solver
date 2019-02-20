#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

void print_bit(char a){
  for (int i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  printf("\n");
}

void draw_loop(struct map* my_map){
  map_loop_init(my_map);
  //map_loop_distortion(my_map);
}

void draw_all_values(struct map* my_map, struct grid* my_grid){
  grid_fill(my_map, my_grid);
}

void remove_values(struct grid* my_grid){
  grid_remove_values(my_grid);
}
