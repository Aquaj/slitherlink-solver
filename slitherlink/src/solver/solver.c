#include <stdio.h>
#include "assert.h"

#include "solver.h"

void print_bit(char a);

void solve(struct map* my_map, struct grid* my_grid){
  basic_rules(my_map, my_grid);
}

void basic_rules(struct map* my_map, struct grid* my_grid){
  int n=my_map->n;
  int m=my_map->m;

  int rule;
  char value;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      struct coord my_square;
      my_square.x = i;
      my_square.y = j;
      value = my_grid->squares[i][j];
      do{
        rule = rule_applies(my_map, my_square, value);
        if(rule){
          apply_rule(my_map, my_square, value, rule);
        }
      }while(rule);
    }
  }
}

int rule_applies(struct map* my_map, struct coord my_square, char value){
  switch(value){
    case '0':
      return rule_zero_applies(my_map, my_square);
    break;
    case '1':
      return 0;
    break;
    case '2':
      return 0;
    break;
    case '3':
      return 0;
    break;
    case 'N':
      return 0;
    break;
    default:
      assert(NULL);
    break;
  }
}

int rule_zero_applies(struct map* my_map, struct coord my_square){
  int i = my_square.x;
  int j = my_square.y;

  // get north/east... edge
  struct coord north_edge = get_edge(my_square, NORTH);
  struct coord east_edge = get_edge(my_square, EAST);
  struct coord south_edge = get_edge(my_square, SOUTH);
  struct coord west_edge = get_edge(my_square, WEST);

  int value = is_edge_crossed(my_map, north_edge, 1) + is_edge_crossed(my_map, east_edge, 0) + is_edge_crossed(my_map, south_edge, 1) + is_edge_crossed(my_map, west_edge, 0);
  return value != 4;
}

void apply_rule(struct map* my_map, struct coord my_square, char value, int rule){
  switch(value){
    case '0':
      apply_zero_rule(my_map, my_square, rule);
    break;
    case '1':
    break;
    case '2':
    break;
    case '3':
    break;
    case 'N':
    break;
    default:
      assert(NULL);
    break;
  }
}

void apply_zero_rule(struct map* my_map, struct coord my_square, int rule){
  struct coord my_point;
  my_point.x = my_square.x;
  my_point.y = my_square.y;
  set_crossed_point(my_map, my_point, EAST);
  set_crossed_point(my_map, my_point, SOUTH);

  my_point.x = my_square.x+1;
  my_point.y = my_square.y;
  set_crossed_point(my_map, my_point, EAST);

  my_point.x = my_square.x;
  my_point.y = my_square.y+1;
  set_crossed_point(my_map, my_point, SOUTH);
}

int main(){
  struct map* my_map = map_init(4,4);
  struct grid* my_grid = grid_init(4,4);

  draw_loop(my_map);

  draw_all_values(my_map, my_grid);

  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      printf("Point %d %d :", i,j);
      print_bit(my_map->points[i][j]);
    }
  }

  print_grid(my_map, my_grid, 1);

  solve(my_map, my_grid);

  for(int i=0; i<my_map->n+1; i++){
    for(int j=0; j<my_map->m+1; j++){
      printf("Point %d %d :", i,j);
      print_bit(my_map->points[i][j]);
    }
  }

  print_grid(my_map, my_grid, 1);
}
