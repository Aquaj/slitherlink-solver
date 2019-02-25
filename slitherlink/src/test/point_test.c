#include <stdio.h>
#include <stdlib.h>
#include "../struct/map.h"
#include "../struct/point.h"

int main(){
  struct map *my_map = map_init(3,3);
  //set_drawn_point(struct map* my_map, struct coord my_point, enum direction my_dir)
  struct coord my_point;
  my_point.x = 0;
  my_point.y = 0;

  //set_drawn_point(my_map, my_point, NORTH);
  print_bit(my_map->points[0][0]);
  set_drawn_point(my_map, my_point, EAST);
  print_bit(my_map->points[0][0]);
  print_bit(my_map->points[0][1]);
  set_crossed_point(my_map, my_point, SOUTH);
  print_bit(my_map->points[0][0]);
  print_bit(my_map->points[0][1]);
  printf("Drawn E%d\n", is_drawn_point(my_map, my_point, EAST));
  printf("Crossed E%d\n", is_crossed_point(my_map, my_point, EAST));
  printf("Drawn E%d\n", is_drawn_point(my_map, my_point, SOUTH));
  printf("Crossed E%d\n", is_crossed_point(my_map, my_point, SOUTH));

  my_point.x = 0;
  my_point.y = 1;
  printf("Drawn E%d\n", is_drawn_point(my_map, my_point, WEST));
  printf("Crossed E%d\n", is_crossed_point(my_map, my_point, WEST));
  //set_drawn_point(my_map, my_point, WEST);
  //print_bit(my_map->points[0][0]);

  return 0;
}
