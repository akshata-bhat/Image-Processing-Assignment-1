EE569 Homework Assignment Prob2 b - Image filtering - Oil Painting 
Date: February 4, 2018
Name : Akshata Bhat
USC ID : 9560895350
Email : akshatab@usc.edu
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
SYSTEM CONFIGURATION IN WHICH THIS CODE RAN:

OS: Linux Ubuntu 64-bit 16.04

Software: Terminal
-----------------------------------------------------------------------------------------------------------------------------------------------------------------
STEPS TO DEBUG CODE:


1. Open Terminal

2. Run this command in the project folder:
    g++ -o prob2_b.exe prob2_b.cpp
3. You should see the program executable named : prob2_b.exe

4.The executable should be run with these arguments:
program_name = ./prob2_b.exe 

<program_name> <input_image.raw> <output_image_quantized.raw> <output_image_oilPainting.raw> <image_width> <image_height> <bytes_per_pixel> <input_color_levels> <output_color_levels>

where;
program_name: 			the name of the .exe file generated
input_image.raw: 		the name of the .raw file along with path to be taken as input for processing
output_image_quantized.raw:	the name of the quantized output
output_image_oilPainting.raw:	the name of the output with oilpainting effect
image_width: 			Width of the image
image_height: 			Height of the image
bytes_per_pixel: 		bytes per pixel (for RGB = 3 and for GRAY = 1)
input_color_levels:		Color levels in the input image
output_color_levels:		Color levels in the output image

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

