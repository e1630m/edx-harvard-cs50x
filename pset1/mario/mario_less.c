#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_height(string input)
{
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            return -1;
        }
    }
    return atoi(input);
}


int main(void)
{
    char *pyramid = "########";
    int h = -1;
    while (h < 1 || h > 8)
    {
        h = get_height(get_string("Height: "));
    }

    for (int i = 1; i <= h; i++)
    {
        printf("%*s%.*s\n", h - i, "", i, pyramid);
    }
}
