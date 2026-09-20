#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char prod[MAX][MAX];
char first[26][MAX];
char follow[26][MAX];

int n;

/* Add a character to a set */
void add(char set[], char c)
{
    int i;

    if (c == '\0')
        return;

    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == c)
            return;
    }

    set[i] = c;
    set[i + 1] = '\0';
}

/* Find FIRST */
void findFirst(char symbol, char result[])
{
    int i, j, k;
    char rhs[MAX];

    /* Terminal */
    if (!isupper(symbol))
    {
        add(result, symbol);
        return;
    }

    /* Find productions of the non-terminal */
    for (i = 0; i < n; i++)
    {
        if (prod[i][0] == symbol)
        {
            strcpy(rhs, prod[i] + 2);

            /* A -> e */
            if (rhs[0] == 'e' && rhs[1] == '\0')
            {
                add(result, 'e');
                continue;
            }

            for (j = 0; rhs[j] != '\0'; j++)
            {
                char temp[MAX] = "";

                findFirst(rhs[j], temp);

                /* Add FIRST except epsilon */
                for (k = 0; temp[k] != '\0'; k++)
                {
                    if (temp[k] != 'e')
                        add(result, temp[k]);
                }

                /* If epsilon is not present, stop */
                if (strchr(temp, 'e') == NULL)
                    break;

                /* If all symbols can produce epsilon */
                if (rhs[j + 1] == '\0')
                    add(result, 'e');
            }
        }
    }
}

/* Find FOLLOW */
void findFollow(char symbol, char result[])
{
    int i, j, k;

    /* Start symbol */
    if (symbol == prod[0][0])
        add(result, '$');

    for (i = 0; i < n; i++)
    {
        char *rhs = prod[i] + 2;

        for (j = 0; rhs[j] != '\0'; j++)
        {
            if (rhs[j] == symbol)
            {
                /* Symbol is at the end */
                if (rhs[j + 1] == '\0')
                {
                    if (prod[i][0] != symbol)
                    {
                        char temp[MAX] = "";

                        findFollow(prod[i][0], temp);

                        for (k = 0; temp[k] != '\0'; k++)
                            add(result, temp[k]);
                    }
                }
                else
                {
                    char temp[MAX] = "";

                    findFirst(rhs[j + 1], temp);

                    /* Add FIRST(next) except epsilon */
                    for (k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != 'e')
                            add(result, temp[k]);
                    }

                    /* If next can produce epsilon */
                    if (strchr(temp, 'e') != NULL &&
                        prod[i][0] != symbol)
                    {
                        char temp2[MAX] = "";

                        findFollow(prod[i][0], temp2);

                        for (k = 0; temp2[k] != '\0'; k++)
                            add(result, temp2[k]);
                    }
                }
            }
        }
    }
}

int main()
{
    int i;
    char left, right[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c = %s", &left, right);

        prod[i][0] = left;
        prod[i][1] = '=';
        strcpy(prod[i] + 2, right);
    }

    /* FIRST */
    for (i = 0; i < n; i++)
    {
        char symbol = prod[i][0];

        if (first[symbol - 'A'][0] == '\0')
            findFirst(symbol, first[symbol - 'A']);
    }

    printf("\nFIRST:\n");

    for (i = 0; i < n; i++)
    {
        char symbol = prod[i][0];

        if (i == 0 || prod[i][0] != prod[i - 1][0])
        {
            printf("FIRST(%c) = { ", symbol);

            for (int j = 0; first[symbol - 'A'][j] != '\0'; j++)
            {
                printf("%c", first[symbol - 'A'][j]);

                if (first[symbol - 'A'][j + 1] != '\0')
                    printf(", ");
            }

            printf(" }\n");
        }
    }

    /* FOLLOW */
    for (i = 0; i < n; i++)
    {
        char symbol = prod[i][0];

        if (follow[symbol - 'A'][0] == '\0')
            findFollow(symbol, follow[symbol - 'A']);
    }

    printf("\nFOLLOW:\n");

    for (i = 0; i < n; i++)
    {
        char symbol = prod[i][0];

        if (i == 0 || prod[i][0] != prod[i - 1][0])
        {
            printf("FOLLOW(%c) = { ", symbol);

            for (int j = 0; follow[symbol - 'A'][j] != '\0'; j++)
            {
                printf("%c", follow[symbol - 'A'][j]);

                if (follow[symbol - 'A'][j + 1] != '\0')
                    printf(", ");
            }

            printf(" }\n");
        }
    }

    return 0;
}