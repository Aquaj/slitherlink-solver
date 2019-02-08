#include <stdio.h>
#include <stdlib.h>

#include "loop.h"

struct node* choose_next(struct map* my_map, struct node* my_node){
  int n = my_map->n;
  int m = my_map->m;

  // struct node* new_node = malloc(sizeof(struct node));
  // // Corners
  // if((my_node->x == 0 && my_node->y == 0) || (my_node->x == 0 && my_node->y == m) || (my_node->x == n && my_node->y == 0) || (my_node->x == n && my_node->y == m){
  //   if(my_node->x == 0){
  //     if(my_node->y == 0){
  //       int r = rand() % 2;
  //       new_node->x = my_node->x + r;
  //       new_node->y = my_node->y + (1-r);
  //     }
  //     else if(my_node->y == m){
  //       int r = rand() % 2;
  //       new_node->x = my_node->x + r;
  //       new_node->y = my_node->y - (1-r);
  //     }
  //   }
  //   if(my_node->x == n){
  //     if(my_node->y == 0){
  //       int r = rand() % 2;
  //       new_node->x = my_node->x - r;
  //       new_node->y = my_node->y + (1-r);
  //     }
  //     else if(my_node->y == m){
  //       int r = rand() % 2;
  //       new_node->x = my_node->x - r;
  //       new_node->y = my_node->y - (1-r);
  //     }
  //   }
  // }
}
void generate_loop(struct graph* my_graph, struct map* my_map){
  struct node* curr_node = my_graph->start;
  struct node* next_node = choose_next(my_map, curr_node);
  while(next_node != start_node){
    node_add(curr_node, next_node);
    curr_node = next_node;
    next_node = choose_next(my_map, curr_node);
  }
}
