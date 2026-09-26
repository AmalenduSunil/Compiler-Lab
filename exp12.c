#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i = 0, error = 0;

void E(void);
void T(void);
void Eprime(void);
void Tprime(void);
void F(void);
int main(void){
    printf("Enter an arithmetic expression: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    i = 0;
    error = 0;
    E();
    if (i == strlen(input) && error == 0)
        printf("\nAccepted..!!!\n");
    else
        printf("\nRejected..!!!\n");

    return 0;
}
void E(void){
    T();
    Eprime();
}
void Eprime(void){
    if (error)
        return;
    if (input[i] == '+'){
        i++;
        T();
        Eprime();
    }
}
void T(void){
    F();
    Tprime();
}
void Tprime(void){
    if (error)
        return;
    if (input[i] == '*'){
        i++;
        F();
        Tprime();
    }
}
void F(void){
    if (error)
        return;
    if (isalnum((unsigned char)input[i])){
        i++;
    }
    else if (input[i] == '('){
        i++;
        E();
        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else{
        error = 1;
    }
}
