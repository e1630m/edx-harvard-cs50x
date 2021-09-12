#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string t = get_string("Text: ");
    int l = 0, w = 1, s = 1;
    for (int i = 0; i < strlen(t); i++)
    {
        int letter = isalpha(t[i]) / 1024;
        int word = t[i] == ' ';
        int sentence = (t[i] == '.' || t[i] == '?' || t[i] == '!') && (t[i + 1] == ' ');
        l += letter;
        w += word;
        s += sentence;
    }
    float fl = (float) l, fw = (float) w, fs = (float) s;
    float idx = 0.0588 * (fl / fw * 100.0) - 0.296 * (fs / fw * 100.0) - 15.8;
    int grade = round(idx);
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}
