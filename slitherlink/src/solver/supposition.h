#ifndef ___supposition_h___
#define ___supposition_h___

#include "../struct/map.h"
#include "../struct/tree.h"

struct coord;
enum orientation;

struct supposition{
  struct map *map;
  struct coord point;
  enum orientation ori;
  char drawn;
};

struct supposition* supposition_init(int n, int m);
void supposition_fill(struct supposition *my_supposition, struct coord current_point, enum orientation my_ori, int drawn);

struct supposition *last_supposition(struct tree* my_tree);
#endif
