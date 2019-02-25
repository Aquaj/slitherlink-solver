#ifndef ___solver_h___
#define ___solver_h___

#include "../struct/map.h"
#include "../struct/grid.h"
#include "../generator/generator.h"
#include "rules.h"

struct map;
struct grid;

void solve(struct map* my_map, struct grid* my_grid);
int basic_rules(struct map* my_map, struct grid* my_grid);
int point_rules(struct map* my_map);

#endif
