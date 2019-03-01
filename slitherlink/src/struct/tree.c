#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"

struct tree* tree_init(){
  struct tree *my_tree = malloc(sizeof(struct tree));
  my_tree->root = NULL;
  return my_tree;
}

void tree_add(struct tree* my_tree, void *data){
  assert(my_tree);
  assert(data);

  struct node* my_node = node_init(data);
  if(is_tree_empty(my_tree)){
    my_tree->root = my_node;
  }
  else{
    struct node* leaf_node = tree_leaf(my_tree);
    leaf_node->child = my_node;
  }
}

void tree_remove(struct tree* my_tree){
  assert(my_tree);
  assert(!is_tree_empty(my_tree));

  struct node* leaf_node, *before_leaf;
  before_leaf = my_tree->root;
  if(before_leaf->child){
    leaf_node = before_leaf->child;
    while(leaf_node->child){
      before_leaf = leaf_node;
      leaf_node = leaf_node->child;
    }

    //free(leaf_node);
    //leaf_node = NULL;
    before_leaf->child = NULL;
  }
  else{
    my_tree->root = NULL;
    //node_free(before_leaf);
  }
}

struct node* tree_leaf(struct tree *my_tree){
  assert(!is_tree_empty(my_tree));

  struct node* my_node = my_tree->root;
  int i=0;
  while(my_node->child){
    i++;
    my_node = my_node->child;
  }
  return my_node;
}

int is_tree_empty(struct tree* my_tree){
  assert(my_tree);
  if(my_tree->root != NULL){
    return 0;
  }
  return 1;
}

struct node* node_init(void *data){
    struct node* new_node = malloc(sizeof(struct node));
    new_node = malloc(sizeof(data));
    new_node->data = data;

    return new_node;
}

void node_free(struct node *my_node){//, void (*data_free)(void *)){
  // if(my_node->child){
  //   free(my_node->child);
  // }
  //data_free(my_node->data);
  free(my_node);
}
