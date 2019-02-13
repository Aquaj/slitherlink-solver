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
/*
void remove_values(struct map* my_map){
  map_remove_values(my_map);
}

void fill_points(struct map* my_map){
  map_fill_points(my_map);
}

void init_edges(struct map* my_map){
  //map_init_edges(my_map);
}
*/
int main(){
  struct map* my_map = map_init(4,4);
  struct grid* my_grid = grid_init(4,4);

  draw_loop(my_map);

  draw_all_values(my_map, my_grid);

  /*
  generate_grid(my_map, my_graph, 0);

  remove_values(my_map);

  fill_points(my_map);

  //init_edges(my_map);

  generate_grid(my_map, my_graph, 0);
  */
}
