%{ 
#include<stdio.h> 
#include<string.h> 
char replace_with [] = "abc"; 
char replace [] ="ABC"; 
%} 
%% 
"abc" {strcpy(yytext, replace);ECHO;} 
%% 
int yywrap() 
{ 
return 1; 
} 
/* code section */ 
int main() 
{ 
yylex(); 
} 
