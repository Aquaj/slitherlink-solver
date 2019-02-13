#include <stdio.h>
#include <stdlib.h>
#include "../struct/map.h"
#include "../struct/point.h"

void print_bit(char a){
  for (int i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  printf("\n");
}

int main(){
  struct map *my_map = map_init(3,3);
  //set_drawn_point(struct map* my_map, struct coord my_point, enum direction my_dir)
  struct coord my_point;
  my_point.x = 0;
  my_point.y = 0;

  set_drawn_point(my_map, my_point, NORTH);
  print_bit(my_map->points[0][0]);
  set_drawn_point(my_map, my_point, EAST);
  print_bit(my_map->points[0][0]);
  set_drawn_point(my_map, my_point, SOUTH);
  print_bit(my_map->points[0][0]);
  set_drawn_point(my_map, my_point, WEST);
  print_bit(my_map->points[0][0]);

  char tmp = my_map->points[0][0] & 0x30;
  //tmp = tmp >> 4;

  printf("%d\n", tmp == 0x03);
  print_bit(tmp);



  return 0;
}
