#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

struct graph* graph_init(){
  struct graph* my_graph = malloc(sizeof(struct graph));
  return my_graph;
}

void graph_start(struct graph* my_graph, struct node* start){
  my_graph->start = start;
}

struct node* graph_end(struct graph* my_graph){
  assert(my_graph);
  assert(my_graph->start);

  struct node *my_node = my_graph->start;
  while(my_node->next){
    my_node = my_node->next;
  }

  return my_node;
}

int node_exists(struct graph* my_graph, struct coord node){
  assert(my_graph);
  assert(my_graph->start);
  struct node *my_node = my_graph->start;
  if(my_node->x == node.x && my_node->y == node.y){
    return 1;
  }
  while(my_node->next){
    my_node = my_node->next;
    if(my_node->x == node.x && my_node->y == node.y){
      return 1;
    }
  }
  return 0;
}

void node_add(struct node* my_node, struct node* next){
  assert(my_node);
  assert(next);

  my_node->next = next;
}

void graph_print(struct graph* my_graph){
  assert(my_graph);

  struct node* my_node = my_graph->start;
  while(my_node){
    printf("(%d, %d)-->", my_node->x, my_node->y);
    my_node = my_node->next;
  }
}
