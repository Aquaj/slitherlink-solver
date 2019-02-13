#ifndef ___grid_h___
#define ___grid_h___

#include "map.h"
#include "edge.h"

struct coord;
enum orientation;

struct grid{
  int n;
  int m;
  char** squares; // n * m
};

struct grid* grid_init(int n, int m);
void grid_free(struct grid* my_grid);

void grid_fill(struct map* my_map, struct grid* my_grid);
void grid_remove_values(struct grid* my_grid);

#endif
