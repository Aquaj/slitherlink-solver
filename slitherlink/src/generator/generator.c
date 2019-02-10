#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

struct map* generate_map(int n, int m){
  struct map* my_map = map_init(n,m);

  return my_map;
}

void draw_loop(struct map* my_map){
  int n = my_map->n;
  int m = my_map->m;

  // Random point
  int x=0;
  int y=0;

  map_fill(my_map, x, y);
}

int main(){
  struct map* my_map = map_init(3,3);

  draw_loop(my_map);
}
