#ifndef ___tree_h___
#define ___tree_h___

struct tree {
  struct node *root;
};

struct node {
    void *data;
    struct node* child;
};

struct tree* tree_init();
void tree_add(struct tree* my_tree, void *data);
void tree_remove(struct tree* my_tree);
struct node* tree_leaf(struct tree *my_tree);
int is_tree_empty(struct tree* my_tree);

struct node* node_init(void *data);
void node_free(struct node *my_node);

#endif
