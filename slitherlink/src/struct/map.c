#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "map.h"
#include "../output/output.h"

void print_bit(char a){
  for (int i = 0; i < 8; i++) {
      printf("%d", !!((a << i) & 0x80));
  }
  printf("\n");
}

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

void map_free(struct map* my_map){
  assert(my_map);
  int n = my_map->n;
  int m = my_map->m;

  for(int i=0; i<m+1; i++){
    free(my_map->points[i]);
  }
  free(my_map->points);

  free(my_map);
}

void map_copy(struct map* dest, struct map* src){
  assert(dest);
  assert(src);
  dest->n = src->n;
  dest->m = src->m;

  for(int i=0; i<src->n+1; i++){
    for(int j=0; j<src->m+1; j++){
      dest->points[i][j] = src->points[i][j];
    }
  }
}

void get_border_squares(struct map *my_map, char **border_squares){
  for(int i=0; i<my_map->n; i++){
    for(int j=0; j<my_map->m; j++){
      if(i==0 || i==my_map->n-1 || j==0 || j==my_map->m-1){
        border_squares[i][j] = 0x01;
      }
      else{
        border_squares[i][j] = 0x00;
      }
    }
  }
}

struct coord get_random_square(char **border_squares, int n, int m){
  int x,y;
  srand(time(0));
  struct coord my_square;
  int border_size = 0;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      border_size += (border_squares[i][j] == 0x01);
    }
  }

  int square_num = rand() % border_size;

  int count = 0;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(border_squares[i][j] == 0x01){
        count++;
        if(count > square_num){
          my_square.x = i;
          my_square.y = j;
          return my_square;
        }
      }
    }
  }
}

void map_remove_square(struct map *my_map, struct coord removed_square){
  struct coord my_edge;
  for(int i=0; i<4; i++){
    my_edge = get_edge(removed_square, i);
    if(is_edge_drawn(my_map, my_edge, (i+1)%2)){
      empty_edge(my_map, my_edge, (i+1)%2);
    }
    else if(is_edge_empty(my_map, my_edge, (i+1)%2)){
      draw_edge(my_map, my_edge, (i+1)%2);
    }
  }
}

int is_valid_border(struct map* my_map, struct coord my_square){
  struct coord my_point, my_edge;
  int edges=0;
  map_remove_square(my_map, my_square);

  // CASE | 2 |
  for(int i=0; i<4; i++){
    my_edge = get_edge(my_square, i);
    edges += is_edge_drawn(my_map, my_edge, (i+1)%2);
  }
  if(edges == 2){
    struct coord first;
    struct coord second;
    first = get_edge(my_square, NORTH);
    second = get_edge(my_square, SOUTH);
    if(is_edge_drawn(my_map, first, 1) && is_edge_drawn(my_map, second, 1)){
      map_remove_square(my_map, my_square);
      return 0;
    }
    first = get_edge(my_square, EAST);
    second = get_edge(my_square, WEST);
    if(is_edge_drawn(my_map, first, 0) && is_edge_drawn(my_map, second, 0)){
      map_remove_square(my_map, my_square);
      return 0;
    }
  }

  // All other cases
  edges = 0;
  for(int i=0; i<4; i++){
    my_point = get_point_frm_square(my_square, i);
    for(int j=0; j<4; j++){
      edges+=is_drawn_point(my_map, my_point, j);
    }
    if(edges > 2){
      map_remove_square(my_map, my_square);
      return 0;
    }
    edges = 0;
  }
  map_remove_square(my_map, my_square);
  return 1;
}

void update_border(struct map* my_map, char **border_squares, struct coord removed_square){
  int x = removed_square.x;
  int y = removed_square.y;
  struct coord new_square;
  int nx, ny;
  border_squares[x][y] = 0x03;

  for(int i=0; i<4; i++){
    for(int j=i; j<4; j++){
      if(i==j || ((j-i)%2)){
        new_square = get_square_frm_square(removed_square, i, j, my_map->n, my_map->m);
        nx = new_square.x;
        ny = new_square.y;
        if(nx != -1 && border_squares[nx][ny] != 0x03){
          border_squares[nx][ny] = 0x00;
          if(is_valid_border(my_map, new_square)){
            border_squares[nx][ny] = 0x01;
          }
        }
      }
    }
  }
}

void map_loop_distortion(struct map* my_map, struct grid *my_grid, int iter){
  int n = my_map->n;
  int m = my_map->m;
  char **border_squares = calloc(n,sizeof(char *));
  for(int i=0; i<m; i++){
      border_squares[i] = calloc(m, sizeof(char));
  }
  struct coord removed_square;
  get_border_squares(my_map, border_squares);
  for(int i=0; i<iter; i++){
    removed_square = get_random_square(border_squares, n, m);
    map_remove_square(my_map, removed_square);
    update_border(my_map, border_squares, removed_square);
  }

  for(int i=0; i<m; i++){
    free(border_squares[i]);
  }
  free(border_squares);
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
