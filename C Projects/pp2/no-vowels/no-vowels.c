// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string s);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Command-line argument error\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}

string replace(string s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        switch (s[i])
        {
        case 'a':
            s[i] = '6';
            break;

        case 'e':
            s[i] = '3';
            break;

        case 'i':
            s[i] = '1';
            break;

        case 'o':
            s[i] = '0';
            break;
        }
        i++;
    }
    return s;
}
