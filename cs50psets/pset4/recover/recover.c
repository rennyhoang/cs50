#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
    }
    
    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL)
    {
        return 1;
    }

    BYTE buffer[512];
    int jpgCounter = 0;
    bool jpgFound = false;
    char filename[8];
    FILE *img = NULL;
    
    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpgCounter == 0)
            {
                jpgFound = true;
                sprintf(filename, "%03i.jpg", jpgCounter);
                jpgCounter++;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
            
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", jpgCounter);
                jpgCounter++;
                img = fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
            }
        }
        
        else
        {
            if (jpgFound == true)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
    }
    
    fclose(file);
    fclose(img);
    
    return (0);
}
