#include <stdio.h>
#include <string.h>

char stack[100], input[100];
int top = -1;

void print_state(int i, const char *action)
{
    printf("%-15s %-15s %s\n", stack, &input[i], action);
}

void reduce(int i)
{
    if (top >= 1 && stack[top - 1] == 'i' && stack[top] == 'd')
    {
        stack[top - 1] = 'E';
        top--;
        stack[top + 1] = '\0';
        print_state(i, "REDUCE->id to E");
    }
    else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E')
    {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        print_state(i, "REDUCE->E+E to E");
    }
    else if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E')
    {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        print_state(i, "REDUCE->E*E to E");
    }
    else if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')')
    {
        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        print_state(i, "REDUCE->(E) to E");
    }
}

int main()
{
    int i = 0;
    printf("Grammar:\nE → id\nE → E + E\nE → E * E\nE → (E)\n");
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    strcat(input, "$");
    stack[++top] = '$';
    stack[top + 1] = '\0';
    printf("\n%-15s %-15s %s\n", "stack", "input", "action");

    while (input[i] != '$')
    {
        if (input[i] == 'i' && input[i + 1] == 'd')
        {
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top + 1] = '\0';
            print_state(i, "SHIFT->id");
            i += 2;
            reduce(i);
        }
        else
        {
            stack[++top] = input[i];
            stack[top + 1] = '\0';
            char action[20];
            sprintf(action, "SHIFT->%c", input[i]);
            print_state(i, action);
            i++;
        }
        int prev_top;
        do
        {
            prev_top = top;
            reduce(i);
        } while (top != prev_top && top > 0);
    }
    print_state(i, "");
    if (top == 1 && stack[1] == 'E')
    {
        printf("Input accepted\n");
    }
    else
    {
        printf("Input rejected\n");
    }
    return 0;
}