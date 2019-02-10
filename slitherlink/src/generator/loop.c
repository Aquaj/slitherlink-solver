#include <stdio.h>
#include <stdlib.h>

#include "loop.h"

void priority_ori(struct coord first, struct coord second, enum orientation *prio_arr){
  int x = first.x > second.x;
  int y = first.y > second.y;

  switch(x){
    case 1:
      prio_arr[0] = UP;
      prio_arr[2] = DOWN;
    break;
    case 0:
      prio_arr[0] = DOWN;
      prio_arr[2] = UP;
    break;
  }
  switch (y) {
    case 1:
      prio_arr[1] = LEFT;
      prio_arr[3] = RIGHT;
    break;
    case 0:
      prio_arr[1] = RIGHT;
      prio_arr[3] = LEFT;
    break;
  }

  if(first.x == second.x){
    enum orientation tmp = prio_arr[0];
    prio_arr[0] = prio_arr[1];
    prio_arr[1] = tmp;
  }
}

void connect_nodes(struct graph *my_graph, struct map* my_map, struct coord first, struct coord second){
  struct node *my_node = graph_end(my_graph);
  struct coord my_node_coord;
  my_node_coord.x = first.x;
  my_node_coord.y = first.y;
  enum orientation prio_arr[4];

  int stop = 0;

  priority_ori(first, second, prio_arr);
  printf("first : %d %d, second : %d %d\n", first.x, first.y, second.x, second.y);
  struct coord next;
  do{
    next = neighbor(my_map, my_node_coord, prio_arr[0]);
    printf("Potential Priority : %d\n", prio_arr[0]);
    int i=0;
    while(next.x == -1 || node_exists(my_graph, next)){
      next = neighbor(my_map, first, prio_arr[i++]); // If no neighbor is available do smth
      printf("Potential Priority : %d\n", prio_arr[i]);
      printf("Potential neighbor (%d, %d)\n", next.x, next.y);
      if(i==4){
        stop = 1;
        break;
      }
    }
    printf("Definite neighbor (%d, %d)\n", next.x, next.y);
    if(stop){
      break;
    }
    struct node* next_node = malloc(sizeof(struct node));
    next_node->x = next.x;
    next_node->y = next.y;
    node_add(my_node, next_node);
    my_node = next_node;
    my_node_coord.x = next.x;
    my_node_coord.y = next.y;
  }while(next.x != second.x || next.y != second.y);
}

void generate_loop(struct graph* my_graph, struct map* my_map){
  int N = 4; // Number of points (n*m * 0.1)

  struct coord* chosen_points = tsp_init(my_map, N);

  for(int i=0; i<N; i++){
    printf("Chosen Point : (%d, %d)\n", chosen_points[i].x, chosen_points[i].y);
  }

  struct node* start_node = malloc(sizeof(struct node));
  start_node->x = chosen_points[0].x;
  start_node->y = chosen_points[0].y;

  graph_start(my_graph, start_node);

  for(int i=0; i<N; i++){
    if(i==N-1){
      connect_nodes(my_graph, my_map, chosen_points[i], chosen_points[0]);
    }
    connect_nodes(my_graph, my_map, chosen_points[i], chosen_points[i+1]);
  }
}
