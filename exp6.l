%{
#include "exp6.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+                  { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z][_a-zA-Z0-9]*  { return ID; }
[ \t]                   ;
\n                      { return 0; }
.                       { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}