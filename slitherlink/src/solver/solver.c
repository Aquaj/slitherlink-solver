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

    nb_iter_points = point_rules(my_map, my_grid);

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
  printf("Grid Solved : %d\n", is_solved(my_map, my_grid));
}

int point_rules(struct map* my_map, struct grid* my_grid){
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

    /* VERBOSE */
    // sleep(1);
    // print_grid(my_map, my_grid, 1);
    /* VERBOSE */

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
      my_subgrid = rule_init(rule_n, rule_m);

      for(int offset_x=0; offset_x<n+1-rule_n; offset_x++){
        for(int offset_y=0; offset_y<m+1-rule_m; offset_y++){
          subgrid_extract(my_map, my_grid, my_subgrid, rule_n, rule_m, offset_x, offset_y);
          if(rule_applies(*my_subgrid, *my_rules[i])){
            rule_counter[i]++;
            subgrid_draw_res(my_map, my_rules[i], offset_x, offset_y);
          }
          rule_clear(my_subgrid);
        }
      }
      rule_free(my_subgrid);
    }

    /* VERBOSE */
    // sleep(1);
    // print_grid(my_map, my_grid, 1);
    /* VERBOSE */

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

int is_valid_values(struct map* my_map, struct grid* my_grid){
  assert(my_map);
  assert(my_grid);

  struct coord my_square;

  for(int i=0; i<my_grid->n; i++){
    for(int j=0; j<my_grid->m; j++){
      if(my_grid->squares[i][j] != 'N'){
        my_square.x = i;
        my_square.y = j;
        if(my_grid->squares[i][j] != square_value(my_map, my_square)){
          return 0;
        }
      }
    }
  }

  return 1;
}

int is_loop_closed(struct map* my_map){
  assert(my_map);

  struct coord my_point;
  int my_point_deg = 0;
  int is_drawn = 0;
  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      my_point.x = i;
      my_point.y = j;
      my_point_deg = point_deg(my_map, my_point, 1);
      assert(my_point_deg < 3);
      if(my_point_deg == 1){
        return 0;
      }
      else if(my_point_deg == 2){
        is_drawn = 1;
      }
    }
  }

  return is_drawn;
}

int is_one_loop(struct map* my_map){
  assert(my_map);
  int n = my_map->n;
  int m = my_map->m;

  char **is_in_loop = calloc((n+1),sizeof(char *));
  for(int i=0; i<n+1; i++){
    is_in_loop[i] = calloc((m+1),sizeof(char));
  }

  struct coord my_point, first, end;
  first.x = -1;
  first.y = -1;
  int my_point_deg = 0;
  for(int i=0; i<n+1; i++){
    for(int j=0; j<m+1; j++){
      my_point.x = i;
      my_point.y = j;
      my_point_deg = point_deg(my_map, my_point, 1);
      if(my_point_deg == 1){
        assert(NULL);
      }
      else if(my_point_deg == 2){
        if(first.x == -1){
          first.x = i;
          first.y = j;
        }
        is_in_loop[i][j] = 0x01;
      }
    }
  }

  assert(point_deg(my_map, first, 1) == 2);
  end = run_through_loop(my_map, is_in_loop, first);

  if(end.x != first.x || end.y != first.y){
    for(int i=0;i<n+1; i++){
      free(is_in_loop[i]);
    }
    free(is_in_loop);

    return 0;
  }

  for(int i=0; i<n+1; i++){
    for(int j=0; j<m+1; j++){
      if(is_in_loop[i][j] == 0x01){
        for(int i=0;i<n+1; i++){
          free(is_in_loop[i]);
        }
        free(is_in_loop);

        return 0;
      }
    }
  }

  for(int i=0;i<n+1; i++){
    free(is_in_loop[i]);
  }
  free(is_in_loop);

  return 1;
}

struct coord run_through_loop(struct map* my_map, char** is_in_loop, struct coord first){
  struct coord end, next;
  enum orientation my_ori = 0;

  is_in_loop[first.x][first.y] = 0x03;
  next = next_hop(my_map, first, my_ori);
  while(is_in_loop[next.x][next.y] != 0x03){
    is_in_loop[next.x][next.y] = 0x03;
    my_ori = first.x - next.x + 1;
    if(my_ori == 1){
      my_ori = (4 + first.y - next.y)%4;
    }

    first.x = next.x;
    first.y = next.y;
    next = next_hop(my_map, first, my_ori);
  }

  end.x = next.x;
  end.y = next.y;
  return end;
}

struct coord next_hop(struct map* my_map, struct coord first, enum orientation my_ori){
  for(int i=0; i<3; i++){
    my_ori = (my_ori + 1)%4;
    if(is_drawn_point(my_map, first, my_ori)){
      return neighbor(my_map, first, my_ori);
    }
  }
}

int is_solved(struct map* my_map, struct grid *my_grid){
  int valid_values = is_valid_values(my_map, my_grid);
  if(!valid_values){
    printf("Values Not Satisfied\n");
    return 0;
  }

  int closed_loop = is_loop_closed(my_map);
  if(!closed_loop){
    printf("Loop Not Closed\n");
    return 0;
  }

  int one_loop = is_one_loop(my_map);
  if(!one_loop){
    printf("Loop Compromised\n");
    return 0;
  }

  return 1;
}
