#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_number(char *s)
{
    for (; *s != '\0'; s++)
    {
        if (!isdigit(*s))
        {
            return 0;
        }
    }
    return 1;
}


int main(int argc, char *argv[])
{
    if (argc != 2 || !is_number(argv[1]) || atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            int modifier = isupper(plain[i]) ? 'A' : 'a';
            printf("%c", ((plain[i] - modifier) + key) % 26 + modifier);
            continue;
        }
        printf("%c", plain[i]);
    }
    printf("\n");
}
