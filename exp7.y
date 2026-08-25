%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *);
%}

%token DIGIT ALPHA

%%

var:
      ALPHA
    | var ALPHA
    | var DIGIT
    ;

%%

int main()
{
    printf("Enter a variable name: ");
    yyparse();
    printf("\nValid Variable\n");
    return 0;
}

void yyerror(const char *s)
{
    printf("\nInvalid Variable\n");
    exit(1);
}