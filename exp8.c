#include <stdio.h>
#include <string.h>

#define MAX 20
#define SIZE 20

char states[MAX][SIZE];
int visited[MAX];

int findState(char state[], int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (strcmp(states[i], state) == 0)
            return i;
    }

    return -1;
}

void epsilonClosure(char start[], int n)
{
    FILE *fp;
    char state1[SIZE], input[SIZE], state2[SIZE];
    int stack[MAX];
    int top = -1;
    int startIndex;
    int i;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    startIndex = findState(start, n);

    if (startIndex == -1)
        return;

    visited[startIndex] = 1;
    stack[++top] = startIndex;

    while (top >= 0)
    {
        int current = stack[top--];

        fp = fopen("automata.txt", "r");

        if (fp == NULL)
        {
            printf("\nError: automata.txt not found!\n");
            return;
        }

        while (fscanf(fp, "%s %s %s",
                      state1, input, state2) == 3)
        {
            if (strcmp(states[current], state1) == 0 &&
                strcmp(input, "e") == 0)
            {
                int next = findState(state2, n);

                if (next != -1 && visited[next] == 0)
                {
                    visited[next] = 1;
                    stack[++top] = next;
                }
            }
        }

        fclose(fp);
    }

    printf("\nEpsilon closure of %s = { ", start);

    for (i = 0; i < n; i++)
    {
        if (visited[i])
            printf("%s ", states[i]);
    }

    printf("}\n");
}

int main()
{
    int n, i;

    printf("\nEnter the no of states: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number of states.\n");
        return 1;
    }

    printf("\nEnter the states max = 20\n");

    for (i = 0; i < n; i++)
    {
        scanf("%19s", states[i]);
    }

    for (i = 0; i < n; i++)
    {
        epsilonClosure(states[i], n);
    }

    return 0;
}