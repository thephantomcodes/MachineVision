# MachineVision
This repository contains a number of single file C programs for performing common machine vision tasks on 8-bit grayscale image files. Common file formats such as BMP and JPG will not work.

MakeCircles.c will create a 256x256 8-bit grayscale image with concentric circles. No cmd args are required. Output file is simply called "circles".

AddNoiseToImage.c will add uniform noise to an image with a user defined max. Output file will append "_noise_[MAX-LEVEL]"
Cmd args are as follows:
1. Filename
2. Num rows
3. Num colums
4. Max noise level
Output file will append "_noise_[MAX-LEVEL]"

AverageFilter.c will perform 3x3 average filtering on an image. Output file will append "_filtered"
Cmd args:
1. Filename
2. Num rows
3. Num colums

Sobel.c will perfom Sobel edge detection on and image. Output file will append "_binary_edges_[THRESHOLD]"
Cmd args:
1. Filename
2. Num rows
3. Num colums
4. Threshold to determine when edge is found


The /img directory contains a number of files that were processed using this chain. An additional 256x256 image called "mri" is also included to demonstrate that it works on real images.