#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string encipher(string text, string key);

int main(int argc, string argv[])
{
    // Check the validity of command-line argument

    // Check the number of the arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Check if the key contains 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    int k = 0;
    while (argv[1][k] != '\0')
    {
        // Check if each character of the key is an alphabetical character
        if (isalpha(argv[1][k]) == false)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        // Change the key characters into uppercase letters
        argv[1][k] = toupper(argv[1][k]);
        k++;
    }
    string key = argv[1];

    // Check if there are any repeated characters
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (key[i] == key[j])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }

    // Prompt the user for text
    string plaintext = get_string("plaintext:  ");

    // Encipher the text and print it
    string ciphertext = encipher(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

string encipher(string text, string key)
{
    // Encipher the text using the key
    int i = 0;
    while (text[i] != '\0')
    {
        if (isalpha(text[i]) && isupper(text[i]))
        {
            // If the character is in uppercase, it stays in uppercase
            text[i] = key[text[i] - 'A'];
        }
        else if (isalpha(text[i]) && islower(text[i]))
        {
            // If the character is in lowercase, convert the ciphertext to lowercase
            text[i] = tolower(key[text[i] - 'a']);
        }
        i++;
    }
    return text;
}