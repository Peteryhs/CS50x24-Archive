#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

long numberp(long c, int order)
{
    int target = (c / (long)pow(10, order - 1)) % 10;
    return target;
}

int main(void)
{
    long c = get_long("hi");
    int order = 12;
    printf("%ld", numberp(c,order));
}

