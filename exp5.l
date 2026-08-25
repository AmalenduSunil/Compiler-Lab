%{
#include <stdio.h>
int v = 0;
int c = 0;
%}

%%

[\t\n ]              ;
[aeiouAEIOU]         { v++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]   { c++; }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter string: ");
    yylex();

    printf("Number of vowels: %d\n", v);
    printf("Number of consonants: %d\n", c);

    return 0;
}