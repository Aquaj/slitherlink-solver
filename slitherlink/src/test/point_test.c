#include <stdio.h>
#include <stdlib.h>
#include "../struct/point.h"

int main(){
  struct point *my_point = malloc(sizeof(struct point));

  set_point(my_point, DR, 1);
  set_point(my_point, DL, 1);
  set_point(my_point, UL, 1);
  set_point(my_point, UR, 1);
  printf("DR %d\n", my_point->DR);
  printf("DL %d\n", my_point->DL);
  printf("UL %d\n", my_point->UL);
  printf("UR %d\n", my_point->UR);

  return 0;
}
