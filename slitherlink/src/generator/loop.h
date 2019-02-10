#ifndef ___loop_h___
#define ___loop_h___

#include "../struct/graph.h"
#include "../struct/map.h"
#include "../annexe/tsp.h"

struct map;
struct graph;

void generate_loop(struct graph* my_graph, struct map* my_map);
#endif
