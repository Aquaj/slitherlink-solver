#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "solver.h"

void print_bit(char a);

void solve(struct map* my_map, struct grid* my_grid){
  //basic_rules(my_map, my_grid);
  int nb_rules = 9;
  struct sub_grid **my_rules = init_rules(nb_rules);

  //subgrid_draw_rule(my_map, my_rules[4], 0, 0);
  //subgrid_draw_rule(my_map, my_rules[0], 1, 1);
  //subgrid_draw_rule(my_map, my_rules[2], 2, 0);
  //subgrid_draw_rule(my_map, my_rules[3], 2, 2);

  struct sub_grid *my_subgrid, *my_rotation;
  int n = my_map->n;
  int m = my_map->m;
  int rule_n;
  int rule_m;

  int *rule_counter = calloc(nb_rules, sizeof(int));

  int iter = 0;
  while(iter < 10){
    rule_counter = calloc(nb_rules, sizeof(int));
    for(int i=0; i<nb_rules; i++){
      rule_n = my_rules[i]->rule_map->n;
      rule_m = my_rules[i]->rule_map->m;

      //my_subgrid = rule_init(rule_n, rule_m);
      for(int rot=0; rot<4; rot++){
        my_rotation = rule_init(rule_n, rule_m);
        rotate_rule(my_rules[i], my_rotation, rot);

        for(int offset_x=0; offset_x<n+1-rule_n; offset_x++){
          for(int offset_y=0; offset_y<m+1-rule_m; offset_y++){
            my_subgrid = rule_init(rule_n, rule_m);
            subgrid_extract(my_map, my_grid, my_subgrid, rule_n, rule_m, offset_x, offset_y);
            if(rule_applies(*my_subgrid, *my_rotation)){
              rule_counter[i]++;
              subgrid_draw_res(my_map, my_rotation, offset_x, offset_y);
            }
          }
        }
      }


      //rule_free(my_subgrid);
    }

    for(int i=0; i<nb_rules; i++){
      printf("Iter n %d Rule %d applied : %d\n", iter, i, rule_counter[i]);
    }
    iter++;
    printf("\n");
  }
}
