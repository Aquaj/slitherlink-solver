#ifndef ___loop_h___
#define ___loop_h___

#include "graph.h"

struct node* choose_next(struct map* my_map, struct node* my_node);
void generate_loop(struct graph* my_graph, struct map* my_map);
#endif
