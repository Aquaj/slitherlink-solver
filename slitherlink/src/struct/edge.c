#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "edge.h"

int is_edge_drawn(struct map *my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    return is_drawn_point(my_map, my_edge, EAST);
  }
  else{
    return is_drawn_point(my_map, my_edge, SOUTH);
  }
}

int is_edge_crossed(struct map *my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    return is_crossed_point(my_map, my_edge, EAST);
  }
  else{
    return is_crossed_point(my_map, my_edge, SOUTH);
  }
}

struct coord get_edge(struct coord my_square, enum orientation my_ori){
  struct coord my_edge;
  int i = my_square.x;
  int j = my_square.y;

  switch(my_ori){
    case NORTH:
      my_edge.x = i;
      my_edge.y = j;
    break;
    case EAST:
      my_edge.x = i;
      my_edge.y = j+1;
    break;
    case SOUTH:
      my_edge.x = i+1;
      my_edge.y = j;
    break;
    case WEST:
      my_edge.x = i;
      my_edge.y = j;
    break;
    default:
      assert(NULL);
    break;
  }

  return my_edge;
}
