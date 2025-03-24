#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float avgl(string s);
float avgs(string s);
float wordc = 1;

int main(void)
{
    string text = get_string("Text: ");
    float index;
    if (wordc < 10)
    {
        index = (0.0588 * avgl(text) * 100 - 0.296 * avgs(text) * 100 - 15.8);


    }
    else if (wordc < 100)
    {
        index = (0.0588 * avgl(text) * 10 - 0.296 * avgs(text) * 10 - 15.8);


    }
    else
    {
        index = (0.0588 * avgl(text) - 0.296 * avgs(text) - 15.8);
    }

    if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        int flat = round(index);
        printf("Grade %i", flat);

    }
    printf("\n");
}

float avgl(string s)
{
    float sum = 0;

    for (int j = 0, n = strlen(s); j < n && wordc < 100; j++)
    {
        if (s[j] == ' ')
        {
            wordc++;
        }
        else if (isalpha(s[j]))
        {
            sum++;
        }
    }
    return sum / wordc;

}

float avgs(string s)
{
    float sum = 0;
    float punc = 0;
    for (int j = 0, n = strlen(s); j < n && wordc < 100; j++)
    {
        if (ispunct(s[j]) && (s[j] == '.' || s[j] == '?' || s[j] == '!'))
        {
            punc++;
        }
    }
    return punc / wordc;
}
