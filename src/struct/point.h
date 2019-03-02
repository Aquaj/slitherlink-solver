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
enum orientation;

//void set_square_points(struct map* my_map, struct coord my_square_coord, int my_square_value);

void set_point(struct map* my_map, struct coord my_point, enum orientation my_ori, int drawn);
void set_empty_point(struct map* my_map, struct coord my_point, enum orientation my_ori);
void set_drawn_point(struct map* my_map, struct coord my_point, enum orientation my_ori);
void set_crossed_point(struct map* my_map, struct coord my_point, enum orientation my_ori);

int is_point_aff(struct map* my_map, struct coord my_point, enum orientation my_ori, char aff);
int is_drawn_point(struct map* my_map, struct coord my_point, enum orientation my_ori);
int is_crossed_point(struct map* my_map, struct coord my_point, enum orientation my_ori);
int is_empty_point(struct map* my_map, struct coord my_point, enum orientation my_ori);

int point_deg(struct map* my_map, struct coord my_point, int drawn);

void draw_line(struct map* my_map, struct coord first, struct coord second, enum orientation my_ori);


#endif
