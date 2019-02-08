#ifndef ___parser_h___
#define ___parser_h___

#include map.h

enum q_state{
  q0,
  q1,
  q2,
  qver,
  qerr,
  qout
}

void file_parse(FILE* my_file);


#endif
