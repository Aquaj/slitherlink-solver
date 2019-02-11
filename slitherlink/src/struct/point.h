#ifndef ___point_h___
#define ___point_h___

/* int set
  1 : [0,0,1] = {0}
  2 : [0,1,0] = {1}
  3 : [0,1,1] = {0,1}
  4 : [1,0,0] = {2}
  5 : [1,0,1] = {0,2}
  6 : [1,1,0] = {1,2}
  7 : [1,1,1] = {0,1,2}

*/

#include "map.h"

struct map;
struct coord;

enum direction {
  UR,
  UL,
  DR,
  DL
  };

struct point{
  int UR : 4;
  int UL : 4;
  int DR : 4;
  int DL : 4;
};

void set_point(struct point *my_point, enum direction dir, int set);
void set_square_points(struct map* my_map, struct coord my_square_coord, int my_square_value);

#endif
