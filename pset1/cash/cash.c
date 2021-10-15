#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    float owed = -1.0;
    while (owed < 0)
    {
        owed = get_float("Change owed: ");
    }
    int coins = 0, left = round(owed * 100);
    while (left)
    {
        int change = left >= 25 ? 25 : left >= 10 ? 10 : left >= 5 ? 5 : 1;
        left -= change;
        coins++;
    }
    printf("%d\n", coins);
}
