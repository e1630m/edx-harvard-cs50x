#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    string key = argv[1];
    for (int i = 0; i < 26; i++)
    {
        if (isalpha(key[i]))
        {
            key[i] = tolower(key[i]);
        }
        else
        {
            printf("Key must be alphabetical.");
            return 1;
        }

        int count = 0;
        for (int j = 0; j < 26; j++)
        {
            if (key[i] == tolower(key[j]))
            {
                count++;
            }
        }
        if (count > 1)
        {
            printf("No duplicates");
            return 1;
        }
    }
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            if (!isupper(plain[i]))
            {
                printf("%c", key[plain[i] - 'a']);
            }
            else
            {
                printf("%c", toupper(key[plain[i] - 'A']));
            }
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
}
