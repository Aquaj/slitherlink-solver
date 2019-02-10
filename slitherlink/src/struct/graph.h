#ifndef ___graph_h___
#define ___graph_h___

#include "map.h"

struct coord;

struct node{
  int x;
  int y;
  struct node *next;
};

struct graph{
  struct node *start;
};

struct graph* graph_init();
void graph_start(struct graph* my_graph, struct node* start);
struct node* graph_end(struct graph* my_graph);
void is_graph_valid(struct graph* my_graph);
void graph_print(struct graph* my_graph);

void node_add(struct node* my_node, struct node* next);
int node_exists(struct graph* my_graph, struct coord node);

#endif
