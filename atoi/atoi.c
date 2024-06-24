#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int i = strlen(input) - 1;
    int x = 0;
    int counter = 0;

    while (i >= 0)
    {
        x = x + pow(10, counter) * (input[i] - '0');
        counter++;
        i--;
    }

    return x;
}