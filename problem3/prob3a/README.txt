EE569 Homework Assignment Prob3a - Mix noise in color image 
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
    g++ -o prob3a.exe prob3a.cpp
3. You should see the program executable named : prob3a.exe

4.The executable should be run with these arguments:
program_name = ./prob3a.exe 

<program_name> <clean_image.raw> <noisy_img.raw> <denoised_image.raw> <width> <height> <bytes_per_pixel>"


where;
program_name: 			the name of the .exe file generated
clean_image.raw: 		the name of the clean image.raw file along with path to be taken as input for processing
noisy_image.raw:		the name of the input noisy image to be filtered
denoised_image.raw		the name of the output denoised image 
width:	 			Width of the image
height: 			Height of the image
bytes_per_pixel: 		bytes per pixel (for RGB = 3 and for GRAY = 1)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

