#ifndef ___generator_h___
#define ___generator_h___

#include "../struct/map.h"
#include "loop.h"
#include "../output/output.h"

void draw_loop(struct map* my_map);
void draw_all_values(struct map* my_map, struct grid* my_grid);
void draw_values(struct map* my_map);
void remove_values(struct map* my_map);
void fill_points(struct map* my_map);

#endif
