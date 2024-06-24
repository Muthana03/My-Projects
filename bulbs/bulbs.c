#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

int decimal_to_binary(int n);
void print_bulb(int bit);

int main(void)
{
    // Prompt user for a message
    string message = get_string("Message: ");

    // Convert the message into 8-bit binary code
    int bits[8];

    int i = 0;
    while (message[i] != '\0')
    {
        for (int j = 7; j >= 0 ; j--)
        {
            bits[j] = message[i] % 2;
            message[i] /= 2;
        }
        // Print the 8-bit binary code as bulbs
        for (int j = 0; j < 8 ; j++)
        {
            print_bulb(bits[j]);
        }
        i++;
        printf("\n");
    }





}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}