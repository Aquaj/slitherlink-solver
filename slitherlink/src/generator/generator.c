#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

void print_bit(char a){
  for (int i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  printf("\n");
}

void draw_loop(struct map* my_map){
  map_loop_init(my_map);
  //map_loop_distortion(my_map);
}

void draw_all_values(struct map* my_map, struct grid* my_grid){
  grid_fill(my_map, my_grid);
}

void remove_values(struct grid* my_grid){
  grid_remove_values(my_grid);
}

int main(){
  int N = 5;
  int M = 5;
  struct map* my_map = map_init(N,M);
  struct grid* my_grid = grid_init(N,M);

  draw_loop(my_map);

  draw_all_values(my_map, my_grid);

  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      printf("Point %d %d :", i,j);
      print_bit(my_map->points[i][j]);
    }
  }

  //remove_values(my_grid);

  print_grid(my_map, my_grid, 1);

}
