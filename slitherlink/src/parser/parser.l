%{
#include <stdlib.h>
#include "y.tab.h"

%}
%option header-file="lex.yy.h"
D[0-9]
L[a-zA-Z_]
AN[a-aA-Z0-9]
W[a-zA-Z0-9_.]


%%
(#)(.*)(\t)*(\n) {;}
_ {return UNDERSCORE;}
0 {return ZERO;}
1 {return ONE;}
2 {return TWO;}
3 {return THREE;}
[\n] {return NEWLINE;}
[\t]* {;}
. {printf("erreur: caractère non reconnu");}

%%
void yyerror (char *file,char const *s) {
   fprintf (stderr, " error: %s\n", s);
 }
int yywrap(){
//printf("wrapping");
return 1;
}
