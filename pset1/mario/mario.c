#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{   
    int height;
    // It promts the user for a number between 1 and 8
    do
    {
        height = get_int("Height: ");
    
    }
    while (height < 1 || height > 8);
    
    //numS is the number of spaces to be printed
    int numS = height - 1;
    int row = 1;
    char spaces[height];
    char hashes[height];
    strcpy(spaces, "");
    
    do
    {
        //This is a function that builds all the spaces
        for (int i = 0; i < numS; i++)
        {
            strcat(spaces, " ");
        }
        //This line builds up my hashes
        strcat(hashes, "#");
        //print a line of spaces, hashes and hashes to form my pyramid
        printf("%s%s  %s\n", spaces, hashes, hashes);
        strcpy(spaces, "");
        numS--;
        row++;
    }
    while (row <= height);
}