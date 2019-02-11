#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "edge.h"

void set_edge(struct edge* my_edge, enum state my_state){
  assert(my_edge);

  switch (my_state) {
    case CROSSED:
      my_edge->state = 0;
    break;
    case EMPTY:
      my_edge->state = 1;
    break;
    case DRAWN:
      my_edge->state = 2;
    break;
    default:
      assert(NULL);
    break;
  }

  printf("STATE == %d\n", my_edge->state);
}

int is_drawn(struct edge my_edge){
  return my_edge.state == 2;
}
