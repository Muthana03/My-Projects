#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user to enter the highet
    int n;
    do
    {
        n = get_int("Highet: ");
    }
    while (n < 1 || n > 8);

    // Rows
    for (int i = 1; i <= n; i++)
    {
        // Columns

        // Making the first pyramid
        for (int j = n; j > i; j--)
        {
            printf(" ");
        }
        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        // Making the 2-width gap
        printf("  ");

        // Making the second pyramid
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
