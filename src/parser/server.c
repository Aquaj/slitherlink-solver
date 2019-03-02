
#include <stdio.h>
#include <stdlib.h>

#include "y.tab.h"
#include "lex.yy.h"
char *readFile(char *fileName)
{
  FILE *file = fopen(fileName, "r");
  char *code;
  size_t n = 0;
  int c;

  if (file == NULL)
    return NULL; //could not open file

  code = malloc(1000);

  while ((c = fgetc(file)) != EOF)
    {
      code[n++] = (char) c;
    }

  // don't forget to terminate with the null character
  code[n] = '\0';

  return code;
}

int main(int argc, char const *argv[]){
  // printf("%s", readFile(argv[1]));
  //printf("%s", argv[1]);
  //FILE *file = fopen("./tests/grid_1.txt", "r");
  yyparse(argv[1]);
  return 0;
}
