#include <stdio.h>
#include <assert.h>

#include "point.h"

int point_deg(struct map* my_map, struct coord my_point, int drawn){
  if(drawn){
    return is_drawn_point(my_map, my_point, NORTH) + is_drawn_point(my_map, my_point, EAST) + is_drawn_point(my_map, my_point, SOUTH) + is_drawn_point(my_map, my_point, WEST);
  }
  return is_crossed_point(my_map, my_point, NORTH) + is_crossed_point(my_map, my_point, EAST) + is_crossed_point(my_map, my_point, SOUTH) + is_crossed_point(my_map, my_point, WEST);
}

void set_empty_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  struct coord next = neighbor(my_map, my_point, my_ori);

  assert(next.x != -1);

  set_point(my_map, my_point, my_ori, 2);
  set_point(my_map, next, (my_ori+2)%4, 2);
}

void set_drawn_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  struct coord next = neighbor(my_map, my_point, my_ori);

  assert(next.x != -1);

  set_point(my_map, my_point, my_ori, 1);
  set_point(my_map, next, (my_ori+2)%4, 1);
}

void set_crossed_point(struct map* my_map, struct coord my_point, enum orientation my_ori){
  struct coord next = neighbor(my_map, my_point, my_ori);

  assert(next.x != -1);

  set_point(my_map, my_point, my_ori, 0);
  set_point(my_map, next, (my_ori+2)%4, 0);
}

void set_point(struct map* my_map, struct coord my_point, enum orientation my_ori, int drawn){
  assert(my_map);

  int i = my_point.x;
  int j = my_point.y;

  char mask;
  char aff = 0x00; // 00 EMPTY

  if(drawn == 0){
    aff = 0x02; // 10 CROSSED
  }
  else if(drawn == 1){
    aff = 0x03; // 11 DRAWN
  }

  int shift=0;

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

  my_map->points[i][j] = my_map->points[i][j] & ~mask;

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
  tmp = tmp & 0x03;

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
