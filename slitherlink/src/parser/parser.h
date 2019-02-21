#ifndef ___parser_h___
#define ___parser_h___
#include <stdio.h>
#include <stdlib.h>
#include "../struct/grid.h"

enum q_state{
  Q0,    //0
  Q1,    //1
  Q_IGN, //2
  Q_ERR, //3
  Q_OUT  //4
};

void file_parse(FILE* file, enum q_state *state, struct grid* my_grid, int n, int m);
void matrix_size(FILE* file, int* m, int* n);
void fill_matrix(FILE* file, enum q_state *state, int *caractere, struct grid* my_grid, int *my_n, int *my_m, int n, int m);

#endif
