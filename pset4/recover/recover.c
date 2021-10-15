#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

size_t BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("File does not exist\n");
        return 1;
    }
    unsigned char buffer[BLOCK_SIZE];
    FILE *jpg = NULL;
    char fname[8];
    int num_jpgs = 0;
    while (fread(&buffer, 1, BLOCK_SIZE, raw))
    {
        bool is_jpg = (buffer[0] == 0xff && buffer[1] == 0xd8 
                       && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);
        if (is_jpg)
        {
            if (num_jpgs)
            {
                fclose(jpg);
            }
            sprintf(fname, "%03d.jpg", num_jpgs);
            jpg = fopen(fname, "w");
            fwrite(&buffer, 1, BLOCK_SIZE, jpg);
            num_jpgs++;
        }
        if (!is_jpg && num_jpgs)
        {
            fwrite(&buffer, 1, BLOCK_SIZE, jpg);
        }
    }
    fclose(raw);
    fclose(jpg);
    return 0;
}
