#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "map.h"

struct map* map_init(int n, int m){
  struct map* my_map = malloc(sizeof(struct map));
  my_map->points = malloc((n+1)*sizeof(struct point*));
  for(int i=0; i<m+1; i++){
    my_map->points[i] = calloc((m+1),sizeof(struct point));
  }

  my_map->edges_h = malloc((n+1)*sizeof(struct edge*));
  for(int i=0; i<n+1; i++){
    my_map->edges_h[i] = malloc((m)*sizeof(struct edge));
  }

  my_map->edges_v = malloc((n)*sizeof(struct edge*));
  for(int i=0; i<n; i++){
    my_map->edges_v[i] = malloc((m+1)*sizeof(struct edge));
  }

  my_map->squares = malloc((n)*sizeof(struct square*));
  for(int i=0; i<n; i++){
    my_map->squares[i] = malloc((m)*sizeof(struct square));
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
    case UP:
      if(x==0){
        return my_neighbor;
      }
      my_neighbor.x = x-1;
      my_neighbor.y = y;
      return my_neighbor;
    break;
    case RIGHT:
      if(y==my_map->m){
        return my_neighbor;
      }
      my_neighbor.x = x;
      my_neighbor.y = y+1;
      return my_neighbor;
    break;
    case DOWN:
      if(x==my_map->n){
        return my_neighbor;
      }
      my_neighbor.x = x+1;
      my_neighbor.y = y;
      return my_neighbor;
    break;
    case LEFT:
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

void map_fill(struct map* my_map, struct graph* my_graph){
  generate_loop(my_map, my_graph);

  graph_print(my_graph);
}

void map_fill_values(struct map* my_map, struct graph* my_graph){
  for(int i=0; i<my_map->n; i++){
    for(int j=0; j<my_map->m; j++){
      my_map->squares[i][j].value = is_drawn(my_map->edges_h[i][j]) + is_drawn(my_map->edges_h[i+1][j]) + is_drawn(my_map->edges_v[i][j]) + is_drawn(my_map->edges_v[i][j+1]);
      printf("square [%d %d] : %d\n", i, j, my_map->squares[i][j].value);
    }
  }
}

void map_remove_values(struct map* my_map){
  assert(my_map);
  int ones = 0;
  int twos = 0;
  int threes = 0;

  for(int i=0; i<my_map->n; i++){
    for(int j=0; j<my_map->m; j++){
      switch(my_map->squares[i][j].value){
        case 0:
          my_map->squares[i][j].value = -1;
        break;
        case 1:
          ones++;
          if(ones < 3){
            my_map->squares[i][j].value = -1;
          }
          else{
            ones = 0;
          }
        break;
        case 2:
          twos++;
          if(twos < 2){
            my_map->squares[i][j].value = -1;
          }
          else{
            twos = 0;
          }
        break;
        case 3:
          threes++;
          if(threes < 4){
            my_map->squares[i][j].value = -1;
          }
          else{
            threes = 0;
          }
        break;
      }
      printf("new square [%d %d] : %d\n", i, j, my_map->squares[i][j].value);
    }
  }
}

void map_fill_points(struct map* my_map){
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

void map_init_edges(struct map* my_map);
