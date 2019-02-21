#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "edge.h"

int is_edge_empty(struct map *my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    return is_empty_point(my_map, my_edge, EAST);
  }
  else{
    return is_empty_point(my_map, my_edge, SOUTH);
  }
}

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

void empty_edge(struct map* my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    set_empty_point(my_map, my_edge, EAST);
  }
  else{
    set_empty_point(my_map, my_edge, SOUTH);
  }
}

void draw_edge(struct map* my_map, struct coord my_edge, int is_horizontal){
  if(is_horizontal){
    set_drawn_point(my_map, my_edge, EAST);
  }
  else{
    set_drawn_point(my_map, my_edge, SOUTH);
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

struct coord get_square_frm_point(struct coord my_point, enum orientation my_first_ori, enum orientation my_second_ori){
  struct coord my_square;
  int north_east = 0;
  int north_west = 0;
  int south_east = 0;
  int south_west = 0;

  switch(my_first_ori){
    case NORTH:
      north_east++;
      north_west++;
    break;
    case EAST:
      north_east++;
      south_east++;
    break;
    case SOUTH:
      south_east++;
      south_west++;
    break;
    case WEST:
      north_west++;
      south_west++;
    break;
    default:
      assert(NULL);
    break;
  }

  switch(my_second_ori){
    case NORTH:
      north_east++;
      north_west++;
    break;
    case EAST:
      north_east++;
      south_east++;
    break;
    case SOUTH:
      south_east++;
      south_west++;
    break;
    case WEST:
      north_west++;
      south_west++;
    break;
    default:
      assert(NULL);
    break;
  }

  if(north_east == 2){
    my_square.x = my_point.x-1;
    my_square.y = my_point.y;
  }
  else if(south_east == 2){
    my_square.x = my_point.x;
    my_square.y = my_point.y;
  }
  else if(south_west == 2){
    my_square.x = my_point.x;
    my_square.y = my_point.y-1;
  }
  else if(north_west == 2){
    my_square.x = my_point.x-1;
    my_square.y = my_point.y-1;
  }
  else{
    assert(NULL);
  }
  return my_square;
}

struct coord get_square_frm_square(struct coord my_square, enum orientation my_first_ori, enum orientation my_second_ori, int n, int m){
  struct coord returned_square;
  if(my_first_ori == my_second_ori){
    switch(my_first_ori){
      case NORTH:
        returned_square.x = my_square.x-1;
        returned_square.y = my_square.y;
      break;
      case EAST:
        returned_square.x = my_square.x;
        returned_square.y = my_square.y+1;
      break;
      case SOUTH:
        returned_square.x = my_square.x+1;
        returned_square.y = my_square.y;
      break;
      case WEST:
        returned_square.x = my_square.x;
        returned_square.y = my_square.y-1;
      break;
      default:
        assert(NULL);
      break;
    }
  }
  else{
    int north_east = 0;
    int north_west = 0;
    int south_east = 0;
    int south_west = 0;

    switch(my_first_ori){
      case NORTH:
        north_east++;
        north_west++;
      break;
      case EAST:
        north_east++;
        south_east++;
      break;
      case SOUTH:
        south_east++;
        south_west++;
      break;
      case WEST:
        north_west++;
        south_west++;
      break;
      default:
        assert(NULL);
      break;
    }

    switch(my_second_ori){
      case NORTH:
        north_east++;
        north_west++;
      break;
      case EAST:
        north_east++;
        south_east++;
      break;
      case SOUTH:
        south_east++;
        south_west++;
      break;
      case WEST:
        north_west++;
        south_west++;
      break;
      default:
        assert(NULL);
      break;
    }

    if(north_east == 2){
      returned_square.x = my_square.x-1;
      returned_square.y = my_square.y+1;
    }
    else if(south_east == 2){
      returned_square.x = my_square.x+1;
      returned_square.y = my_square.y+1;
    }
    else if(south_west == 2){
      returned_square.x = my_square.x+1;
      returned_square.y = my_square.y-1;
    }
    else if(north_west == 2){
      returned_square.x = my_square.x-1;
      returned_square.y = my_square.y-1;
    }
    else{
      assert(NULL);
    }

  }

  if(returned_square.x < 0 || returned_square.x >= n || returned_square.y < 0 || returned_square.y >= m){
    returned_square.x = -1;
    returned_square.y = -1;
  }
  return returned_square;
}

struct coord get_point_frm_square(struct coord my_square, int which){
  struct coord my_point;
  switch(which){
    case 0:
      my_point.x = my_square.x;
      my_point.y = my_square.y;
    break;
    case 1:
      my_point.x = my_square.x;
      my_point.y = my_square.y+1;
    break;
    case 2:
      my_point.x = my_square.x+1;
      my_point.y = my_square.y+1;
    break;
    case 3:
      my_point.x = my_square.x+1;
      my_point.y = my_square.y;
    break;
    default:
      assert(NULL);
    break;
  }

  return my_point;
}
