// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

    float factor = atof(argv[3]);

    char buffer[HEADER_SIZE];

    fread(buffer, HEADER_SIZE, 1, input);

    fwrite(buffer, HEADER_SIZE, 1, output);

    int16_t buffer2[1];

    while (fread(buffer2, sizeof(int16_t), 1, input) != 0)
    {
        buffer2[0] = buffer2[0] * factor;
        fwrite(buffer2, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
