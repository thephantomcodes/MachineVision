# MachineVision
This repository contains a number of single file C programs for performing common machine vision tasks on 8-bit grayscale image files. Common file formats such as BMP and JPG will not work.

### MakeCircles.c 
Creates a 256x256 8-bit grayscale image with concentric circles. No cmd args are required. Output file is simply called "circles".

### AddNoiseToImage.c 
Adds uniform noise to an image with a user defined max. Output file will append "_noise_MAX-LEVEL"

Cmd args are as follows:
1. Filename
2. Num rows
3. Num colums
4. Max noise level

### AverageFilter.c 
Performs 3x3 average filtering on an image. Output file will append "_filtered"

Cmd args:
1. Filename
2. Num rows
3. Num colums

### Sobel.c 
Performs Sobel edge detection on an image. Output file will append "_binary_edges_THRESHOLD"

Cmd args:
1. Filename
2. Num rows
3. Num colums
4. Threshold to determine when edge is found

### img directory 
Contains a number of files that were processed using this chain. An additional 256x256 image called "mri" is also included to demonstrate that it works on real images.

### show_image.py
Since the image files are binary, most applications will not display them. This python script can be used to see them.
