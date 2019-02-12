#include <stdio.h>
#include <assert.h>

#include "point.h"

void set_point(struct point *my_point, enum direction dir, int set){
  assert(my_point);

  switch(dir){
    case UR:
      my_point->UR = set;
    break;
    case UL:
      my_point->UL = set;
    break;
    case DR:
      my_point->DR = set;
    break;
    case DL:
      my_point->DL = set;
    break;
    default:
      assert(NULL);
    break;
  }
}

void set_square_points(struct map* my_map, struct coord my_square_coord, int my_square_value){
  int i = my_square_coord.x;
  int j = my_square_coord.y;
  int set = 0;

  switch(my_square_value){
    case -1:
      set = 7;
    break;
    case 0:
      set = 1;
    break;
    case 1:
      set = 3;
    break;
    case 2:
      set = 7;
    break;
    case 3:
      set = 6;
    break;
    default:
      assert(NULL);
    break;
  }

  set_point(&my_map->points[i][j], DR, set);
  set_point(&my_map->points[i][j+1], DL, set);
  set_point(&my_map->points[i+1][j+1], UL, set);
  set_point(&my_map->points[i+1][j], UR, set);
}
