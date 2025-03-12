#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 20

void regex_to_nfa(char *regex)
{
    // Initialize transition table with empty characters
    char t[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            t[i][j] = '\0';
        }
    }

    int n = strlen(regex);
    int r = 0; // Current state
    int i = 0;

    while (i < n)
    {
        if (regex[i] == '|')
        {
            // Handle OR operation
            t[r][r + 1] = 'E';
            t[r + 1][r + 2] = regex[i - 1];
            t[r + 2][r + 5] = 'E';
            t[r][r + 3] = 'E';
            t[r + 3][r + 4] = regex[i + 1];
            t[r + 4][r + 5] = 'E';
            r += 5; // Set r to 5 for OR operation
            i += 2;
        }
        else if (regex[i] == '*')
        {
            // Handle Kleene closure
            t[r - 1][r] = 'E';
            t[r][r + 1] = 'E';
            t[r][r + 3] = 'E';
            t[r + 1][r + 2] = regex[i - 1];
            t[r + 2][r + 1] = 'E';
            t[r + 2][r + 3] = 'E';
            r += 3;
            i++;
        }
        else if (regex[i] == '+')
        {
            // Handle one or more occurrences
            t[r][r + 1] = regex[i - 1];
            t[r + 1][r] = 'E';
            r++;
            i++;
        }
        else
        {
            // Handle regular characters
            if (i + 1 < n && regex[i + 1] != '|' &&
                regex[i + 1] != '*' && regex[i + 1] != '+')
            {
                t[r][r + 1] = regex[i];
                t[r + 1][r + 2] = regex[i + 1];
                r += 2;
                i += 2;
            }
            else
            {
                t[r][r + 1] = regex[i];
                r++;
                i++;
            }
        }
    }

    // Print the transition table
    printf("\nTransition Table:\n");
    printf("   ");
    for (i = 0; i <= r; i++)
    {
        printf("%3d", i);
    }
    printf("\n");

    for (i = 0; i <= r; i++)
    {
        printf("%2d ", i);
        for (int j = 0; j <= r; j++)
        {
            if (t[i][j] != '\0')
            {
                printf("%3c", t[i][j]);
            }
            else
            {
                printf(" - ");
            }
        }
        printf("\n");
    }

    printf("\nStart state: 0\n");
    printf("End state: %d\n", r);
}

int main()
{
    char regex[MAX_SIZE];
    printf("Enter regex: ");
    scanf("%s", regex);
    regex_to_nfa(regex);
    return 0;
}