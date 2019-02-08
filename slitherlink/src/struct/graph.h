#ifndef ___graph_h___
#define ___graph_h___

struct node{
  int x;
  int y;
  struct node *next;
}

struct graph{
  struct node *start;
};

struct graph* graph_init();
void graph_start(struct graph* my_graph, struct node* start);
void graph_end(struct graph* my_graph, struct node* end);
void is_graph_valid(struct graph* my_graph);

void node_add(struct node* my_node, struct node* next);

#endif
