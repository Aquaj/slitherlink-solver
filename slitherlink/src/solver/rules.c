#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rules.h"

struct sub_grid* init_rules(int n){
  struct sub_grid* my_rules = malloc(n*sizeof(struct sub_grid));

  int i = 0;
  struct coord my_edge;

  rule_init(&my_rules[i], 2, 2);
  my_edge.x = 1;
  my_edge.y = 0;
  cross_rule_edge(&my_rules[i], my_edge, 1, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(&my_rules[i], my_edge, 1, 1);
  my_edge.x = 0;
  my_edge.y = 1;
  cross_rule_edge(&my_rules[i], my_edge, 0, 1);
  my_edge.x = 1;
  my_edge.y = 1;
  cross_rule_edge(&my_rules[i], my_edge, 0, 0);

  return my_rules;
}

void rule_init(struct sub_grid *my_rule, int n, int m){
  my_rule->n = n;
  my_rule->m = m;
  int num_char;
  if(((n+1)*m+n*(m+1))%4){
    num_char = ((n+1)*m+n*(m+1))/4 + 1;
  }
  else{
    num_char = ((n+1)*m+n*(m+1))/4;
  }

  my_rule->edges = calloc(num_char,sizeof(char));
  my_rule->res_edges = calloc(num_char,sizeof(char));
  my_rule->square_values = calloc(n*m,sizeof(char));
}

// Return the position of the edge in the binary representation of struct sub_grid
struct coord edge_position(struct coord my_edge, int n, int m, int is_horizontal){
  struct coord returned_pos;
  int num_bit = 0;
  int num_edge = 0;

  if(!is_horizontal){
    for(int i=0; i<n+1; i++){
      for(int j=0; j<m; j++){
        num_bit++;
        if(!(num_bit%4)){
          num_bit = 0;
          num_edge++;
        }
      }
    }
  }

  int i=0;
  int j=0;
  int x = my_edge.x;
  int y = my_edge.y;
  while(i!=x || j!=y){
    j++;
    num_bit++;
    if(!(num_bit%4)){
      num_bit = 0;
      num_edge++;
    }
    if(i==x && j==y){
      break;
    }
    if(j==m-is_horizontal){
      j=0;
      i++;
      num_bit++;
      if(!(num_bit%4)){
        num_bit = 0;
        num_edge++;
      }
    }
  }

  returned_pos.x = num_bit;
  returned_pos.y = num_edge;
  return returned_pos;
}

void set_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int drawn, int is_rule){
  struct coord bit_edge_pos = edge_position(my_edge, my_rule->n, my_rule->m, is_horizontal);
  int bit_pos = bit_edge_pos.x;
  int edge_pos = bit_edge_pos.y;

  char aff = 0x00;
  char mask;
  int shift = 0;
  if(drawn == 0){
    aff = 0x02; // 10 CROSSED
  }
  else if(drawn == 1){
    aff = 0x03; // 11 DRAWN
  }

  switch(bit_pos){
    case 0:
      mask = 0x03;
    break;
    case 1:
      mask = 0x0C;
      shift = 2;
    break;
    case 2:
      mask = 0x30;
      shift = 4;
    break;
    case 3:
      mask = 0xC0;
      shift = 6;
    break;
    default:
      assert(NULL);
    break;
  }

  if(is_rule){
    my_rule->edges[edge_pos] = my_rule->edges[edge_pos] & ~mask;

    char tmp = my_rule->edges[edge_pos] >> shift;
    tmp = tmp | aff;
    tmp = tmp << shift;
    my_rule->edges[edge_pos] = my_rule->edges[edge_pos] | tmp;
  }
  else{
    my_rule->res_edges[edge_pos] = my_rule->res_edges[edge_pos] & ~mask;

    char tmp = my_rule->res_edges[edge_pos] >> shift;
    tmp = tmp | aff;
    tmp = tmp << shift;
    my_rule->res_edges[edge_pos] = my_rule->res_edges[edge_pos] | tmp;
  }
}

void draw_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule){
  set_rule_edge(my_rule, my_edge, is_horizontal, 1, is_rule);
}

void cross_rule_edge(struct sub_grid *my_rule, struct coord my_edge, int is_horizontal, int is_rule){
  set_rule_edge(my_rule, my_edge, is_horizontal, 0, is_rule);
}
