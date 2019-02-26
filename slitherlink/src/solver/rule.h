#ifndef ___rule_h___
#define ___rule_h___

#include "../struct/map.h"

struct coord;

struct sub_grid{
  struct map *rule_map;
  struct map *res_map;
  struct grid *rule_grid;
};

struct sub_grid* rule_init(int n, int m);
void rule_free(struct sub_grid* my_rule);
void rule_clear(struct sub_grid* my_rule);
void set_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int drawn, int is_rule);
void set_rule_square(struct sub_grid *my_rule, struct coord my_square, char value);

void draw_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule);
void cross_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule);

void subgrid_extract(struct map* my_map, struct grid *my_grid, struct sub_grid *my_subgrid, int n, int m, int offset_x, int offset_y);
int rule_applies(struct sub_grid my_subgrid, struct sub_grid my_rule);
void subgrid_draw_res(struct map* my_map, struct sub_grid *my_subgrid, int offset_x, int offset_y);
void subgrid_draw_rule(struct map* my_map, struct sub_grid* my_subgrid, int offset_x, int offset_y);

void rotate_rule(struct sub_grid *my_rule, struct sub_grid *my_rotation, int rot);

void copy_subgrid(struct sub_grid *my_rule, struct sub_grid *my_rotation);
void rotate_subgrid(struct sub_grid *my_rotation);

#endif
