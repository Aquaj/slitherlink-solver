%{
#include <stdio.h>  
%}

%parse-param {char *file
     }
%union{
  char *value;
 }
%code requires{
  //#include "extern.h"  //#include "lex.yy.h"
 }
%code provides {
  void yyerror(char *,char const *);
  int yylex();
  int yyparse(char *);
  }




%token ALPHANUM  NEWLINE TAB
%token HASHTAG UNDERSCORE ZERO ONE TWO THREE
%start grid
%%

grid
: line NEWLINE grid
| line
;
line
: valid_char line
| valid_char
;
valid_char
: UNDERSCORE {printf("under\n");}
| ZERO {printf("zero\n");}
| ONE {printf("one\n");}
| TWO {printf("two\n");}
| THREE {printf("three\n");}
%%
  /*int main () {
  char server_response[100]= "blabla";
  extern FILE * yyin;
  yyin = fopen("test", "rt");
  if (!yyparse(server_response))
    printf(" server_response %s\n", server_response);
    //fprintf(stderr, "Successful parsing.\n");
  else
    fprintf(stderr, "error found.\n");
  yyin = fopen("test_look", "rt");
  if (!yyparse(server_response))
    printf("server_response %s\n", server_response);
    //fprintf(stderr, "Successful parsing.\n");
  else
    fprintf(stderr, "error found.\n");
}*/
