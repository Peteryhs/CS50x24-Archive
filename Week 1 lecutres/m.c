#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int ("Size :");
    }
    while (n<1);

    for (int i = 0 ; i < n ; i++)
    {
        for (int r = 0 ; r < (n-i) ; r++)
        {
            printf(" ");
        }
        for (int j = 0 ; j < i ; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int y = 0 ; y < i ; y++)
        {
            printf("#");
        }
        printf("\n");
    }
}

