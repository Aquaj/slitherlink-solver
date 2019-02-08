#ifndef ___edge_h___
#define ___edge_h___

// state : crossed, empty, drawn.
enum state {
  CROSSED,
  EMPTY,
  DRAWN
  };

struct edge{
  int state : 2;
};

void set_edge(struct edge* my_edge, enum state my_state);

#endif
