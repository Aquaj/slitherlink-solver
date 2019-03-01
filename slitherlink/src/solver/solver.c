#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "solver.h"

void print_bit(char a);

int expand_rules(struct map* my_map, struct grid* my_grid){
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
    if(nb_iter_points <= 1 || nb_iter_rules == 0){
      can_expand = 0;
    }
  }

  print_grid(my_map, my_grid, 1);
/*
  printf("Expand Iterations : %d\n", expand_iter);
  printf("Rule Iterations : %d\n", rule_iter);
  printf("Point Iterations : %d\n", point_iter);
  printf("Grid Solved : %d\n", is_solved(my_map, my_grid));
*/
  if(nb_iter_rules == 0 || nb_iter_points == 0){
    return 0;
  }
  return 1;
}

void solve(struct map* my_map, struct grid* my_grid){
  int solvable = expand_rules(my_map, my_grid);

  if(solvable == 0){
    printf("Grid Unsolvable\n");
  }

  make_suppositions(my_map, my_grid);
}

void make_suppositions(struct map* my_map, struct grid *my_grid){
  struct tree *supp_tree = tree_init();

  int nb_suppositions = 0;
  while(!is_solved(my_map, my_grid)){
    printf("Make supposition\n");
    while(!make_supposition(my_map, my_grid, supp_tree)){
      nb_suppositions++;
      printf("Contradiction\n");
      backtrack(my_map, my_grid, supp_tree);
      while(!draw_supposition(my_map, my_grid, supp_tree)){
        nb_suppositions++;
        printf("Contradiction\n");
        backtrack(my_map, my_grid, supp_tree); // D -> X, X -> Del + Parent X
      }
    }
    nb_suppositions++;
    while(!draw_supposition(my_map, my_grid, supp_tree)){
      nb_suppositions++;
      printf("Contradiction\n");
      backtrack(my_map, my_grid, supp_tree); // D -> X, X -> Del + Parent X
    }
    while(is_loop_closed(my_map) && !is_one_loop(my_map)){
      nb_suppositions++;
      printf("Contradiction Loop Compromised\n");
      backtrack(my_map, my_grid, supp_tree);
      while(!draw_supposition(my_map, my_grid, supp_tree)){
        nb_suppositions++;
        printf("Contradiction\n");
        backtrack(my_map, my_grid, supp_tree); // D -> X, X -> Del + Parent X
      }
    }
  }

  printf("Solved in %d iterations\n", nb_suppositions);
}

int make_supposition(struct map* my_map, struct grid* my_grid, struct tree *supp_tree){
  assert(my_map);
  assert(my_grid);
  assert(supp_tree);

  struct supposition *current_supposition = supposition_init(my_map->n, my_map->m);
  struct supposition *parent_supposition;
  map_copy(current_supposition->map, my_map);

  struct coord parent_point, current_point;
  enum orientation current_ori;

  if(is_tree_empty(supp_tree)){
    parent_point.x = 0;
    parent_point.y = 0;
    current_point = choose_point(current_supposition->map, parent_point);
    if(current_point.x == -1){
      return 0;
    }
    current_ori = choose_orientation(current_supposition->map, current_point);
    supposition_fill(current_supposition, current_point, current_ori, 1); // DRAWN = 1
    tree_add(supp_tree, current_supposition);
  }
  else{
    parent_supposition = last_supposition(supp_tree);
    parent_point = parent_supposition->point;
    current_point = choose_point(current_supposition->map, parent_point);
    if(current_point.x == -1){
      return 0;
    }
    current_ori = choose_orientation(current_supposition->map, current_point);
    supposition_fill(current_supposition, current_point, current_ori, 1); // DRAWN = 1
    tree_add(supp_tree, current_supposition);
  }
  return 1;
}

void backtrack(struct map* my_map, struct grid *my_grid, struct tree *supp_tree){
  struct supposition *failed_supposition;
  failed_supposition = last_supposition(supp_tree);

  map_copy(my_map, failed_supposition->map);

  if(failed_supposition->drawn == 0x01){
    supposition_fill(failed_supposition, failed_supposition->point, failed_supposition->ori, 0);
  }
  else{
    tree_remove(supp_tree);
    backtrack(my_map, my_grid, supp_tree);
  }
}

int draw_supposition(struct map *my_map, struct grid *my_grid, struct tree *supp_tree){
  struct supposition* my_supposition = last_supposition(supp_tree);

  if(my_supposition->drawn == 0x01){
    printf("Point %d %d : %d DRAWN\n", my_supposition->point.x, my_supposition->point.y, my_supposition->ori);
    set_drawn_point(my_map, my_supposition->point, my_supposition->ori);
  }
  else{
    printf("Point %d %d : %d CROSSED\n", my_supposition->point.x, my_supposition->point.y, my_supposition->ori);
    set_crossed_point(my_map, my_supposition->point, my_supposition->ori);
  }

  return expand_rules(my_map, my_grid);
}

