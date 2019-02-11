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

int main(){
  struct map* my_map = generate_map(6,6);
  struct graph* my_graph = graph_init();

  draw_loop(my_map, my_graph);

  draw_all_values(my_map, my_graph);
}
