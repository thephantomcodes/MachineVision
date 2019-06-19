/*
 This is a single file program that will add noise to a binary image file and
 save the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

unsigned char** allocateArray(int x_size, int y_size);
unsigned char** readArrayFromFile(char* filename, int x_size, int y_size);
void saveArrayToFile(char* filename, int x_size, int y_size, unsigned char** array);

int main(int argc, char** argv) {
    char * filename = argv[1];
    int noise_max = atoi(argv[2]);
    int m = atoi(argv[3]);
    int n = atoi(argv[4]);
    
    //output fname will append noise and level
    char * filename_out = (char *) malloc(100);
    strcpy(filename_out, filename);
    strcat(filename_out, "_noise_");
    strcat(filename_out, argv[2]);
    
    int mod_factor = noise_max*2 + 1;
    unsigned char** data = readArrayFromFile(filename, m, n);
    
    srand(time(NULL));
    int i, j, x;
    
    //Add random noise to each pixel
    for(i=0; i< m; i++)
        for(j=0; j< n; j++)
        {
            x = (rand()%mod_factor) - noise_max;
            data[i][j] += x;
        }
    
    saveArrayToFile(filename_out, m, n, data);
    
    return (EXIT_SUCCESS);
}

//Dynamically allocate 2D array from size inputs.
unsigned char** allocateArray(int x_size, int y_size)
{
  int i;
  unsigned char** array = (unsigned char**)malloc(x_size * sizeof(unsigned char*));
  for(i=0; i<x_size; i++)
    array[i] = (unsigned char*)malloc(y_size * sizeof(unsigned char));

  return array;
}

//Read file and store contents in 2D array
unsigned char** readArrayFromFile(char* filename, int x_size, int y_size)
{
  FILE* fp_in = fp_in = fopen(filename, "rb");
  
  if(fp_in == 0)
  {
      printf("Input file not found. Terminating.\n");
      exit(0);
  }

  int i,j;
  unsigned char** array = allocateArray(x_size, y_size);
  
  for(i=0; i<x_size; i++)
    for(j=0; j<y_size; j++)
      array[i][j] = fgetc(fp_in);
  
  fclose(fp_in);

  return array;
}

//Save array contents to file.
void saveArrayToFile(char* filename, int x_size, int y_size, unsigned char** array)
{
  FILE *fp_out = fp_out = fopen(filename, "wb");
  
  if(fp_out == 0)
  {
      printf("Output file not found. Terminating.\n");
      exit(0);
  }
  
  int i,j;
  for(i=0; i<x_size; i++)
    for(j=0; j<y_size; j++)
       fprintf(fp_out,"%c", array[i][j]);

  fclose(fp_out);  
}
