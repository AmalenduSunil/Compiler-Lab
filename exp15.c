#include <stdio.h>
#include <string.h>
int temp = 1;
void generate(char expr[]){
    char left[20], right[20], op;
    char result[20];
    int i, j;
    while (strchr(expr, '(') != NULL){
        int open = -1, close = -1;
        for (i = 0; expr[i] != '\0'; i++){
            if (expr[i] == '(')
                open = i;
            if (expr[i] == ')' && open != -1)
            {
                close = i;
                break;
            }
        }
        strcpy(left, expr + open + 1);
        left[close - open - 1] = '\0';
        generate(left);
        sprintf(result, "t%d", temp - 1);
        char newexpr[100];
        strncpy(newexpr, expr, open);
        newexpr[open] = '\0';
        strcat(newexpr, result);
        strcat(newexpr, expr + close + 1);
        strcpy(expr, newexpr);
    }
    for (i = 0; expr[i] != '\0'; i++){
        if (expr[i] == '*' || expr[i] == '/'){
            op = expr[i];
            j = i - 1;
            while (j >= 0 && expr[j] != ' ')
                j--;
            strcpy(left, expr + j + 1);
            left[i - j - 1] = '\0';
            strcpy(right, expr + i + 1);
            printf("t%d = %s %c %s\n",
                   temp, left, op, right);
            sprintf(result, "t%d", temp);
            expr[j + 1] = '\0';
            strcat(expr, result);
            temp++;
            i = 0;
        }
    }
    for (i = 0; expr[i] != '\0'; i++){
        if (expr[i] == '+' || expr[i] == '-'){
            op = expr[i];
            strcpy(left, expr);
            left[i] = '\0';
            strcpy(right, expr + i + 1);
            printf("t%d = %s %c %s\n",
                   temp, left, op, right);
            temp++;
            break;
        }
    }
}
int main(){
    char expr[100];
    printf("Enter the expression: ");
    scanf("%s", expr);
    printf("\nIntermediate Code:\n");
    generate(expr);
    return 0;
}