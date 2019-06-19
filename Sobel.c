/*
 This is a single file program that will perform sobel edge detection of a 
 binary image file and save the result.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

float**  allocateArray(int m, int n);
void printArray(float** array, int m, int n, int pad);
float** readArrayFromFile(char* filename, int x_size, int y_size, int pad);
void saveArrayToFile(char* filename, int x_size, int y_size, float** array, int step);
float** convolve(float** arr1, float** arr2, int dimensions[4]);
void scaleForDisplay(float** array, int m, int n);
float getArrayMax(float** array, int m, int n);
float getArrayMin(float** array, int m, int n);
float** sumArrs(float** arr1, float** arr2, int m, int n);
float** absArr(float** arr1, int m, int n);
float** binarize(float** arr, int m, int n, int threshold);

int main(int argc, char *argv[])
{
    //Verify correct number of cmd args are passed. Terminate if not.
    if(argc != 5)
    {
      printf("Invalide cmd arguments, terminating program execution.\n\n");
      exit(0);
    }

    //Convert args to appropriate values.
    char* data_file = argv[1];  //input file name
    int m = atoi(argv[2]);	//num rows
    int n = atoi(argv[3]);	//num columns
    int threshold = atoi(argv[4]); //edge threshold
    
    char* filename[2];
    filename[0] = (char*)malloc(100);  //Fname of Edge image
    filename[1] = (char*)malloc(100);  //Fname of Thresholded Edge Img
    strcpy(filename[0], data_file);
    strcpy(filename[1], data_file);
    strcat(filename[0], "_edges");
    strcat(filename[1], "_binary_edges_");
    strcat(filename[1], argv[4]); //Threshold level
    
    //Variable declarations
    int i, j; //loop indices
    float **data = readArrayFromFile(data_file, m, n, 1); //input image, padded
    
    //Compute vertical sobel operator
    float **sobel_v = allocateArray(3,3);
    sobel_v[0][0] = -1; sobel_v[0][1] =  0; sobel_v[0][2] =  1;
    sobel_v[1][0] = -2; sobel_v[1][1] =  0; sobel_v[1][2] =  2;
    sobel_v[2][0] = -1; sobel_v[2][1] =  0; sobel_v[2][2] =  1;
    
    //Compute horizontal sobel operator
    float **sobel_h = allocateArray(3,3);
    sobel_h[0][0] = -1; sobel_h[0][1] = -2; sobel_h[0][2] = -1;
    sobel_h[1][0] =  0; sobel_h[1][1] =   0; sobel_h[1][2] =  0;
    sobel_h[2][0] =  1; sobel_h[2][1] =   2; sobel_h[2][2] =  1;
    
    int dim[4] = {m, n, 3, 3};
    float **edges_v = absArr(convolve(data, sobel_v, dim), m, n);
    float **edges_h = absArr(convolve(data, sobel_h, dim), m, n);
    float **edges    = sumArrs(edges_v, edges_h, m, n);
    
    float **binaryEdges = binarize(edges, m, n, threshold);
    scaleForDisplay(edges, m, n);
    
    saveArrayToFile(filename[0], m, n, edges, 1);
    saveArrayToFile(filename[1], m, n, binaryEdges, 1);
    
    return 0;
}

//Perform discrete convolution of 2 arrays
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

//Add 2 arrays together
float** sumArrs(float** arr1, float** arr2, int m, int n)
{
    float **ret = allocateArray(m,n);
    
    int i, j;
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            ret[i][j] = arr1[i][j] + arr2[i][j];
    
    return ret;
}

float** absArr(float** arr1, int m, int n)
{
    int i, j;
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            arr1[i][j] = abs(arr1[i][j]);
    
    return arr1;
}

//binarize array based on threshold
float** binarize(float** arr, int m, int n, int threshold)
{
    float **ret = allocateArray(m,n);
    
    int i, j;
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            if(arr[i][j] > threshold)
                ret [i][j] = 255;
    
    return ret;
}


//ensure values range from 0-255
void scaleForDisplay(float** array, int m, int n)
{
    int i,j;
    float max, min, multiplier;
    max = getArrayMax(array,m,n);
    min = getArrayMin(array,m,n);
    multiplier = 255.0/(max-min);

    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
	{
	    array[i][j] = multiplier*(array[i][j] - min);
	}
}

void printArray(float** array, int m, int n, int pad)
{
    int i,j;
    for(i=pad; i<m+pad; i++)
    {
       for(j=pad; j<n+pad; j++)
            printf("%.0f ", array[i][j]);
       
       printf("\n");
    }
    printf("\n");
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
  FILE* fp_in = fopen(filename, "rb");
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

float getArrayMax(float** array, int m, int n)
{
    int i,j;
    float max = array[0][0];
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
		if(array[i][j] > max) max = array[i][j];
        }
    return max;
}

float getArrayMin(float** array, int m, int n)
{
    int i,j;
    float min = array[0][0];
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
        {
		if(array[i][j] < min) min = array[i][j];
        }
    return min;
}