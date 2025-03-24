#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char c = get_char("Are you Sigma?\n");

    if (c == 'y' || c == 'Y')
    {
        printf("Thats very sigma.\n");
    }
    else if (c == 'n' || c == 'N')
    {
        printf("Thats so skibidi.\n");
    }
}
