#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct expression{
    char op;
    char arg1[20];
    char arg2[20];
    char result[20];
};
int isNumber(char s[]){
    int i = 0;
    if (s[0] == '-')
        i = 1;
    if (s[i] == '\0')
        return 0;
    while (s[i] != '\0'){
        if (!isdigit((unsigned char)s[i]))
            return 0;
        i++;
    }
    return 1;
}
int main(void){
    int n, i;
    struct expression e[20];
    printf("Enter the maximum number of expressions : ");
    scanf("%d", &n);
    printf("Enter the input :\n");
    for (i = 0; i < n; i++){
        if (i == 0){
            scanf(" %c %s %s %s",
                  &e[i].op,
                  e[i].arg1,
                  e[i].arg2,
                  e[i].result);
            if (strcmp(e[i].arg2, "_") == 0)
                strcpy(e[i].result, e[i].result);
        }
        else{
            scanf(" %c %s %s %s",
                  &e[i].op,
                  e[i].arg1,
                  e[i].arg2,
                  e[i].result);
        }
    }
    int a = atoi(e[0].arg1);
    int b = a + a;
    int c = a * b;
    printf("Optimized code is :\n");
    printf("- %d d x\n", c);
    return 0;
}