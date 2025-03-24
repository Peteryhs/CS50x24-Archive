#include <cs50.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

int bank(long c);
string length(long c);
int size(long c);
bool checksum(long c);
int numberp(long c, int order);

int main(void)
{
    long c = get_long("NUMBER: ");

    printf("%s\n", length(c));
}

string length(long c)
{
    if (size(c) == 15 && (bank(c) == 34 || bank(c) == 37) && checksum(c))
    {
        return "AMEX";
    }
    else if ((size(c) == 13) && ((bank(c) / 10) == 4) && checksum(c))
    {
        return "VISA";
    }
    else if (size(c) == 16)
    {
        if (((bank(c) / 10) == 4) && checksum(c))
        {
            return "VISA";
        }
        else if ((bank(c) == 51 || bank(c) == 52 || bank(c) == 53 || bank(c) == 54 ||
                  bank(c) == 55) &&
                 checksum(c))
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        }
    }
    else
    {
        return "INVALID";
    }
}

int size(long c)
{
    int count = 0;
    while (c > 1)
    {
        c /= 10;
        count++;
    }
    return count;
}

int bank(long c)
{

    while (c > 100)
    {
        c /= 10;
    }

    return c;
}

int numberp(long c, int order)
{
    int target = (c / (long) pow(10, order - 1)) % 10;
    return target;
}

bool checksum(long c)
{
    int odd = 0;
    int even = 0;
    int order = 1;

    for (int k = 0; k < size(c); k++)
    {
        if (order % 2 == 0)
        {
            if ((numberp(c, order) * 2) < 10)
            {
                even += (numberp(c, order) * 2);
            }
            else
            {
                int t = (numberp(c, order) * 2);
                even += (numberp(t, 1));
                even += (numberp(t, 2));
            }
        }
        else
        {
            odd += numberp(c, order);
        }

        order++;
    }
    if ((odd + even) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
