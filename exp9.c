#include <stdio.h>

#define MAX 20

int trans[MAX][MAX][26];
int eps[MAX][MAX];
int closure[MAX][MAX];
int n = 0;

void findClosure(int s)
{
    int stack[MAX], top = -1;
    int i, v;

    for (i = 0; i < n; i++)
        closure[s][i] = 0;

    closure[s][s] = 1;
    stack[++top] = s;

    while (top >= 0)
    {
        v = stack[top--];

        for (i = 0; i < n; i++)
        {
            if (eps[v][i] && !closure[s][i])
            {
                closure[s][i] = 1;
                stack[++top] = i;
            }
        }
    }
}

int main()
{
    int t, i, j, k, p;
    int from, to, finalState;
    char symbol;

    printf("Enter no. of transitions : ");
    scanf("%d", &t);

    printf("Enter transitions in format state symbol state :\n");

    for (i = 0; i < t; i++)
    {
        scanf("%d %c %d", &from, &symbol, &to);

        if (from >= n)
            n = from + 1;

        if (to >= n)
            n = to + 1;

        if (symbol == 'e')
            eps[from][to] = 1;
        else
            trans[from][to][symbol - 'a'] = 1;
    }

    printf("Final states : ");
    scanf("%d", &finalState);

    /* Find epsilon closure of every state */
    for (i = 0; i < n; i++)
        findClosure(i);

    printf("\nNFA Transitions\n");

    /*
       δ'(q,a) =
       ε-closure(δ(ε-closure(q),a))
    */

    for (i = 0; i < n; i++)
    {
        for (k = 0; k < 26; k++)
        {
            int result[MAX] = {0};
            int found = 0;

            /* Find states in epsilon closure */
            for (j = 0; j < n; j++)
            {
                if (closure[i][j])
                {
                    /* Follow transition on symbol */
                    for (p = 0; p < n; p++)
                    {
                        if (trans[j][p][k])
                        {
                            found = 1;

                            /* Take epsilon closure again */
                            int x;
                            for (x = 0; x < n; x++)
                            {
                                if (closure[p][x])
                                    result[x] = 1;
                            }
                        }
                    }
                }
            }

            if (found)
            {
                printf("%d %c ", i, 'a' + k);

                for (j = 0; j < n; j++)
                {
                    if (result[j])
                        printf("%d", j);
                }

                printf("\n");
            }
        }
    }

    /*
       New final states:
       A state becomes final if its epsilon closure
       contains the original final state.
    */

    printf("Final states : {");

    for (i = 0; i < n; i++)
    {
        if (closure[i][finalState])
            printf("%d", i);
    }

    printf("}\n");

    return 0;
}