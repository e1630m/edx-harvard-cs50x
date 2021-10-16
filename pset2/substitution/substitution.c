#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        string err = argc != 2 ? "Usage: ./substitution key" : "Key must contain 26 characters.";
        printf("%s\n", err);
        return 1;
    }
    string key = argv[1];
    int count[26] = {};
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must be alphabetical.\n");
            return 1;
        }
        key[i] = tolower(key[i]);
        if (++count[key[i] - 'a'] > 1)
        {
            printf("Duplicated key is not allowed.\n");
            return 1;
        }
    }
    string plain = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plain); i++)
    {
        char to_print = plain[i];
        to_print = !isalpha(to_print) ? to_print : isupper(plain[i]) ? 
                   toupper(key[plain[i] - 'A']) : key[plain[i] - 'a'];
        printf("%c", to_print);
    }
    printf("\n");
}
