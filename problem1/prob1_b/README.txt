EE569 Homework Assignment Prob1 b - Bilinear Interpolation
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
    g++ -o prob1_b.exe prob1_b.cpp
3. You should see the program executable named : prob1_b.exe

4.The executable should be run with these arguments:
program_name = ./prob1_b.exe 

<program_name> <input_image.raw> <output_image.raw> <orig_width> <orig_height> <bytes per pixel> <new_width> <new_height>"
where;
program_name: 		the name of the .exe file generated
input_image.raw: 	the name of the .raw file along with path to be taken as input for processing
output_image.raw:	the name of the output file
orig_width: 		Width of the original image
orig_height: 		Height of the original image
bytes per pixel: 	bytes per pixel (for RGB = 3 and for GRAY = 1)
new_width:		Width of resized image
new_height:		Height of the resized image
-----------------------------------------------------------------------------------------------------------------------------------------------------------------

