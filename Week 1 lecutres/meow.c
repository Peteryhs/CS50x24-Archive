#include <stdio.h>
#include <cs50.h>

void meow(int n);

int main(void)
{
    meow(300000000);
}

void meow(int n)
{
    for (int i=0; i<n; i++)
    {
        printf("meow\n");
    }

}
