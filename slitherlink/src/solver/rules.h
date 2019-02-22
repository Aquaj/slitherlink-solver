#ifndef ___rules_h___
#define ___rules_h___

#include "../struct/map.h"

struct coord;

struct sub_grid{
  int n;
  int m;
  char *edges;
  char *square_values;
  char *res_edges;
};

struct sub_grid* init_rules(int n);
void rule_init(struct sub_grid *my_rule, int n, int m);
void set_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int drawn, int is_rule);
void set_rule_square(struct sub_grid *my_rule, struct coord my_square, char value);

void draw_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule);
void cross_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule);

struct coord edge_position(struct coord my_edge, int n, int m, int is_horizontal);

#endif
