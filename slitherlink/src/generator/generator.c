#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

struct map* generate_map(int n, int m){
  struct map* my_map = map_init(n,m);

  return my_map;
}

void draw_loop(struct map* my_map, struct graph* my_graph){
  map_fill(my_map, my_graph);
}

void draw_all_values(struct map* my_map, struct graph* my_graph){
  map_fill_values(my_map, my_graph);
}

void remove_values(struct map* my_map){
  map_remove_values(my_map);
}
<<<<<<< HEAD
=======

void fill_points(struct map* my_map){
  map_fill_points(my_map);
}

int main(){
  struct map* my_map = generate_map(4,4);
  struct graph* my_graph = graph_init();

  draw_loop(my_map, my_graph);

  draw_all_values(my_map, my_graph);

  remove_values(my_map);

  fill_points(my_map);
}
>>>>>>> 1b93a248370bc1c6e92b63dc17037462d160761c
