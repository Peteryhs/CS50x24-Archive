#include <cs50.h>
#include <stdio.h>

// modified from the mario.c I wrote in lecutre btw

int main(void)
{
    int n;
    do
    {
        n = get_int("Size :");
    }
    while (n < 1);

    for (int i = 1; i <= n; i++)
    {

        for (int r = 1; r <= n; r++)
        {

            if (r <= (n - i))
            {

                printf(" ");
            }

            else
            {
                printf("#");
            }
        }
        printf("  ");
        for (int y = 1; y <= i; y++)
        {
            printf("#");
        }

        printf("\n");
    }
}
