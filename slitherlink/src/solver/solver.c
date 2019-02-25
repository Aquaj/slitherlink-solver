#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "solver.h"

void print_bit(char a);

void solve(struct map* my_map, struct grid* my_grid){
  int nb_iter_rules = 0;
  int nb_iter_points = 0;

  int can_expand = 1;

  int expand_iter = 0;
  int rule_iter = 0;
  int point_iter = 0;
  while(can_expand){
    nb_iter_rules = basic_rules(my_map, my_grid);

    nb_iter_points = point_rules(my_map);

    expand_iter++;
    rule_iter+=nb_iter_rules;
    point_iter+=nb_iter_points;
    if(nb_iter_points == 1){
      can_expand = 0;
    }
  }

  print_grid(my_map, my_grid, 1);

  printf("Expand Iterations : %d\n", expand_iter);
  printf("Rule Iterations : %d\n", rule_iter);
  printf("Point Iterations : %d\n", point_iter);
}

int point_rules(struct map* my_map){
  assert(my_map);

  int n = my_map->n;
  int m = my_map->m;

  int deg_drawn = 0;
  int deg_crossed = 0;
  struct coord my_point, my_neighbor;

  int changed = 0;
  int my_iter = 0;
  do{
    changed = 0;
    for(int i=0; i<n+1; i++){
      for(int j=0; j<m+1; j++){
        // Corner points
        if((i==0 && j==0) || (i==0 && j==m) || (i==n && j==0) || (i==n && j==m)){
          my_point.x = i;
          my_point.y = j;
          deg_drawn = point_deg(my_map, my_point, 1);
          deg_crossed = point_deg(my_map, my_point, 0);

          if(deg_drawn + deg_crossed == 1){

            if(deg_drawn == 1){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_drawn_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
            if(deg_crossed == 1){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_crossed_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
          }
        }

        // Border points
        else if(i==0 || i==n || j==0 || j==m){
          my_point.x = i;
          my_point.y = j;
          deg_drawn = point_deg(my_map, my_point, 1);
          deg_crossed = point_deg(my_map, my_point, 0);
          if(deg_drawn + deg_crossed == 2){
            if(deg_drawn == 2){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_crossed_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
            if(deg_crossed == 2){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_crossed_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
            else{
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_drawn_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
          }
        }

        // All other cases
        else{
          my_point.x = i;
          my_point.y = j;
          deg_drawn = point_deg(my_map, my_point, 1);
          deg_crossed = point_deg(my_map, my_point, 0);
          if(deg_drawn + deg_crossed == 2 || deg_drawn + deg_crossed == 3){
            if(deg_drawn == 2){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_crossed_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
            if(deg_crossed == 2 && deg_drawn == 1){
              for(enum orientation my_ori=NORTH; my_ori<4; my_ori++){
                if(is_empty_point(my_map, my_point, my_ori)){
                  my_neighbor = neighbor(my_map, my_point, my_ori);
                  if(my_neighbor.x != -1){
                    set_drawn_point(my_map, my_point, my_ori);
                    changed = 1;
                  }
                }
              }
            }
          }
        }
      }
    }
    my_iter++;
  }while(changed);

  return my_iter;
}

int basic_rules(struct map* my_map, struct grid* my_grid){
  struct sub_grid** my_rules = malloc(4*32*sizeof(struct sub_grid*));
  int nb_rules = init_rules(my_rules);

  struct sub_grid *my_subgrid;
  int n = my_map->n;
  int m = my_map->m;
  int rule_n;
  int rule_m;

  int *rule_counter;
  int *old_counter = calloc(nb_rules, sizeof(int));

  int my_iter = 0;
  int break_rules = 0;
  while(!break_rules){
    rule_counter = calloc(nb_rules, sizeof(int));

    for(int i=0; i<nb_rules; i++){
      rule_n = my_rules[i]->rule_map->n;
      rule_m = my_rules[i]->rule_map->m;

      for(int offset_x=0; offset_x<n+1-rule_n; offset_x++){
        for(int offset_y=0; offset_y<m+1-rule_m; offset_y++){
          my_subgrid = rule_init(rule_n, rule_m);
          subgrid_extract(my_map, my_grid, my_subgrid, rule_n, rule_m, offset_x, offset_y);
          if(rule_applies(*my_subgrid, *my_rules[i])){
            rule_counter[i]++;
            subgrid_draw_res(my_map, my_rules[i], offset_x, offset_y);
          }
          rule_free(my_subgrid);
        }
      }
    }

    break_rules = 1;
    for(int i=0; i<nb_rules; i++){
      if(old_counter[i] != rule_counter[i]){
        break_rules = 0;
      }
    }

    if(!break_rules){
      my_iter++;
      free(old_counter);
      old_counter = calloc(nb_rules, sizeof(int));
      for(int i=0; i<nb_rules; i++){
        old_counter[i] = rule_counter[i];
      }

      free(rule_counter);
    }
    else{
      my_iter++;
      for(int i=0; i<nb_rules; i++){
        //printf("Rule %d applied : %d\n", i, rule_counter[i]);
      }
      free(old_counter);
      free(rule_counter);
    }
  }
  free_rules(my_rules, nb_rules);

  return my_iter;
}
