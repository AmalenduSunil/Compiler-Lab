%{
#include <stdio.h>

FILE *yyin;
%}

%%

int|float|char|if|else|while|for|return {
    printf("Keyword:%s\n", yytext);
}

[0-9]+ {
    printf("Number:%s\n", yytext);
}

\"([^\"\n]|\\.)*\" {
    printf("String Literal:%s\n", yytext);
}

\'([^\\\n]|\\.)\' {
    printf("Character Literal:%s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("Identifier:%s\n", yytext);
}

[+\-*/=<>] {
    printf("Operator:%s\n", yytext);
}

[(){};,] {
    printf("Special Symbol:%s\n", yytext);
}

[ \t\n]+ ;

. ;

%%

int yywrap(void)
{
    return 1;
}

int main()
{
    yyin = fopen("input.c", "r");

    if (yyin == NULL)
    {
        printf("Cannot open input.c\n");
        return 1;
    }

    yylex();
    fclose(yyin);
    return 0;
}
