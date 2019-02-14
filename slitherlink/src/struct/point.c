#include <stdio.h>
#include <assert.h>

#include "point.h"
/*
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
*/
void set_drawn_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  struct coord next = neighbor(my_map, my_point, my_ori);
  enum orientation opposite = opposite_orientation(my_ori);

  assert(next.x != -1);

  set_point(my_map, my_point, my_ori, 1);
  set_point(my_map, next, opposite, 1);
}

void set_crossed_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  struct coord next = neighbor(my_map, my_point, my_ori);
  enum orientation opposite = opposite_orientation(my_ori);

  assert(next.x != -1);

  set_point(my_map, my_point, my_ori, 0);
  set_point(my_map, next, opposite, 0);
}

void set_point(struct map* my_map, struct coord my_point, enum orientation my_ori, int drawn){
  assert(my_map);

  int i = my_point.x;
  int j = my_point.y;

  char aff = 0x02; // 10 CROSSED
  if(drawn){
    aff = 0x03; // 11 DRAWN
  }

  int shift=0;

  switch(my_ori){
    case NORTH:
    break;
    case EAST:
      shift = 2;
    break;
    case SOUTH:
      shift = 4;
    break;
    case WEST:
      shift = 6;
    break;
    default:
      assert(NULL);
    break;
  }
  char tmp = my_map->points[i][j] >> shift;
  tmp = tmp | aff;
  tmp = tmp << shift;
  my_map->points[i][j] = my_map->points[i][j] | tmp;
}

int is_drawn_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  char aff = 0x03; // 11 DRAWN
  return is_point_aff(my_map, my_point, my_ori, aff);
}

int is_crossed_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  char aff = 0x02; // 10 CROSSED
  return is_point_aff(my_map, my_point, my_ori, aff);
}

int is_empty_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  char aff = 0x00; // 00 EMPTY
  return is_point_aff(my_map, my_point, my_ori, aff);
}

int is_point_aff(struct map* my_map, struct coord my_point, enum orientation my_ori, char aff){
  assert(my_map);

  int i = my_point.x;
  int j = my_point.y;
  char mask;
  int shift = 0;

  switch(my_ori){
    case NORTH:
      mask = 0x03;
    break;
    case EAST:
      mask = 0x0C;
      shift = 2;
    break;
    case SOUTH:
      mask = 0x30;
      shift = 4;
    break;
    case WEST:
      mask = 0xC0;
      shift = 6;
    break;
    default:
      assert(NULL);
    break;
  }

  char tmp = my_map->points[i][j] & mask;
  tmp = tmp >> shift;

  return tmp == aff;
}

void draw_line(struct map* my_map, struct coord first, struct coord second, enum orientation my_ori){
  assert(my_map);
  struct coord my_point;

  switch(my_ori){
    case NORTH:
      my_point.x = first.x;
      my_point.y = first.y;
      while(my_point.x > second.x){
        set_drawn_point(my_map, my_point, NORTH);
        my_point.x--;
      }
    break;
    case EAST:
      my_point.x = first.x;
      my_point.y = first.y;
      while(my_point.y < second.y){
        set_drawn_point(my_map, my_point, EAST);
        my_point.y++;
      }
    break;
    case SOUTH:
      my_point.x = first.x;
      my_point.y = first.y;
      while(my_point.x < second.x){
        set_drawn_point(my_map, my_point, SOUTH);
        my_point.x++;
      }
    break;
    case WEST:
      my_point.x = first.x;
      my_point.y = first.y;
      while(my_point.y > second.y){
        set_drawn_point(my_map, my_point, WEST);
        my_point.y--;
      }
    break;
    default:
      assert(NULL);
    break;
  }
}
