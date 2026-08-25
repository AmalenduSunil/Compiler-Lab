%{
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    char filename[20];
    FILE *f;
%}

%%

[a-zA-Z]+    { charCount += yyleng; wordCount++; }
\n           { lineCount++; charCount++; }
.            { charCount++; }

%%

int yywrap(void)
{
    return 1;
}

int main()
{
    printf("Enter filename:\n");
    scanf("%s", filename);

    f = fopen(filename, "r");

    if (f == NULL)
    {
        printf("File cannot be opened.\n");
        return 1;
    }

    yyin = f;
    yylex();

    printf("\nNo. of lines: %d\n", lineCount);
    printf("No. of words: %d\n", wordCount);
    printf("No. of characters: %d\n", charCount);

    fclose(f);

    return 0;
}