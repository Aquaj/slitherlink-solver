#ifndef ___square_h___
#define ___square_h___

struct square{
  int value : 3;
};

void set_square(struct square* my_square, int my_value);

#endif
