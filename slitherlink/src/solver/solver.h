#ifndef ___solver_h___
#define ___solver_h___

#include "../struct/map.h"
#include "../struct/grid.h"
#include "../generator/generator.h"

struct map;
struct grid;

void solve(struct map* my_map, struct grid* my_grid);
void basic_rules(struct map* my_map, struct grid* my_grid);

int rule_applies(struct map* my_map, struct coord my_square, char value);

int rule_zero_applies(struct map* my_map, struct coord my_square);

void apply_rule(struct map* my_map, struct coord my_square, char value, int rule);
void apply_zero_rule(struct map* my_map, struct coord my_square, int rule);

#endif
