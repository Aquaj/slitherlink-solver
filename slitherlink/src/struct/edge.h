#ifndef ___edge_h___
#define ___edge_h___

// state : crossed, empty, drawn.
enum state {
  CROSSED,
  EMPTY,
  DRAWN
  };

struct edge{
  int state : 3; // 2 bit doesn't work ???
};

void set_edge(struct edge* my_edge, enum state my_state);
int is_drawn(struct edge my_edge);
int is_empty(struct edge my_edge);
int is_crossed(struct edge my_edge);

#endif
