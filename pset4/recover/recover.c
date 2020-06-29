#include <cs50.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    bool check_header(uint8_t *data);
    int remaining;
    //Check whether the program is executed with exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    uint8_t *buffer  = (uint8_t *)malloc(512 * sizeof(uint8_t));
   
    //Initialize the name of the files that I am going to write as ###.JPEG starting at 0. eg. 000.jpg
    char filename[8];
    int n_file = 0;
    FILE *img;
    fread(buffer, sizeof(uint8_t), 512 * sizeof(uint8_t), file);
    while (1)
    {
        if (feof(file))
        {
            break;
        }
        else
        {
            if (check_header(buffer))
            {
                sprintf(filename, "%.3i.jpg", n_file);
                img = fopen(filename, "w");
                do
                {
                    fwrite(buffer, sizeof(uint8_t), 512, img);
                    remaining = fread(buffer, sizeof(uint8_t), 512 * sizeof(uint8_t), file);

                    
    
                }
                while (!check_header(buffer) && remaining == 512);
                if (remaining != 512)
                {
                    fwrite(buffer, sizeof(uint8_t), remaining, img);
                    
                }
                fclose(img);
                n_file++;
            
            }
            else
            {
                fread(buffer, sizeof(uint8_t), 512 * sizeof(uint8_t), file);
            
            }
            
        }//if no end of file
        
        
        
        
        
    }//while
    
    free(buffer);
    return 0;

}//main

//Check whether the first 4 bytes are the beginning of a JPEG file.
bool check_header(uint8_t *data)
{
    bool found = false;
    if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)
    {
        found = true;
    }
    return found;
}//check_header


