
#include <cs50.h>
#include <stdio.h>

int main()
{
    // Prompting the user for their name
    string name = get_string("What's your name? ");

    // Saying hello to the user :)
    printf("hello, %s\n", name);

    return 0;
}
