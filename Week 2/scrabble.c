#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string words[2];
    words[0] = get_string("Player 1: ");
    words[1] = get_string("Player 2: ");
    int score[2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0, n = strlen(words[i]); j < n; j++)
        {
            words[i][j] = toupper(words[i][j]);
            if (words[i][j] == 'D' || words[i][j] == 'G')
            {
                score[i] += 2;
            }
            else if (words[i][j] == 'B' || words[i][j] == 'C' || words[i][j] == 'M' ||
                     words[i][j] == 'P')
            {
                score[i] += 3;
            }
            else if (words[i][j] == 'F' || words[i][j] == 'H' || words[i][j] == 'V' ||
                     words[i][j] == 'W' || words[i][j] == 'Y')
            {
                score[i] += 4;
            }
            else if (words[i][j] == 'K')
            {
                score[i] += 5;
            }
            else if (words[i][j] == 'J' || words[i][j] == 'X')
            {
                score[i] += 8;
            }
            else if (words[i][j] == 'Q' || words[i][j] == 'Z')
            {
                score[i] += 10;
            }
            else if (isalpha(words[i][j]))
            {
                score[i] += 1;
            }
        }
    }
    if (score[0] > score[1])
    {
        printf("Player 1 wins!");
    }
    else if (score[0] < score[1])
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
    printf("\n");
}
