#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing cmd arg\n");
        return 115;
    }
    printf("Hello, %s\n", argv[1]);
    return 0;
}
