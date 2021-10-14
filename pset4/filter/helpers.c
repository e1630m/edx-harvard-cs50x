#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int gray;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            gray = round((image[r][c].rgbtRed + image[r][c].rgbtGreen + image[r][c].rgbtBlue) / 3.0);
            image[r][c].rgbtRed = image[r][c].rgbtGreen = image[r][c].rgbtBlue = gray;
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

// edges helper
int limited_rsp(int x, int y)
{
    int rspsum = round(sqrt(pow(x, 2) + pow(y, 2)));
    return rspsum > 255 ? 255 : rspsum;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE detected[height][width];
    int sob[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int rx, ry, gx, gy, bx, by, tr, tg, tb;
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            rx = ry = gx = gy = bx = by = 0;
            for (int dr = -1; dr < 2; dr++)
            {
                for (int dc = -1; dc < 2; dc++)
                {
                    int nr = r + dr, nc = c + dc, ir = dr + 1, ic = dc + 1;
                    if (nr >= 0 && nr < height && nc >= 0 && nc < width)
                    {
                        rx += image[nr][nc].rgbtRed   * sob[ir][ic];
                        ry += image[nr][nc].rgbtRed   * sob[ic][ir];
                        gx += image[nr][nc].rgbtGreen * sob[ir][ic];
                        gy += image[nr][nc].rgbtGreen * sob[ic][ir];
                        bx += image[nr][nc].rgbtBlue  * sob[ir][ic];
                        by += image[nr][nc].rgbtBlue  * sob[ic][ir];
                    }
                }
            }
            detected[r][c].rgbtRed   = limited_rsp(rx, ry);
            detected[r][c].rgbtGreen = limited_rsp(gx, gy);
            detected[r][c].rgbtBlue  = limited_rsp(bx, by);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = detected[i][j];
        }
    }
}
