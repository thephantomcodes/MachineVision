/*
 This is a single file program that will perform 3x3 average filtering of a 
 binary image file and save the result.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float** convolve(float** arr1, float** arr2, int dimensions[4]);
float**  allocateArray(int m, int n);
float** readArrayFromFile(char* filename, int x_size, int y_size, int pad);
void saveArrayToFile(char* filename, int m, int n, float** array, int step);

int main(int argc, char** argv) {
    char* data_file = argv[1];  //input file name
    int m = atoi(argv[2]);	//num rows
    int n = atoi(argv[3]);	//num columns
    
    //output fname appends filtered
    char* filename = (char*)malloc(100);
    strcpy(filename, data_file);
    strcat(filename, "_filtered");
    
    float **filter = allocateArray(3,3);
    filter[0][0] = 1.0/9.0;      filter[0][1] =  filter[0][0]; filter[0][2] =  filter[0][0];
    filter[1][0] = filter[0][0]; filter[1][1] =  filter[0][0]; filter[1][2] =  filter[0][0];
    filter[2][0] = filter[0][0]; filter[2][1] =  filter[0][0]; filter[2][2] =  filter[0][0];
    
    float **data = readArrayFromFile(data_file, m, n, 1); //input image, padded
    int dim[4] = {m, n, 3, 3};
    float **filteredImage = convolve(data, filter, dim);
    
    saveArrayToFile(filename, m, n, filteredImage, 1);
    
    return (EXIT_SUCCESS);
}

float** convolve(float** arr1, float** arr2, int dimensions[4])
{
  int m1=dimensions[0], n1=dimensions[1]; //dim of arr1
  int m2=dimensions[2], n2=dimensions[3]; //dim of arr2

  float **ret = allocateArray(m1,n1);

  int i1, j1, i2, j2;
  for(i1=0; i1<m1; i1++)
  for(j1=0; j1<n1; j1++)
  {
      for(i2=0; i2<m2; i2++)
      for(j2=0; j2<n2; j2++)
      {
          ret[i1][j1] += (arr1[i1+i2][j1+j2]*arr2[i2][j2]);
      }
  }

  return ret;
}

float**  allocateArray(int m, int n)
{
    int i;
    float** c = (float**)calloc(m,  sizeof(float*));
    for(i=0; i<m; i++)
        c[i] = (float*)calloc(n,  sizeof(float));
    
    return c;
}

//Read file and store contents in 2D array
float** readArrayFromFile(char* filename, int x_size, int y_size, int pad)
{
  FILE* fp_in = fp_in = fopen(filename, "rb");
  if(fp_in == NULL)
  {
      printf("File not found. Terminating.\n");
      exit(0);
  }

  float** array_float = allocateArray(x_size + 2*pad, y_size + 2*pad);
  
  int i, j;
  for(i=pad; i<x_size + pad; i++)
    for(j=pad; j<x_size + pad; j++)
      array_float[i][j] = (float)fgetc(fp_in);

  fclose(fp_in);

  return array_float;
}

//Save array contents to file.
void saveArrayToFile(char* filename, int m, int n, float** array, int step)
{
  FILE *fp_out = fopen(filename, "wb");
  int i,j;
  for(i=0; i<m; i++)
    for(j=0; j<n; j += step)
       fprintf(fp_out,"%c", (unsigned char)array[i][j]);

  fclose(fp_out);  
}