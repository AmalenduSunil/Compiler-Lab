#include <stdio.h>
#include <ctype.h>
#include <string.h>

char keywords[][20] = {
    "int", "float", "char", "if", "else", "while",
    "for", "return", "void", "break", "continue"
};

int isKeyword(char str[]) {
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, next, buffer[100];
    int i, sno = 1;

    fp = fopen("input.c", "r");

    if (fp == NULL) {
        printf("File not found!\n");
        return 0;
    }

    printf("\n-------------------------------------------------\n");
    printf("%-10s %-20s %-15s\n", "Serial No", "Lexeme", "Token");
    printf("-------------------------------------------------\n");

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore spaces
        if (isspace(ch))
            continue;

        // Ignore comments
        if (ch == '/') {
            next = fgetc(fp);

            // Single-line comment
            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }

            // Multi-line comment
            else if (next == '*') {
                char prev = 0;

                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }

            else {
                printf("%-10d %-20s %-15s\n", sno++, "/", "Operator");
                ungetc(next, fp);
                continue;
            }
        }

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            i = 0;

            do {
                buffer[i++] = ch;
                ch = fgetc(fp);
            } while (isalnum(ch) || ch == '_');

            buffer[i] = '\0';

            if (isKeyword(buffer))
                printf("%-10d %-20s %-15s\n", sno++, buffer, "Keyword");
            else
                printf("%-10d %-20s %-15s\n", sno++, buffer, "Identifier");

            if (ch != EOF)
                ungetc(ch, fp);
        }

        // Number
        else if (isdigit(ch)) {
            i = 0;

            do {
                buffer[i++] = ch;
                ch = fgetc(fp);
            } while (isdigit(ch) || ch == '.');

            buffer[i] = '\0';

            printf("%-10d %-20s %-15s\n", sno++, buffer, "Number");

            if (ch != EOF)
                ungetc(ch, fp);
        }

        // String Literal
        else if (ch == '"') {
            i = 0;

            while ((ch = fgetc(fp)) != '"' && ch != EOF)
                buffer[i++] = ch;

            buffer[i] = '\0';

            printf("%-10d %-20s %-15s\n", sno++, buffer, "Literal");
        }

        // Operators
        else if (strchr("+-*=<>!%", ch)) {
            buffer[0] = ch;
            buffer[1] = '\0';

            printf("%-10d %-20s %-15s\n", sno++, buffer, "Operator");
        }

        // Special Symbols
        else if (strchr("(){}[];,", ch)) {
            buffer[0] = ch;
            buffer[1] = '\0';

            printf("%-10d %-20s %-15s\n", sno++, buffer, "Symbol");
        }
    }

    printf("-------------------------------------------------\n");

    fclose(fp);

    return 0;
}