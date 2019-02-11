#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "loop.h"
#include "../struct/edge.h"

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
  int is_first = 0;

  printf("first : %d %d, second : %d %d\n", first.x, first.y, second.x, second.y);
  struct coord next;
  do{
    priority_ori(my_node_coord, second, prio_arr);
    next = neighbor(my_map, my_node_coord, prio_arr[0]);
    printf("Potential Priority : %d\n", prio_arr[0]);
    printf("Potential neighbor (%d, %d)\n", next.x, next.y);

    if(second.x == my_graph->start->x && second.y == my_graph->start->y){
      if(next.x == my_graph->start->x && next.y == my_graph->start->y){
        is_first = 1;
      }
    }

    int i=0;
    while(next.x == -1 || (node_exists(my_graph, next) && !is_first) ){
      if(i==3){
        stop = 1;
        break;
      }
      next = neighbor(my_map, my_node_coord, prio_arr[++i]); // If no neighbor is available do smth
      printf("Potential Priority : %d\n", prio_arr[i]);
      printf("Potential neighbor (%d, %d)\n", next.x, next.y);
    }
    printf("Definite Priority : %d\n", prio_arr[i]);
    printf("Definite neighbor (%d, %d)\n", next.x, next.y);
    if(stop){
      break;
    }
    struct node* next_node = malloc(sizeof(struct node));
    next_node->x = next.x;
    next_node->y = next.y;
    node_add(my_node, next_node);

    if(my_node->x == next_node->x){
      if(my_node->y < next_node->y){
        set_edge(&my_map->edges_h[my_node->x][my_node->y], DRAWN);
        printf("edgeh : %d, %d\n", my_node->x, my_node->y);
      }
      else{
        set_edge(&my_map->edges_h[my_node->x][next_node->y], DRAWN);
        printf("edgeh : %d, %d\n", my_node->x, next_node->y);
      }
    }

    else if(my_node->y == next_node->y){
      if(my_node->x < next_node->x){
        set_edge(&my_map->edges_v[my_node->x][my_node->y], DRAWN);
        printf("edgev : %d, %d\n", my_node->x, my_node->y);
      }
      else{
        set_edge(&my_map->edges_v[next_node->x][my_node->y], DRAWN);
        printf("edgev : %d, %d\n", next_node->x, my_node->y);
      }
    }

    my_node = next_node;
    my_node_coord.x = next.x;
    my_node_coord.y = next.y;
  }while(next.x != second.x || next.y != second.y);
}

void generate_loop(struct map* my_map, struct graph* my_graph){
  int N = 4; // Number of points (n*m * 0.1)

  struct coord* chosen_points;
  struct node* start_node;
  struct node* end_node;

  // Free graph after each try
  do{
    chosen_points = tsp_init(my_map, N);

    for(int i=0; i<N; i++){
      printf("Chosen Point : (%d, %d)\n", chosen_points[i].x, chosen_points[i].y);
    }

    start_node = malloc(sizeof(struct node));
    start_node->x = chosen_points[0].x;
    start_node->y = chosen_points[0].y;

    graph_start(my_graph, start_node);


    for(int i=0; i<N; i++){
      if(i==N-1){
        connect_nodes(my_graph, my_map, chosen_points[i], chosen_points[0]);
      }
      else{
        connect_nodes(my_graph, my_map, chosen_points[i], chosen_points[i+1]);
      }
    }

    end_node = graph_end(my_graph);
  }while(end_node->next->x != start_node->x || end_node->next->y != start_node->y);
  //printf("IS DONE : %d\n", (start_node->x == end_node->next->x && start_node->y == end_node->next->y));
  assert(end_node->next);
}
