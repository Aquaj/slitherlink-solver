#ifndef ___point_h___
#define ___point_h___

enum direction {
  UR,
  UL,
  DR,
  DL
  };

struct point{
  int UR : 3;
  int UL : 3;
  int DR : 3;
  int DL : 3;
};

void set_point(struct point *my_point, enum direction dir, int set);

#endif
