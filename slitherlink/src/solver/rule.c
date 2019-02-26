#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "rule.h"

struct sub_grid* rule_init(int n, int m){
  struct sub_grid* my_rule = malloc(sizeof(struct sub_grid));

  my_rule->rule_map = map_init(n,m);
  my_rule->res_map = map_init(n,m);
  my_rule->rule_grid = grid_init(n,m);

  return my_rule;
}

void rule_free(struct sub_grid* my_rule){
  assert(my_rule);

  map_free(my_rule->rule_map);
  map_free(my_rule->res_map);
  grid_free(my_rule->rule_grid);

  free(my_rule);
}

void rule_clear(struct sub_grid* my_rule){
  assert(my_rule);

  map_clear(my_rule->rule_map);
  map_clear(my_rule->res_map);
  grid_clear(my_rule->rule_grid);
}

void set_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int drawn, int is_rule){
  if(is_rule){
    if(drawn){
      draw_edge(my_rule->rule_map, my_edge, is_horizontal);
    }
    else{
      cross_edge(my_rule->rule_map, my_edge, is_horizontal);
    }
  }
  else{
    if(drawn){
      draw_edge(my_rule->res_map, my_edge, is_horizontal);
    }
    else{
      cross_edge(my_rule->res_map, my_edge, is_horizontal);
    }
  }

}

void set_rule_square(struct sub_grid *my_rule, struct coord my_square, char value){
  int x = my_square.x;
  int y = my_square.y;
  my_rule->rule_grid->squares[x][y] = value;
}

void draw_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule){
  set_rule_edge(my_rule, my_edge, is_horizontal, 1, is_rule);
}

void cross_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule){
  set_rule_edge(my_rule, my_edge, is_horizontal, 0, is_rule);
}

void subgrid_extract(struct map* my_map, struct grid *my_grid, struct sub_grid *my_subgrid, int n, int m, int offset_x, int offset_y){
  assert(my_map);
  assert(my_grid);
  assert(my_subgrid);
  assert(offset_x+n < my_map->n+1);
  assert(offset_y+m < my_map->m+1);

  struct coord my_edge, rule_edge, my_square;

  for(int i=offset_x; i<offset_x+n+1; i++){
    for(int j=offset_y; j<offset_y+m+1; j++){

      // horizontal
      if(j!=offset_y+m){
        my_edge.x = i;
        my_edge.y = j;
        rule_edge.x = i - offset_x;
        rule_edge.y = j - offset_y;
        if(is_edge_drawn(my_map, my_edge, 1)){
          draw_rule_edge(my_subgrid, rule_edge, 1, 1);
        }
        else if(is_edge_crossed(my_map, my_edge, 1)){
          cross_rule_edge(my_subgrid, rule_edge, 1, 1);
        }
      }
      // vertical
      if(i!=offset_x+n){
        my_edge.x = i;
        my_edge.y = j;
        rule_edge.x = i - offset_x;
        rule_edge.y = j - offset_y;
        if(is_edge_drawn(my_map, my_edge, 0)){
          draw_rule_edge(my_subgrid, rule_edge, 0, 1);
        }
        else if(is_edge_crossed(my_map, my_edge, 0)){
          cross_rule_edge(my_subgrid, rule_edge, 0, 1);
        }
      }

      if(i!=offset_x+n && j!=offset_y+m){
        my_square.x = i - offset_x;
        my_square.y = j - offset_y;
        set_rule_square(my_subgrid, my_square, my_grid->squares[i][j]);
      }
    }
  }
}

