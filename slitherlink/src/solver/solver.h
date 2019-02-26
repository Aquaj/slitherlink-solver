#ifndef ___solver_h___
#define ___solver_h___

#include "../struct/map.h"
#include "../struct/grid.h"
#include "../generator/generator.h"
#include "rules.h"

struct map;
struct grid;
struct coord;

void solve(struct map* my_map, struct grid* my_grid);
int basic_rules(struct map* my_map, struct grid* my_grid);
int point_rules(struct map* my_map, struct grid* my_grid);

int is_solved(struct map* my_map, struct grid *my_grid);
int is_valid_values(struct map* my_map, struct grid* my_grid);
int is_loop_closed(struct map* my_map);
int is_one_loop(struct map* my_map);
struct coord run_through_loop(struct map* my_map, char** is_in_loop, struct coord first);
struct coord next_hop(struct map* my_map, struct coord first, enum orientation my_ori);

#endif
