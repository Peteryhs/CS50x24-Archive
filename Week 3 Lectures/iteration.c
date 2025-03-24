#include <cs50.h>
#include <stdio.h>
#include <string.h>

void draw(int n);

int main(void)
{
    int height = get_int("Hegiht: ");
    draw(height);
}

void draw(int n)
{
    draw(n - 1);
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n")
}
