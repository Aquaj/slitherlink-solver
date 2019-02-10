#include <stdio.h>
#include <stdlib.h>

#include "../struct/map.h"

int main(){
  struct map *my_map = map_init(4,4);

  tsp_init(my_map);
}
