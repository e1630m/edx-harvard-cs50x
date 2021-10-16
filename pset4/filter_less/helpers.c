#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int gray = round((image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue) / 3.0);
            image[r][c].rgbtRed = image[r][c].rgbtGreen = image[r][c].rgbtBlue = gray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            int R = image[r][c].rgbtRed, G = image[r][c].rgbtGreen, B = image[r][c].rgbtBlue;
            image[r][c].rgbtRed   = fmin(255, round(.393 * R + .769 * G + .189 * B));
            image[r][c].rgbtGreen = fmin(255, round(.349 * R + .686 * G + .168 * B));
            image[r][c].rgbtBlue  = fmin(255, round(.272 * R + .534 * G + .131 * B));
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width / 2; c++)
        {
            tmp = image[r][c];
            image[r][c] = image[r][width - 1 - c];
            image[r][width - 1 - c] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float rsum, gsum, bsum, num_pixels;
    RGBTRIPLE blurred[height][width];
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            rsum = gsum = bsum = num_pixels = 0.0;
            for (int dr = -1; dr < 2; dr++)
            {
                for (int dc = -1; dc < 2; dc++)
                {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < height && nc >= 0 && nc < width)
                    {
                        rsum += image[nr][nc].rgbtRed;
                        gsum += image[nr][nc].rgbtGreen;
                        bsum += image[nr][nc].rgbtBlue;
                        num_pixels++;
                    }
                }
            }
            blurred[r][c].rgbtRed   = round(rsum / num_pixels);
            blurred[r][c].rgbtGreen = round(gsum / num_pixels);
            blurred[r][c].rgbtBlue  = round(bsum / num_pixels);
        }
    }
    for (int r = 0; r < height; r++)
        for (int c = 0; c < width; c++)
        {
            image[r][c] = blurred[r][c];
        }
}
