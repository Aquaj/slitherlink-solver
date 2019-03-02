#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../struct/tree.h"

int main(){
  struct tree *my_tree = tree_init();
  struct node* leaf_node;
  int *my_point;

  printf("empty %d\n", is_tree_empty(my_tree));

  int *point = malloc(5*sizeof(int));
  int *point2 = malloc(5*sizeof(int));
  point[0] = 55;
  point2[0] = 66;

  tree_add(my_tree, point);
  leaf_node = tree_leaf(my_tree);
  my_point = (int *)leaf_node->data;
  printf("Point %d\n", my_point[0]);
  assert(my_point == point);

  printf("empty %d\n", is_tree_empty(my_tree));

  tree_add(my_tree, point2);
  leaf_node = tree_leaf(my_tree);
  my_point = (int *)leaf_node->data;
  printf("Point %d\n", my_point[0]);
  assert(my_point != point);
  assert(my_point == point2);

  tree_remove(my_tree);
  leaf_node = tree_leaf(my_tree);
  my_point = (int *)leaf_node->data;
  printf("Point %d\n", my_point[0]);
  assert(my_point == point);
  assert(my_point != point2);

  tree_remove(my_tree);
  //leaf_node = tree_leaf(my_tree);
  //my_point = (int *)leaf_node->data;
  //printf("Point %d\n", my_point[0]);

  printf("empty %d\n", is_tree_empty(my_tree));

  return 0;
}
