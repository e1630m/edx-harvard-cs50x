#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_number(string card)
{
    for (int i = 0; card[i] != '\0'; i++)
        if (!isdigit(card[i]))
        {
            return 0;
        }
    return 1;
}

int luhn(string card, int last_idx)
{
    int sum1 = 0, sum2 = 0;
    for (int i = 0; i <= last_idx; i++)
    {
        if (!(i % 2))
        {
            sum1 += card[last_idx - i] - '0';
        }
        else
        {
            int tmp = (card[last_idx - i] - '0') * 2;
            sum2 += tmp < 10 ? tmp : tmp % 10 + 1;
        }
    }
    return (!((sum1 + sum2) % 10));
}

int main(void)
{
    string card = "Not a number";
    while (!is_number(card))
    {
        card = get_string("Number: ");
    }
    int len = strlen(card), f = card[0] - '0', s = card[1] - '0';
    string brand = "INVALID\n";
    if (luhn(card, len - 1))
    {
        brand = (len == 15 && f == 3 && (s == 4 || s == 7)) ? "AMEX\n" : brand;
        brand = ((len == 13 || len == 16) && f == 4) ? "VISA\n" : brand;
        brand = (len == 16 && f == 5 && s > 0 && s < 6) ? "MASTERCARD\n" : brand;
    }
    printf("%s", brand);
}
