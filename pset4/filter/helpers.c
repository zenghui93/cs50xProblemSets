#include "stdio.h"
#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    double avg = 0;
    //Calculate the average of Red, Green and Blue for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = (int)avg;
            image[i][j].rgbtGreen = (int)avg;
            image[i][j].rgbtBlue = (int)avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    //Create a temporary image
    RGBTRIPLE temp[height][width];
    int w;

    for (int i = 0; i < height; i++)
    {
        w = width - 1;
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][w].rgbtRed;
            temp[i][j].rgbtGreen = image[i][w].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][w].rgbtBlue;
            w--;
        }
    }
    //Assign the values of the temporary image to the final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
           
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a temporary image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
  

    //Calculate the average of the color Red, Green and Blue for each pixel
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            double counter = 0.0;
            double avgRed = 0;
            double avgGreen = 0;
            double avgBlue = 0;
            
            for (int h = -1; h <= 1; h++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    if (i + h == -1 || i + h == height || j + k == -1 || j + k == width)
                    {
                        avgRed += 0;
                        avgGreen += 0;
                        avgBlue += 0;
                    }
                    else
                    {
                        avgRed += image[i + h][j + k].rgbtRed;
                        avgGreen += image[i + h][j + k].rgbtGreen;
                        avgBlue += image[i + h][j + k].rgbtBlue;
                        counter++;  
                    }
                }
            }
            temp[i][j].rgbtRed = (int)round(avgRed / counter);
            temp[i][j].rgbtGreen = (int)round(avgGreen / counter);
            temp[i][j].rgbtBlue = (int)round(avgBlue / counter);
        }
    }

    //Assign the values of the temporary image to the final image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
           
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
          
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue; 
        }
        
    }
    return;
}

//This is a function that compute the square root, giving parameters gx and gy and capping the final result at 255.
int calcola(int gx, int gy)
{
    double squareroot = round(sqrt((gx * gx) + (gy * gy)));
    if (squareroot >= 255)
    {
        return 255;
    }
    else
    {
        return (int)squareroot ;
    }
     
}//calcola matrice





// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a temporary image
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    //gx contains the values of my matrix(Gx)
    int gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    //gy contains the values of my matrix(Gy)
    int gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    /*
    GxRed tells me if there is any changes of value of Red in x direction
    GxGreen tells me if there is any changes of value of Green in x direction
    GxBlue tells me if there is any changes of value of Blue in x direction
    GyRed tells me if there is any changes of value of Red in y direction
    GyGreen tells me if there is any changes of value of Green in y direction
    GyBlue tells me if there is any changes of value of Blue in y direction
    */
    int GxRed, GxGreen, GxBlue, GyRed, GyGreen, GyBlue;
    int counter;
    //Calculate the values of GxRed, GxGreen, GxBlue, GyRed, GyGreen and GyBlue
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            counter = 0;
            GxRed = 0;
            GxGreen = 0;
            GxBlue = 0;
            GyRed = 0;
            GyGreen = 0;
            GyBlue = 0;
            //Compute the values of the matrix. h is the height and k is the width
            for (int h = -1; h <= 1; h++)
            {
                for (int k = -1; k <= 1; k++)
                {   
                    //If i + h == -1 || i + h == height || j + k == -1 || j + k == width that means that it's a border or corner pixel
                    if (i + h == -1 || i + h == height || j + k == -1 || j + k == width)
                    {
                        GxRed += 0;
                        GxGreen += 0;
                        GxBlue += 0;
                        GyRed += 0;
                        GyGreen += 0;
                        GyBlue += 0;
                        counter++;
                    }
                    else
                    {
                        GxRed += gx[counter] * image[i + h][j + k].rgbtRed;
                        GxGreen += gx[counter] * image[i + h][j + k].rgbtGreen;
                        GxBlue += gx[counter] * image[i + h][j + k].rgbtBlue;
                        GyRed += gy[counter] * image[i + h][j + k].rgbtRed;
                        GyGreen += gy[counter] * image[i + h][j + k].rgbtGreen;
                        GyBlue += gy[counter] * image[i + h][j + k].rgbtBlue;
                        counter++;  
                    }
                  
                }
            }
            // Calculate the new value of Red only if there has been a change of color either in x direction or y direction
            if (GxRed != 0 || GyRed != 0)
            {
                temp[i][j].rgbtRed = calcola(GxRed, GyRed);
            }
            // Calculate the new value of Green only if there has been a change of color either in x direction or y direction
            if (GxGreen != 0 || GyGreen != 0)
            {
                temp[i][j].rgbtGreen = calcola(GxGreen, GyGreen);
            }
            // Calculate the new value of Blue only if there has been a change of color either in x direction or y direction
            if (GxBlue != 0 || GyBlue != 0)
            {
                temp[i][j].rgbtBlue = calcola(GxBlue, GyBlue);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
           
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
          
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue; 
        }
        
    }
    return;
}