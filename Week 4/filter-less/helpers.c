#include "helpers.h"
#include <math.h>

// Convert image to grayscale

#define min(a, b) ((a) < (b) ? (a) : (b))

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg =
                round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            BYTE result = (BYTE) avg;
            image[i][j].rgbtBlue = result;
            image[i][j].rgbtRed = result;
            image[i][j].rgbtGreen = result;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = (int) image[i][j].rgbtRed;
            int originalBlue = (int) image[i][j].rgbtBlue;
            int originalGreen = (int) image[i][j].rgbtGreen;
            BYTE blue =
                round(min(.272 * originalRed + .534 * originalGreen + .131 * originalBlue, 255));
            BYTE red =
                round(min(.393 * originalRed + .769 * originalGreen + .189 * originalBlue, 255));
            BYTE green =
                round(min(.349 * originalRed + .686 * originalGreen + .168 * originalBlue, 255));

            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int counter = 0;
            int bRed = 0;
            int bBlue = 0;
            int bGreen = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if (i + k < 0 || i + k >= height || j + x < 0 || j + x >= width)
                    {
                        continue;
                    }
                    else
                    {
                        bRed += copy[i + k][j + x].rgbtRed;
                        bBlue += copy[i + k][j + x].rgbtBlue;
                        bGreen += copy[i + k][j + x].rgbtGreen;
                        counter++;
                    }
                }
            }
            bRed = round((float) bRed / counter);
            bBlue = round((float) bBlue / counter);
            bGreen = round((float) bGreen / counter);

            image[i][j].rgbtBlue = (BYTE) bBlue;
            image[i][j].rgbtRed = (BYTE) bRed;
            image[i][j].rgbtGreen = (BYTE) bGreen;
        }
    }
    return;
}
