#ifndef ___edge_h___
#define ___edge_h___

#include "map.h"
#include "point.h"

struct map;
struct coord;

int is_edge_drawn(struct map *my_map, struct coord my_edge, int is_horizontal);

#endif
