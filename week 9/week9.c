#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
char stack[100], temp[10], top = -1;
char ter[6] = {'i', '+', '*', ')', '(', '$'};
char nter[3] = {'E', 'T', 'F'};
char states[12] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'm', 'j', 'k', 'l'};

// Action table - compressed format
const char *actionTable[12][6] = {
    {"sf", "emp", "emp", "se", "emp", "emp"}, {"emp", "sg", "emp", "emp", "emp", "acc"}, {"emp", "rc", "sh", "emp", "rc", "rc"}, {"emp", "re", "re", "emp", "re", "re"}, {"sf", "emp", "emp", "se", "emp", "emp"}, {"emp", "rg", "rg", "emp", "rg", "rg"}, {"sf", "emp", "emp", "se", "emp", "emp"}, {"sf", "emp", "emp", "se", "emp", "emp"}, {"emp", "sg", "emp", "emp", "sl", "emp"}, {"emp", "rb", "sh", "emp", "rb", "rb"}, {"emp", "rb", "rd", "emp", "rd", "rd"}, {"emp", "rf", "rf", "emp", "rf", "rf"}};

// Goto table - compressed format
const char *gotoTable[12][3] = {
    {"b", "c", "d"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}, {"i", "c", "d"}, {"emp", "emp", "emp"}, {"emp", "j", "d"}, {"emp", "emp", "k"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}};

// Grammar rules
struct
{
    char left;
    char right[5];
} grammar[6] = {
    {'E', "e+T"}, {'E', "T"}, {'T', "T*F"}, {'T', "F"}, {'F', "(E)"}, {'F', "i"}};

// Function declarations
void push(char item) { stack[++top] = item; }
char pop() { return stack[top--]; }
char stacktop() { return stack[top]; }

// Find indices in tables
int ister(char x)
{
    for (int i = 0; i < 6; i++)
        if (x == ter[i])
            return i + 1;
    return 0;
}
int isnter(char x)
{
    for (int i = 0; i < 3; i++)
        if (x == nter[i])
            return i + 1;
    return 0;
}
int isstate(char p)
{
    for (int i = 0; i < 12; i++)
        if (p == states[i])
            return i + 1;
    return 0;
}

// Get production from tables
void isproduct(char x, char p)
{
    int k = ister(x), l = isstate(p);
    strcpy(temp, (k > 0 && l > 0) ? actionTable[l - 1][k - 1] : "emp");
}

void isreduce(char x, char p)
{
    int k = isstate(x), l = isnter(p);
    strcpy(temp, (k > 0 && l > 0) ? gotoTable[k - 1][l - 1] : "emp");
}

// Print state in numeric form
void printState(char c)
{
    switch (c)
    {
    case 'a':
        printf("0");
        break;
    case 'b':
        printf("1");
        break;
    case 'c':
        printf("2");
        break;
    case 'd':
        printf("3");
        break;
    case 'e':
        printf("4");
        break;
    case 'f':
        printf("5");
        break;
    case 'g':
        printf("6");
        break;
    case 'h':
        printf("7");
        break;
    case 'm':
        printf("8");
        break;
    case 'j':
        printf("9");
        break;
    case 'k':
        printf("10");
        break;
    case 'l':
        printf("11");
        break;
    default:
        printf("%c", c);
    }
}

// Print stack and input
void printt(char inp[], int i)
{
    printf("\n");
    for (int r = 0; r <= top; r++)
        printState(stack[r]);
    printf("\t\t\t");
    printf("%s", inp + i);
}

// Error handling
void error()
{
    printf(" error in the input ");
    exit(0);
}

int main()
{
    char input[80], x, p, dl[2] = {0};
    int i = 0, j, k, n;

    printf(" Enter the input: ");
    scanf("%s", input);

    strcat(input, "$"); // Append end marker
    push('a');          // Initialize stack with start state

    printf("\n stack \t\t\t input");
    printt(input, i);

    while (1)
    {
        x = input[i];
        p = stacktop();
        isproduct(x, p);

        if (strcmp(temp, "emp") == 0)
            error();
        if (strcmp(temp, "acc") == 0)
            break;

        if (temp[0] == 's')
        {
            // Shift operation
            push(input[i++]);
            push(temp[1]);
        }
        else
        {
            // Reduce operation
            j = isstate(temp[1]);
            strcpy(temp, grammar[j - 2].right);
            dl[0] = grammar[j - 2].left;
            n = strlen(temp);

            // Pop 2 * length of right side
            for (k = 0; k < 2 * n; k++)
                pop();

            push(dl[0]);
            isreduce(stack[top - 1], dl[0]);
            push(temp[0]);
        }

        printt(input, i);
    }

    printf("\n %s the input", strcmp(temp, "acc") == 0 ? "accept" : "do not accept");
    return 0;
}