int rule_applies(struct sub_grid my_subgrid, struct sub_grid my_rule){
  assert(my_subgrid.rule_map->n == my_rule.rule_map->n);
  assert(my_subgrid.rule_map->m == my_rule.rule_map->m);

  int n = my_subgrid.rule_map->n;
  int m = my_subgrid.rule_map->m;

  struct coord my_edge, my_square;

  int rule_drawn, rule_crossed, drawn, crossed;

  for(int i=0; i<n+1; i++){
    for(int j=0; j<m+1; j++){

      // horizontal
      if(j!=m){
        my_edge.x = i;
        my_edge.y = j;
        rule_drawn = is_edge_drawn(my_rule.rule_map, my_edge, 1);
        rule_crossed = is_edge_crossed(my_rule.rule_map, my_edge, 1);

        if(rule_drawn){
          drawn = is_edge_drawn(my_subgrid.rule_map, my_edge, 1);
          if(!drawn){
            return 0;
          }
        }
        else if(rule_crossed){
          crossed = is_edge_crossed(my_subgrid.rule_map, my_edge, 1);
          if(!crossed){
            return 0;
          }
        }
      }
      // vertical
      if(i!=n){
        my_edge.x = i;
        my_edge.y = j;
        rule_drawn = is_edge_drawn(my_rule.rule_map, my_edge, 0);
        rule_crossed = is_edge_crossed(my_rule.rule_map, my_edge, 0);

        if(rule_drawn){
          drawn = is_edge_drawn(my_subgrid.rule_map, my_edge, 0);
          if(!drawn){
            return 0;
          }
        }
        else if(rule_crossed){
          crossed = is_edge_crossed(my_subgrid.rule_map, my_edge, 0);
          if(!crossed){
            return 0;
          }
        }
      }

      if(i!=n && j!=m){
        if(my_rule.rule_grid->squares[i][j] != 'N'){
          if(my_rule.rule_grid->squares[i][j] != my_subgrid.rule_grid->squares[i][j]){
            return 0;
          }
        }
      }
    }
  }

  return 1;
}

void subgrid_draw_res(struct map* my_map, struct sub_grid* my_subgrid, int offset_x, int offset_y){
  assert(my_map);
  assert(my_subgrid);

  int n = my_subgrid->res_map->n;
  int m = my_subgrid->res_map->m;

  assert(offset_x+n < my_map->n+1);
  assert(offset_y+m < my_map->m+1);

  struct coord my_edge, map_edge, my_square;

  for(int i=offset_x; i<offset_x+n+1; i++){
    for(int j=offset_y; j<offset_y+m+1; j++){

      // horizontal
      if(j!=offset_y+m){
        my_edge.x = i - offset_x;
        my_edge.y = j - offset_y;
        map_edge.x = i;
        map_edge.y = j;
        if(is_edge_drawn(my_subgrid->res_map, my_edge, 1)){
          draw_edge(my_map, map_edge, 1);
        }
        else if(is_edge_crossed(my_subgrid->res_map, my_edge, 1)){
          cross_edge(my_map, map_edge, 1);
        }
      }
      // vertical
      if(i!=offset_x+n){
        my_edge.x = i - offset_x;
        my_edge.y = j - offset_y;
        map_edge.x = i;
        map_edge.y = j;
        if(is_edge_drawn(my_subgrid->res_map, my_edge, 0)){
          draw_edge(my_map, map_edge, 0);
        }
        else if(is_edge_crossed(my_subgrid->res_map, my_edge, 0)){
          cross_edge(my_map, map_edge, 0);
        }
      }
    }
  }
}

void subgrid_draw_rule(struct map* my_map, struct sub_grid* my_subgrid, int offset_x, int offset_y){
  assert(my_map);
  assert(my_subgrid);

  int n = my_subgrid->rule_map->n;
  int m = my_subgrid->rule_map->m;

  assert(offset_x+n < my_map->n+1);
  assert(offset_y+m < my_map->m+1);

  struct coord my_edge, map_edge, my_square;

  for(int i=offset_x; i<offset_x+n+1; i++){
    for(int j=offset_y; j<offset_y+m+1; j++){

      // horizontal
      if(j!=offset_y+m){
        my_edge.x = i - offset_x;
        my_edge.y = j - offset_y;
        map_edge.x = i;
        map_edge.y = j;
        if(is_edge_drawn(my_subgrid->rule_map, my_edge, 1)){
          draw_edge(my_map, map_edge, 1);
        }
        else if(is_edge_crossed(my_subgrid->rule_map, my_edge, 1)){
          cross_edge(my_map, map_edge, 1);
        }
      }
      // vertical
      if(i!=offset_x+n){
        my_edge.x = i - offset_x;
        my_edge.y = j - offset_y;
        map_edge.x = i;
        map_edge.y = j;
        if(is_edge_drawn(my_subgrid->rule_map, my_edge, 0)){
          draw_edge(my_map, map_edge, 0);
        }
        else if(is_edge_crossed(my_subgrid->rule_map, my_edge, 0)){
          cross_edge(my_map, map_edge, 0);
        }
      }
    }
  }
}

