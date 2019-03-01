#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "supposition.h"

struct supposition* supposition_init(int n, int m){
  struct supposition* my_supposition = malloc(sizeof(struct supposition));
  my_supposition->map = map_init(n, m);

  return my_supposition;
}

void supposition_free(struct supposition* my_supposition){
  assert(my_supposition);

  map_free(my_supposition->map);
  free(my_supposition);
}

void supposition_fill(struct supposition *my_supposition, struct coord current_point, enum orientation my_ori, int drawn){
  assert(my_supposition);

  my_supposition->point = current_point;
  my_supposition->ori = my_ori;
  if(drawn){
    my_supposition->drawn = 0x01;
  }
  else{
    my_supposition->drawn = 0x00;
  }
}

struct supposition *last_supposition(struct tree* my_tree){
  struct node* leaf_node = tree_leaf(my_tree);
  struct supposition *my_supposition = (struct supposition *)leaf_node->data;
  return my_supposition;
}
