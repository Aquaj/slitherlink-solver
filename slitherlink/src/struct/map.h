#ifndef ___map_h___
#define ___map_h___

#include "grid.h"
#include "point.h"

struct grid;

struct coord{
  int x;
  int y;
};

enum orientation{
  NORTH,    // 0
  EAST,     // 1
  SOUTH,    // 2
  WEST      // 3
};

struct map{
  int n;
  int m;
  char** points; // n+1 * m+1
};

struct map* map_init(int n, int m);
void map_free(struct map* my_map);
void map_clear(struct map* my_map);
void map_copy(struct map* dest, struct map* src);

void map_fill_points(struct map* my_map, struct grid* my_grid);
void map_loop_init(struct map* my_map);
void map_loop_distortion(struct map* my_map, struct grid *my_grid,int iter);

void get_border_squares(struct map *my_map, char **border_squares);
struct coord get_random_square(char **border_squares, int n, int m);

struct coord neighbor(struct map* my_map, struct coord my_point, enum orientation my_ori);
enum orientation opposite_orientation(enum orientation my_ori);

#endif
