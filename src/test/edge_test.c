#include <stdio.h>
#include <assert.h>

#include "../struct/edge.h"
#include "../output/output.h"
#include "../struct/grid.h"

int main(){
  printf("___Edge Tests___ : .........................");
  struct map *my_map = map_init(4,4);

  struct coord my_point, my_edge, my_square, extracted_edge;
  my_point.x = 1;
  my_point.y = 1;
  for(int i=0 ; i<4; i++){
    my_edge.x = my_point.x - (i==0);
    my_edge.y = my_point.y - (i==3);

    if(i%2){
      set_drawn_point(my_map, my_point, i);
      assert(is_edge_drawn(my_map, my_edge, 1));
    }
    else{
      set_crossed_point(my_map, my_point, i);
      assert(is_edge_crossed(my_map, my_edge, 0));
    }

    my_square = get_square_frm_point(my_point, i, (i+1)%4);
    extracted_edge = get_edge(my_square, ((i+1) + 2)% 4);
    assert(my_edge.x == extracted_edge.x);
    assert(my_edge.y == extracted_edge.y);
  }

  printf("Complete\n");

  return 0;
}