int distance(struct coord first, struct coord second){
  return abs(first.x - second.x) + abs(first.y - second.y);
}

struct coord choose_point(struct map* my_map, struct coord parent_point){
  int precedence[5] = {0,0,0,0,0};
  int deg_point_drawn = 0;
  int deg_point_crossed = 0;
  int min_dist = (my_map->n+1)*(my_map->m+1);
  struct coord min_point;
  min_point.x = -1;
  min_point.y = -1;

  struct coord my_point;
  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      my_point.x = i;
      my_point.y = j;
      if(!(my_point.x == 0 && my_point.y == 0 || my_point.x == my_map->n+1 && my_point.y == 0 || my_point.x == 0 && my_point.y == my_map->m+1 || my_point.x == my_map->n+1 && my_point.y == my_map->m+1)){
        deg_point_drawn = point_deg(my_map, my_point, 1);
        deg_point_crossed = point_deg(my_map, my_point, 0);
        if(deg_point_drawn + deg_point_crossed <= 2 && deg_point_drawn < 2){
          if(deg_point_drawn == 1){
            if(deg_point_crossed == 1){
              precedence[0] = 1;
            }
            else{
              precedence[1] = 1;
            }
          }
          else{
            if(deg_point_crossed == 2){
              precedence[2] = 1;
            }
            else if(deg_point_crossed == 1){
              precedence[3] = 1;
            }
            else{
              precedence[4] = 1;
            }
          }
        }
      }
    }
  }

  for(int i=0; i<my_map->n; i++){
    for(int j=0; j<my_map->m; j++){
      my_point.x = i;
      my_point.y = j;
      if(!(my_point.x == 0 && my_point.y == 0 || my_point.x == my_map->n+1 && my_point.y == 0 || my_point.x == 0 && my_point.y == my_map->m+1 || my_point.x == my_map->n+1 && my_point.y == my_map->m+1)){
        deg_point_drawn = point_deg(my_map, my_point, 1);
        deg_point_crossed = point_deg(my_map, my_point, 0);
        if(precedence[0]){
          if(deg_point_drawn == 1){
            if(deg_point_crossed == 1){
              if(min_dist > distance(parent_point, my_point)){
                min_dist = distance(parent_point, my_point);
                min_point = my_point;
              }
            }
          }
        }
        else if(precedence[1]){
          if(deg_point_drawn == 1){
            if(deg_point_crossed == 0){
              if(min_dist > distance(parent_point, my_point)){
                min_dist = distance(parent_point, my_point);
                min_point = my_point;
              }
            }
          }
        }
        else if(precedence[2]){
          if(deg_point_drawn == 0){
            if(deg_point_crossed == 2){
              if(min_dist > distance(parent_point, my_point)){
                min_dist = distance(parent_point, my_point);
                min_point = my_point;
              }
            }
          }
        }
        else if(precedence[3]){
          if(deg_point_drawn == 0){
            if(deg_point_crossed == 1){
              if(min_dist > distance(parent_point, my_point)){
                min_dist = distance(parent_point, my_point);
                min_point = my_point;
              }
            }
          }
        }
        else{
          if(deg_point_drawn == 0){
            if(deg_point_crossed == 0){
              if(min_dist > distance(parent_point, my_point)){
                min_dist = distance(parent_point, my_point);
                min_point = my_point;
              }
            }
          }
        }
      }
    }
  }

  printf("%d %d\n", min_point.x, min_point.y);
  return min_point;
}

enum orientation choose_orientation(struct map* my_map, struct coord current_point){
  enum orientation my_ori = 0;
  struct coord neighbor_point;
  for(enum orientation i=0; i<4; i++){
    if(is_empty_point(my_map, current_point, i)){
      neighbor_point = neighbor(my_map, current_point, i);
      if(neighbor_point.x != -1){
        return i;
      }
    }
  }
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
        my_point.x = i;
        my_point.y = j;
        deg_drawn = point_deg(my_map, my_point, 1);
        deg_crossed = point_deg(my_map, my_point, 0);

        // Contradiction
        if(deg_drawn >= 3){
          return 0;
        }


        // Corner points
        if((i==0 && j==0) || (i==0 && j==m) || (i==n && j==0) || (i==n && j==m)){
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
    //  sleep(1);
    //  print_grid(my_map, my_grid, 1);
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
            if(!subgrid_draw_res(my_map, my_rules[i], offset_x, offset_y)){
              return 0;
            }
          }
          rule_clear(my_subgrid);
        }
      }
      rule_free(my_subgrid);
    }

    /* VERBOSE */
    //  sleep(1);
    //  print_grid(my_map, my_grid, 1);
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
