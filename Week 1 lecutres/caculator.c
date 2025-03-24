#include <stdio.h>
#include <cs50.h>


float add(float a, float b);
float divide(float a, float b);

int main(void)
{
    float z;
    float x = get_int ("x: ");
    float y = get_int("y: ");
    char type = get_char ("Operation: ");
    if (type == 'a')
    {
        z = add(x,y);

    }
    else
    {
        z = divide(x,y);
    }

    printf("%f\n", z);
}

float add(float a, float b)
{
    return a+b;
}

float divide(float a, float b)
{
    return a/b;
}
