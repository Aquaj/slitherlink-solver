#ifndef ___map_h___
#define ___map_h___

#include "point.h"

struct map{
  struct point** points;
  struct edge** edge_h;
  struct edge** edge_v;
};

struct map* map_init(int n, int m);

void map_fill(struct map* my_map, int x, int y);

#endif
