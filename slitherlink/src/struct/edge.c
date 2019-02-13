#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "edge.h"

int is_edge_drawn(struct map *my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    return get_drawn_point(my_map, my_edge, EAST);
  }
  else{
    return get_drawn_point(my_map, my_edge, SOUTH);
  }
}
