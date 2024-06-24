#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string encrypt(string text, int key);

int main(int argc, string argv[])
{
    // Check if command-line argument is correct
    if (argc != 2 || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int i = 0;
    while (argv[1][i] != '\0')
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        i++;
    }

    // Prompt the user for the text
    string plain_text = get_string("plaintext:  ");

    // Encrypt the text and print it
    string cipher_text = encrypt(plain_text, atoi(argv[1]));
    printf("ciphertext: %s\n", cipher_text);
    return 0;
}

string encrypt(string text, int key)
{

    // Encrypt the text by rotating each alphabetic character buy k times
    int i = 0;
    while (text[i] != '\0')
    {
        // If the character is alphabetical, encrypt it
        if (isalpha(text[i]) && islower(text[i]))
        {
            text[i] = ((text[i] - 'a' + key) % 26) + 'a';
        }
        else if (isalpha(text[i]) && isupper(text[i]))
        {
            text[i] = ((text[i] - 'A' + key) % 26) + 'A';
        }
        // Else, leave it as it is
        i++;
    }
    return text;
}