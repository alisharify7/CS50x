// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//defind data type
typedef uint8_t BYTE88;
typedef int16_t BYTE166;


// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    //read header from file
    float factor = atof(argv[3]);
    BYTE88 header[HEADER_SIZE];
    fread(header, sizeof(BYTE8), HEADER_SIZE, input);
    fwrite(header, sizeof(BYTE8), HEADER_SIZE, output);
    
    //read each byte
    BYTE166 buffer;
    while (fread(&buffer, sizeof(BYTE16), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(BYTE16), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
