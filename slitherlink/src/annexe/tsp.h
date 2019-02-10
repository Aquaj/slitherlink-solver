#ifndef ___tsp_h___
#define ___tsp_h___

#include "../struct/map.h"

struct map;
struct coord;

struct coord* tsp_init(struct map *my_map, int N);

int least(int c, int *cost, int **cost_ary, int *completed, int N);
void cost_distance(struct map* my_map, struct coord *chosen_points, int **cost_ary, int N);
struct coord *choose_points(struct map *my_map, int N);
void mincost(int point, int *cost, int **cost_ary, int *completed, struct coord *chosen_points, int N);

#endif
