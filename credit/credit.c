#include <cs50.h>
#include <stdio.h>

bool Checksum(long n, int d)
{
    long temp = n;
    n = n / 10; // starting from the second to last digit
    int digit;
    int sum1 = 0;
    int sum2 = 0;
    // calculating the sum of every other digit multiplied by 2
    //(starting from the second-to-last digit)
    for (int i = 2; i <= d; i = i + 2)
    {
        digit = (n % 10) * 2;
        // sum of the digits of the 2-digit number (18 --> 1+8)
        sum1 = sum1 + (digit / 10) + (digit % 10);
        n = n / 100;
    }

    // rest the value of n to the original
    n = temp;

    // calculating the sum of every other digit
    //(starting from the last digit)
    for (int i = 1; i <= d; i = i + 2)
    {
        digit = n % 10;
        sum2 = sum2 + digit;
        n = n / 100;
    }

    // check whether the summation ends with 0 or not
    if ((sum1 + sum2) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Count(long n)
{
    int counter = 0;
    while (n != 0)
    {
        n = n / 10;
        counter++;
    }
    return counter;
}

int main(void)
{
    // Prompt the user for a credit card number
    long card_number = get_long("Number: ");

    // Calculating the number of digits of the credit card number
    int d = Count(card_number);

    // Checking starting digits and card length and checksum
    if (Checksum(card_number, d) && d == 15 && (card_number / 10000000000000 == 34 || card_number / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if (Checksum(card_number, d) && d == 16 &&
             (card_number / 100000000000000 == 51 || card_number / 100000000000000 == 52 || card_number / 100000000000000 == 53 ||
              card_number / 100000000000000 == 54 || card_number / 100000000000000 == 55))
    {
        printf("MASTERCARD\n");
    }
    else if (Checksum(card_number, d) && (d == 13 || d == 16) &&
             (card_number / 1000000000000000 == 4 || card_number / 1000000000000 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
