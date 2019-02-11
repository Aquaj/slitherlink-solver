#include <stdio.h>
#include <assert.h>

#include "point.h"

void set_point(struct point *my_point, enum direction dir, int set){
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
  }
}

void set_square_points(struct map* my_map, struct coord my_square_coord, int my_square_value){
  int i = my_square_coord.x;
  int j = my_square_coord.y;

  switch(my_square_value){
    case -1:
      set_point(my_map->points[i,j], DR, 7);
      set_point(my_map->points[i,j+1], DL, 7);
      set_point(my_map->points[i+1,j+1], UL, 7);
      set_point(my_map->points[i+1,j], UR, 7);
    break;
    case 0:
      set_point(my_map->points[i,j], DR, 1);
      set_point(my_map->points[i,j+1], DL, 1);
      set_point(my_map->points[i+1,j+1], UL, 1);
      set_point(my_map->points[i+1,j], UR, 1);
    break;
    case 1:
      set_point(my_map->points[i,j], DR, 3);
      set_point(my_map->points[i,j+1], DL, 3);
      set_point(my_map->points[i+1,j+1], UL, 3);
      set_point(my_map->points[i+1,j], UR, 3);
    break;
    case 2:
      set_point(my_map->points[i,j], DR, 7);
      set_point(my_map->points[i,j+1], DL, 7);
      set_point(my_map->points[i+1,j+1], UL, 7);
      set_point(my_map->points[i+1,j], UR, 7);
    break;
    case 3:
      set_point(my_map->points[i,j], DR, 6);
      set_point(my_map->points[i,j+1], DL, 6);
      set_point(my_map->points[i+1,j+1], UL, 6);
      set_point(my_map->points[i+1,j], UR, 6);
    break;
    default:
      assert(NULL);
    break;
  }
}
