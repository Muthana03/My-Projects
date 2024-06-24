#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

#define HEADER_SIZE 44

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
void reverseAudioData(FILE *input, FILE *output, int BlockSize);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        printf("No enough memory to open the input file\n");
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, inputFile);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Input is not a WAV file\n");
        return 1;
    }

    // Open output file for writing
    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL)
    {
        printf("No enough memory to open the output file\n");
        return 1;
    }

    // Write header to file
    fwrite(&header, HEADER_SIZE, 1, outputFile);

    // Use get_block_size to calculate size of block
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    reverseAudioData(inputFile, outputFile, blockSize);

    // Close files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

int check_format(WAVHEADER header)
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 1;
    }

    return 0;
}

int get_block_size(WAVHEADER header)
{
    // Calculate bytes per sample
    int bytesPerSample = (header.bitsPerSample / 8);

    // return block size
    return (header.numChannels * bytesPerSample);
}

void reverseAudioData(FILE *input, FILE *output, int BlockSize)
{
    // Set the Output File Pointer and the Input File Pointer to thier right places again
    fseek(input, BlockSize, SEEK_END);
    fseek(output, HEADER_SIZE, SEEK_SET);

    BYTE c[BlockSize];
    // Iterate over input until you reach the last byte in the header
    while (ftell(input) - BlockSize > HEADER_SIZE)
    {
        // Move the File-Pointer cursor
        fseek(input, (-2 * BlockSize), SEEK_CUR);

        // Copy data in reverse order
        fread(c, BlockSize, 1, input);
        fwrite(c, BlockSize, 1, output);
    }
}