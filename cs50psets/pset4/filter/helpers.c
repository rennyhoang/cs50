#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            BYTE tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = tempBlue;
            
            BYTE tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = tempGreen;
            
            BYTE tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = tempRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j +
                                          1].rgbtBlue) / 4.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j +
                                           1].rgbtGreen) / 4.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) /
                                        4.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (i == 0 && j == width - 1)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (i == height - 1 && j == 0)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 4.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 4.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) / 4.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (i == height - 1 && j == width - 1)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 4.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (i == 0)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (i == height - 1)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (j == 0)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else if (j == width - 1)
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
            
            else
            {
                BYTE blueAverage = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
                BYTE greenAverage = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                BYTE redAverage = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
                
                imageCopy[i][j].rgbtBlue = blueAverage;
                imageCopy[i][j].rgbtGreen = greenAverage;
                imageCopy[i][j].rgbtRed = redAverage;
            }
        }
    }
    
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtBlue = imageCopy[k][l].rgbtBlue;
            image[k][l].rgbtGreen = imageCopy[k][l].rgbtGreen;
            image[k][l].rgbtRed = imageCopy[k][l].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                int blueGx = (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGx = (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGx = (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                int blueGy = (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGy = (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGy = (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
                
            }
            
            else if (i == 0 && j == width - 1)
            {
                int blueGx = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);
                int greenGx = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                int redGx = (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1);
                
                int blueGy = (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue * 2);
                int greenGy = (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen * 2);
                int redGy = (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed * 2);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (i == height - 1 && j == 0)
            {
                int blueGx = (image[i - 1][j + 1].rgbtBlue) + (image[i][j + 1].rgbtBlue * 2);
                int greenGx = (image[i - 1][j + 1].rgbtGreen) + (image[i][j + 1].rgbtGreen * 2);
                int redGx = (image[i - 1][j + 1].rgbtRed) + (image[i][j + 1].rgbtRed * 2);
                
                int blueGy = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1);
                int greenGy = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1);
                int redGy = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (i == height - 1 && j == width - 1)
            {
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2);
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2);
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2);
                
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (i == 0)
            {
                int blueGx = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGx = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGx = (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                int blueGy = (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGy = (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGy = (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (i == height - 1)
            {
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue) + (image[i][j + 1].rgbtBlue * 2);
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen) + (image[i][j + 1].rgbtGreen * 2);
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed) + (image[i][j + 1].rgbtRed * 2);
                
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (j == 0)
            {
                int blueGx = (image[i - 1][j + 1].rgbtBlue) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGx = (image[i - 1][j + 1].rgbtGreen) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGx = (image[i - 1][j + 1].rgbtRed) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                int blueGy = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGy = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGy = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else if (j == width - 1)
            {
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1);
                
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue * 2);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen * 2);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed * 2);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
            
            else
            {
                int blueGx = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1) +
                             (image[i - 1][j + 1].rgbtBlue) + (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGx = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1) +
                              (image[i - 1][j + 1].rgbtGreen) + (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGx = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1) +
                            (image[i - 1][j + 1].rgbtRed) + (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                int blueGy = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);
                int greenGy = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int redGy = (image[i - 1][j - 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                
                if (round(sqrt(blueGx * blueGx + blueGy * blueGy)) <= 255)
                {
                    imageCopy[i][j].rgbtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));
                }
                else
                {
                    imageCopy[i][j].rgbtBlue = 255;
                }
                
                if (round(sqrt(greenGx * greenGx + greenGy * greenGy)) <= 255)
                {
                    imageCopy[i][j].rgbtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
                }
                else
                {
                    imageCopy[i][j].rgbtGreen = 255;
                }
                
                if (round(sqrt(redGx * redGx + redGy * redGy)) <= 255)
                {
                    imageCopy[i][j].rgbtRed = round(sqrt(redGx * redGx + redGy * redGy));
                }
                else
                {
                    imageCopy[i][j].rgbtRed = 255;
                }
            }
        }
    }
    
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtBlue = imageCopy[k][l].rgbtBlue;
            image[k][l].rgbtGreen = imageCopy[k][l].rgbtGreen;
            image[k][l].rgbtRed = imageCopy[k][l].rgbtRed;
        }
    }
    
    return;
}
