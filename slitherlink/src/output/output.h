#ifndef ___output_h___
#define ___output_h___

#include "../generator/generator.h"
#include "../struct/map.h"

struct map;
struct grid;

void print_grid(struct map* my_map, struct grid* my_grid, int _verbose);

#endif
