#include <stdio.h>

#define MAX 20

int n, symbols;
char input[MAX];
int nfa[MAX][MAX][MAX];
int dfa[MAX][MAX];

int states[MAX];
int newStateCount = 0;

int isSame(int a[], int b[])
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 0;
    }

    return 1;
}

int findState(int set[])
{
    int i;

    for (i = 0; i < newStateCount; i++)
    {
        int temp[MAX] = {0};
        int j;

        /* Reconstructing is not needed because states
           are stored separately below */
    }

    return -1;
}

int main()
{
    int t;
    int i, j, k;
    int from, to;
    char ch;

    int dfaStates[MAX][MAX];
    int dfaTrans[MAX][MAX];
    int final[MAX];

    printf("Enter number of NFA states : ");
    scanf("%d", &n);

    printf("Enter number of input symbols : ");
    scanf("%d", &symbols);

    printf("Enter input symbols : ");
    for (i = 0; i < symbols; i++)
        scanf(" %c", &input[i]);

    printf("Enter number of transitions : ");
    scanf("%d", &t);

    printf("Enter transitions in format state symbol state :\n");

    for (i = 0; i < t; i++)
    {
        scanf("%d %c %d", &from, &ch, &to);

        for (j = 0; j < symbols; j++)
        {
            if (input[j] == ch)
            {
                nfa[from][to][j] = 1;
                break;
            }
        }
    }

    printf("Enter final state : ");
    scanf("%d", &to);

    final[to] = 1;

    /* Initial DFA state = {0} */
    for (i = 0; i < n; i++)
        dfaStates[0][i] = 0;

    dfaStates[0][0] = 1;
    newStateCount = 1;

    /* Subset construction */
    for (i = 0; i < newStateCount; i++)
    {
        for (j = 0; j < symbols; j++)
        {
            int result[MAX] = {0};

            /* Find all NFA destinations */
            for (k = 0; k < n; k++)
            {
                if (dfaStates[i][k])
                {
                    int p;

                    for (p = 0; p < n; p++)
                    {
                        if (nfa[k][p][j])
                            result[p] = 1;
                    }
                }
            }

            /* Check whether result is already a DFA state */
            int found = -1;

            for (k = 0; k < newStateCount; k++)
            {
                if (isSame(result, dfaStates[k]))
                {
                    found = k;
                    break;
                }
            }

            /* If new state, add it */
            if (found == -1)
            {
                found = newStateCount;

                for (k = 0; k < n; k++)
                    dfaStates[newStateCount][k] = result[k];

                newStateCount++;
            }

            dfaTrans[i][j] = found;
        }
    }

    printf("\nDFA Transitions\n");

    for (i = 0; i < newStateCount; i++)
    {
        for (j = 0; j < symbols; j++)
        {
            printf("{");

            for (k = 0; k < n; k++)
            {
                if (dfaStates[i][k])
                    printf("%d", k);
            }

            printf("} %c {", input[j]);

            for (k = 0; k < n; k++)
            {
                if (dfaStates[dfaTrans[i][j]][k])
                    printf("%d", k);
            }

            printf("}\n");
        }
    }

    /* Print DFA final states */
    printf("\nDFA Final States : ");

    for (i = 0; i < newStateCount; i++)
    {
        int isFinal = 0;

        for (j = 0; j < n; j++)
        {
            if (dfaStates[i][j] && final[j])
            {
                isFinal = 1;
                break;
            }
        }

        if (isFinal)
        {
            printf("{");

            for (j = 0; j < n; j++)
            {
                if (dfaStates[i][j])
                    printf("%d", j);
            }

            printf("} ");
        }
    }

    printf("\n");

    return 0;
}