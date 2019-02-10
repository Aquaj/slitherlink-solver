#ifndef ___generator_h___
#define ___generator_h___

#include "../struct/map.h"
#include "loop.h"

struct map* generate_map(int n, int m);
void draw_loop(struct map* my_map);
void draw_values(struct map* my_map);
void remove_values(struct map* my_map);

#endif
