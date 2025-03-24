#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *input = fopen(argv[1], "r");
    unsigned char buffer[512];
    int counter = 0;
    FILE *file = NULL;
    char filename[8];
    if (input == NULL)
    {
        return 1;
    }
    while (fread(buffer, 512, 1, input) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (counter != 0)
            {
                fclose(file); // close file
            }

            // update counter
            sprintf(filename, "%03d.jpg", counter);
            file = fopen(filename, "w");
            counter++;
        }

        if (file != NULL)
        {
            fwrite(buffer, 512, 1, file);
        }
    }

    if (file != NULL)
    {
        fclose(file);
    }

    fclose(input);
    return 0;
}
