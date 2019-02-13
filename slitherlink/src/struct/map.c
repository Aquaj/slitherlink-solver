#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "map.h"

struct map* map_init(int n, int m){
  struct map* my_map = malloc(sizeof(struct map));
  my_map->points = malloc((n+1)*sizeof(char*));
  for(int i=0; i<m+1; i++){
    my_map->points[i] = calloc((m+1),sizeof(char));
  }

  my_map->n = n;
  my_map->m = m;

  return my_map;
}

struct coord neighbor(struct map* my_map, struct coord my_point, enum orientation my_ori){
  int x = my_point.x;
  int y = my_point.y;
  struct coord my_neighbor;
  my_neighbor.x = -1;
  my_neighbor.y = -1;
  switch(my_ori){
    case NORTH:
      if(x==0){
        return my_neighbor;
      }
      my_neighbor.x = x-1;
      my_neighbor.y = y;
      return my_neighbor;
    break;
    case EAST:
      if(y==my_map->m){
        return my_neighbor;
      }
      my_neighbor.x = x;
      my_neighbor.y = y+1;
      return my_neighbor;
    break;
    case SOUTH:
      if(x==my_map->n){
        return my_neighbor;
      }
      my_neighbor.x = x+1;
      my_neighbor.y = y;
      return my_neighbor;
    break;
    case WEST:
      if(y==0){
        return my_neighbor;
      }
      my_neighbor.x = x;
      my_neighbor.y = y-1;
      return my_neighbor;
    break;
    default:
      assert(NULL);
    break;
  }
}
/*
void map_fill(struct map* my_map, struct graph* my_graph){
  generate_loop(my_map, my_graph);

  graph_print(my_graph);
}
*/
/*
// Fill points from parsed grid
void map_fill_points(struct map* my_map, struct grid* my_grid){
  struct coord my_square_coord;
  for(int i=0; i<my_map->n; i++){
    for(int j=0; j<my_map->m; j++){
      my_square_coord.x = i;
      my_square_coord.y = j;
      int my_square_value = my_map->squares[i][j].value;
      set_square_points(my_map, my_square_coord, my_square_value);
    }
  }
}
*/
void map_draw_line(struct map* my_map, struct coord first, struct coord second){
  int x = first.x > second.x;
  int y = first.y > second.y;

  if(first.x == second.x){
    if(!y){
      draw_line(my_map, first, second, EAST);
    }
    else{
      draw_line(my_map, first, second, WEST);
    }
  }

  else if(first.y == second.y){
    if(!x){
      draw_line(my_map, first, second, SOUTH);
    }
    else{
      draw_line(my_map, first, second, NORTH);
    }
  }
}

void map_draw_square(struct map* my_map){
  struct coord first, second;
  first.x = 0;
  first.y = 0;
  second.x = 0;
  second.y = my_map->m;
  map_draw_line(my_map, first, second);

  first.x = 0;
  first.y = my_map->m;
  second.x = my_map->n;
  second.y = my_map->m;
  map_draw_line(my_map, first, second);

  first.x = my_map->n;
  first.y = my_map->m;
  second.x = my_map->n;
  second.y = 0;
  map_draw_line(my_map, first, second);

  first.x = my_map->n;
  first.y = 0;
  second.x = 0;
  second.y = 0;
  map_draw_line(my_map, first, second);
}

void map_loop_init(struct map* my_map){
  map_draw_square(my_map);
}
