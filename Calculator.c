#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void removeWhitespaces(char *exp)
{
    char *p = exp;
    char *q = exp;
    while (*q != '\0')
    {
        if (!isspace(*q))
        {
            *p++ = *q;
        }
        q++;
    }
    *p = '\0';
};

bool checkValidity(char *exp)
{
    for (int i = 0; exp[i] != '\0'; i++)
    {
        if (i % 2 == 0)
        {
            if (!(exp[i] >= '0' && exp[i] <= '9'))
            {
                return false;
            }
        }
        else
        {
            if (!(exp[i] == '+' || exp[i] == '*' || exp[i] == '-' || exp[i] == '/'))
            {
                return false;
            }
        }
        if (exp[i] == '/' && exp[i + 1] == '0')
        {
            return false;
        }
    }

    // Check if expression ends with a digit
    int len = strlen(exp);
    if (!(exp[len - 1] >= '0' && exp[len - 1] <= '9'))
    {
        return false;
    }
    return true;
}

int calculate(const char *s)
{
    int stack[100];      // Stack to store intermediate results
    int top = -1;        // Top of the stack
    char sign = '+';     // Current operator
    int num = 0;         // Current number
    int i = 0;           // Iterator for the string
    int len = strlen(s); // Length of the input string

    for (i = 0; i < len; i++)
    {
        char c = s[i];

        // Build the current number
        if (isdigit(c))
        {
            num = num * 10 + (c - '0');
        }

        // If the current character is an operator or the end of the string
        if (!isdigit(c) && c != ' ' || i == len - 1)
        {
            if (sign == '+')
            {
                stack[++top] = num;
            }
            else if (sign == '-')
            {
                stack[++top] = -num;
            }
            else if (sign == '*')
            {
                stack[top] = stack[top] * num;
            }
            else if (sign == '/')
            {
                stack[top] = stack[top] / num;
            }

            // Update the operator and reset the number
            sign = c;
            num = 0;
        }
    }

    // Sum all elements in the stack
    int result = 0;
    for (i = 0; i <= top; i++)
    {
        result += stack[i];
    }

    return result;
}

int main()
{
    char exp[100];
    fgets(exp, 100, stdin);
    removeWhitespaces(exp);
    if (checkValidity(exp))
    {
        int result = calculate(exp);
        printf("Result: %d\n", result);
    }
    else
    {
        printf("invalid expression\n");
    };
    return 0;
}