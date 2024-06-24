#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

float readability(string s);

int main(void)
{
    // Prompt the user for the text
    string text = get_string("Text: ");

    // Calculate Coleman-Liau index
    float index = readability(text);

    // Print the matching grade level for the text
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.f\n", round(index));
    }

}

float readability(string s)
{
    // Calculate the number of letters, words and sentences in the text
    int i = 0, letters = 0, words = 1, sentences = 0;
    while (s[i] != '\0')
    {
        if (isalpha(s[i]))
        {
            letters++;
        }
        else if (isspace(s[i]))
        {
            words++;
        }
        else if (s[i] == '.' || s[i] == '?' || s[i] == '!')
        {
            sentences++;
        }
        i++;
    }

    // Calculate letters per 100 words, and sentences per 100 words
    float L = ((float) letters / words) * 100.0;
    float S = ((float) sentences / words) * 100.0;

    // Return the index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    return (index);
}
