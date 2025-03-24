#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int amount = get_int("Amount: ");
    float sum = 0;
    int scores[amount];
    for (int i =0; i<amount; i++)
    {
        scores[i] = get_int("Enter mark: ");
        sum += scores[i];
    }
    float avg = sum/amount;
    printf("Avg: %f\n", avg);

}
