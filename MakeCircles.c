/*
 This is a single file program that will create a binary datafile that consists
 of concentric circles. To be used to test edge detection algorithms.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void saveArrayToFile(char* filename, unsigned char array[256][256]);

int main(int argc, char** argv) {
    unsigned char array[256][256];
    int i, j, dist;
    char* filename = "circles.dat";
    
    //For each pixel, set intensity based on radius
    for(i=0; i<256; i++)
    {
        for(j=0; j<256; j++)
        {
            dist = sqrt((i-128)*(i-128) + (j-128)*(j-128));
            
            if(dist < 20) array[i][j] = 140;
            else if(dist < 40) array[i][j] = 130;
            else if(dist < 60) array[i][j] = 120;
            else if(dist < 80) array[i][j] = 110;
            else if(dist < 100) array[i][j] = 100;
            else if(dist < 120) array[i][j] = 90;
            else if(dist < 140) array[i][j] = 80;
            else array[i][j] = 70;
        }
    }
    
    saveArrayToFile(filename, array);
    
    return (EXIT_SUCCESS);
}

//Save array contents to file.
void saveArrayToFile(char* filename, unsigned char array[256][256])
{
  FILE *fp_out = fopen(filename, "wb");
  int i,j;
  for(i=0; i<256; i++)
    for(j=0; j<256; j++)
       fprintf(fp_out, "%c", array[i][j]);

  fclose(fp_out);  
}