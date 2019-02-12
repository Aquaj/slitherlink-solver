#ifndef ___map_h___
#define ___map_h___

#include "point.h"
#include "graph.h"
#include "../generator/loop.h"
#include "../struct/square.h"
#include "../struct/edge.h"

struct graph;

struct coord{
  int x;
  int y;
};

enum orientation{
  UP,     // 0
  RIGHT,  // 1
  DOWN,   // 2
  LEFT    // 3
};

struct map{
  int n;
  int m;
  struct point** points; // n+1 * m+1
  struct edge** edges_h; // n+1 * m
  struct edge** edges_v; // n * m+1
  struct square** squares; // n * m
};

struct map* map_init(int n, int m);
void map_free(struct map* my_map);

// map
void map_fill(struct map* my_map, struct graph* my_graph);
void map_fill_values(struct map* my_map, struct graph* my_graph);
struct coord neighbor(struct map* my_map, struct coord my_point, enum orientation my_ori);
void map_remove_values(struct map* my_map);
void map_fill_points(struct map* my_map);
void map_init_edges(struct map* my_map);

#endif
