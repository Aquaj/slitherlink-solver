#ifndef ___edge_h___
#define ___edge_h___

#include "map.h"
#include "point.h"

struct map;
struct coord;
enum orientation;

int is_edge_empty(struct map *my_map, struct coord my_edge, int is_horizontal);
int is_edge_drawn(struct map *my_map, struct coord my_edge, int is_horizontal);
int is_edge_crossed(struct map *my_map, struct coord my_edge, int is_horizontal);

void empty_edge(struct map* my_map, struct coord my_edge, int is_horizontal);
void draw_edge(struct map* my_map, struct coord my_edge, int is_horizontal);

struct coord get_edge(struct coord my_square, enum orientation my_ori);
struct coord get_square_frm_point(struct coord my_point, enum orientation my_first_ori, enum orientation my_second_ori);
struct coord get_square_frm_square(struct coord my_square, enum orientation my_first_ori, enum orientation my_second_ori, int n, int m);
struct coord get_point_frm_square(struct coord my_square, int which);

#endif
