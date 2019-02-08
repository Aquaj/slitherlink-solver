#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

struct graph* graph_init(){
  struct graph* my_graph = malloc(sizeof(struct graph));
  return my_graph;
}

void graph_start(struct graph* my_graph, struct node* start){
  my_graph->start = start;
}

void graph_end(struct graph* my_graph, struct node* end){
  my_graph->end = end;
}
