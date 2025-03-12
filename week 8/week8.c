#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void exitWithError()
{
    printf("Not operator grammar\n");
    exit(0);
}

int isValidOperator(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

int main()
{
    char productions[20][20];
    int numProductions;
    int i, j;
    int isOperatorGrammar = 0;

    printf("Enter number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter the productions:\n");
    for (i = 0; i < numProductions; i++)
    {
        scanf("%s", productions[i]);
    }

    for (i = 0; i < numProductions; i++)
    {
        j = 2;

        while (productions[i][j] != '\0')
        {
            if (productions[i][j] == '$')
            {
                exitWithError();
            }

            if (j == 3 && isValidOperator(productions[i][j]))
            {
                isOperatorGrammar = 1;
            }
            else if (j == 3 && !isValidOperator(productions[i][j]))
            {
                exitWithError();
            }

            j++;
        }
    }

    if (isOperatorGrammar)
    {
        printf("Operator grammar\n");
    }
    else
    {
        printf("Not operator grammar\n");
    }

    return 0;
}