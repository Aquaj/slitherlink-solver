#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "map.h"

struct map* map_init(int n, int m){
  struct map* my_map = malloc(sizeof(struct map));
  my_map->points = malloc((n+1)*sizeof(struct point*));
  for(int i=0; i<m; i++){
    my_map->points[i] = malloc((m+1)*sizeof(struct point));
  }

  my_map->edges_h = malloc((n+1)*sizeof(struct point*));
  for(int i=0; i<m; i++){
    my_map->edges_h[i] = malloc((m)*sizeof(struct point));
  }

  my_map->edges_v = malloc((n)*sizeof(struct point*));
  for(int i=0; i<m; i++){
    my_map->edges_v[i] = malloc((m+1)*sizeof(struct point));
  }

  my_map->squares = malloc((n)*sizeof(struct point*));
  for(int i=0; i<m; i++){
    my_map->squares[i] = malloc((m)*sizeof(struct point));
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

void map_fill(struct map* my_map, int x, int y){
  struct graph* my_graph = graph_init();

  generate_loop(my_graph, my_map);

  graph_print(my_graph);
}
