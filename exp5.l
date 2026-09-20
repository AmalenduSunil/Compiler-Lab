%{
#include <stdio.h>

int vowels = 0, consonants = 0;
%}

%%
[aeiouAEIOU]    { vowels++; }
[a-zA-Z]        { consonants++; }
\n              { 
                  printf("Total vowels = %d\n", vowels);
                  printf("Total consonants = %d\n", consonants);
                  return 0;
                }
.               ;
%%

int yywrap() //EOF
{
    return 1;
}

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}