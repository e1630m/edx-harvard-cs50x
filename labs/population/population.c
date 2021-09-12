#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for start size
    int start = 0;
    do
    {
        start = get_int("Start size: ");
    }
    while (start < 9);

    // Prompt for end size
    int end = 0;
    do
    {
        end = get_int("End size: ");
    }
    while (end < start);

    // Calculate number of years until we reach threshold
    int years = 0;
    for (; start < end; years++)
    {
        int births = start / 3, deaths = start / 4;
        start += births - deaths;
    }

    // Print number of years
    printf("Years: %i", years);
}
