#include <stdio.h>
#include <stdlib.h>

#include "map.h"

struct map* map_init(int n, int m);

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

  return my_map;
}

void map_fill(struct map* my_map, int x, int y){
  struct graph* my_graph = graph_init();

  struct node* start_node = malloc(sizeof(struct node));
  start_node->x = x;
  start_node->y = y;

  graph_start(my_graph, start_node);
  generate_loop(my_map, my_graph);
}
