#ifndef ___map_h___
#define ___map_h___

#include "point.h"

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

//
void map_fill(struct map* my_map, int x, int y);

#endif