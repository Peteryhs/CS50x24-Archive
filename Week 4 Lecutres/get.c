#include <stdio.h>

int main(void)
{
    char s[4];
    printf("s: ");
    scanf("%s", s ); //string is already an adress so no & required
    printf("%s\n", s);
}
