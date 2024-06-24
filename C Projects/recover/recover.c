#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

int main(int argc, char *argv[])
{

    // Check if the command-line argument is correct
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card file for reading
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Image cannot be opened for reading\n");
        return 1;
    }

    // Repeat until the end of the file
    while ()
    {

    }

    // Allocate a memory buffer to store data in it
    int array[BLOCK];

    fopen(array, BLOCK, ,file)

}