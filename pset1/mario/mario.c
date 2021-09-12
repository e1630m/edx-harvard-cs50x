#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int h = -1;
    while (h < 1 || h > 8)
    {
        string tmp = get_string("Height: ");
        for (int i = 0; i < strlen(tmp); i++)
        {
            if (!isdigit(tmp[i]))
            {
                break;
            }
            if (i == strlen(tmp) - 1)
            {
                h = atoi(tmp);
            }
        }
    }

    for (int i = 1; i <= h; i++)
    {
        for (int j = h - i; j > 0; j--)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