void rotate_rule(struct sub_grid *my_rule, struct sub_grid *my_rotation, int rot){
  assert(my_rule);
  assert(my_rotation);

  switch(rot){
    case 0:
      copy_subgrid(my_rotation, my_rule);
    break;
    case 1:
      copy_subgrid(my_rotation, my_rule);
      rotate_subgrid(my_rotation);
    break;
    case 2:
      copy_subgrid(my_rotation, my_rule);
      rotate_subgrid(my_rotation);
      rotate_subgrid(my_rotation);
    break;
    case 3:
      copy_subgrid(my_rotation, my_rule);
      rotate_subgrid(my_rotation);
      rotate_subgrid(my_rotation);
      rotate_subgrid(my_rotation);
    break;
    default:
      assert(NULL);
    break;
  }
}

void copy_subgrid(struct sub_grid *dest, struct sub_grid *src){
  assert(dest);
  assert(src);

  map_copy(dest->rule_map, src->rule_map);
  map_copy(dest->res_map, src->res_map);
  grid_copy(dest->rule_grid, src->rule_grid);
}

void rotate_subgrid(struct sub_grid *my_rotation){
  int n = my_rotation->rule_map->n;
  int m = my_rotation->rule_map->m;

  struct sub_grid *next_rotation = rule_init(n, m);
  struct coord my_edge, next_edge, next_square;

  //horizontal
  for(int i=0; i<n+1; i++){
    for(int j=0; j<m; j++){
      my_edge.x = i;
      my_edge.y = j;
      next_edge.x = m-1-j;
      next_edge.y = i;
      if(is_edge_drawn(my_rotation->rule_map, my_edge, 1)){
        draw_edge(next_rotation->rule_map, next_edge, 0);
      }
      else if(is_edge_crossed(my_rotation->rule_map, my_edge, 1)){
        cross_edge(next_rotation->rule_map, next_edge, 0);
      }
      if(is_edge_drawn(my_rotation->res_map, my_edge, 1)){
        draw_edge(next_rotation->res_map, next_edge, 0);
      }
      else if(is_edge_crossed(my_rotation->res_map, my_edge, 1)){
        cross_edge(next_rotation->res_map, next_edge, 0);
      }
    }
  }

  //vertical
  for(int i=0; i<n; i++){
    for(int j=0; j<m+1; j++){
      my_edge.x = i;
      my_edge.y = j;
      next_edge.x = m-j;
      next_edge.y = i;
      if(is_edge_drawn(my_rotation->rule_map, my_edge, 0)){
        draw_edge(next_rotation->rule_map, next_edge, 1);
      }
      else if(is_edge_crossed(my_rotation->rule_map, my_edge, 0)){
        cross_edge(next_rotation->rule_map, next_edge, 1);
      }
      if(is_edge_drawn(my_rotation->res_map, my_edge, 0)){
        draw_edge(next_rotation->res_map, next_edge, 1);
      }
      else if(is_edge_crossed(my_rotation->res_map, my_edge, 0)){
        cross_edge(next_rotation->res_map, next_edge, 1);
      }
    }
  }

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(my_rotation->rule_grid->squares[i][j] != 'N'){
        next_square.x = m-1-j;
        next_square.y = i;
        set_rule_square(next_rotation, next_square, my_rotation->rule_grid->squares[i][j]);
      }
    }
  }

  copy_subgrid(my_rotation, next_rotation);
  rule_free(next_rotation);
}
