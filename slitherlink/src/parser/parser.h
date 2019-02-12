#ifndef ___parser_h___
#define ___parser_h___
#include <stdio.h>
#include <stdlib.h>
#include "../struct/map.h"

enum q_state{
  Q0,
  Q1,
  Q_IGN,
  Q_ERR,
  Q_OUT
};

void file_parse(FILE* file, enum q_state state);

#endif
