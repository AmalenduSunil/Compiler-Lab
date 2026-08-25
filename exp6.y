%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *);
%}

%token NUMBER ID

%left '+' '-'
%left '*' '/'

%%

exp:
      exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | '(' exp ')'
    | NUMBER
    | ID
    ;

%%

int main()
{
    printf("Enter the expression: ");
    yyparse();

    printf("\nValid Expression\n");
    return 0;
}

void yyerror(const char *s)
{
    printf("\nInvalid Expression\n");
    exit(1);
}