// Akshata Bhat
// USCID : 9560895350
// Email : akshatab@usc.edu
// Submission date: 2/4/18


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "my_header_file.h"
using namespace std;

int main(int argc, char *argv[])

{
	FILE *fptr1, *fptr2; // Pointers to i/p and o/p files
	
	// Check for proper syntax
	if (argc != 5){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "Syntax : prob1_a2 <input_img.raw> <width> <height> <bytes per pixel>" << endl;
		return 0;
	} 
	
	int Width= atoi(argv[2]);
	int Height= atoi(argv[3]);
	int BytesPerPixel = atoi(argv[4]);
	int TotalBytes=Width*Height*BytesPerPixel;
	
	// Allocate image data array
	unsigned char Imagedata[TotalBytes];

	// Read image (filename specified by first argument) into image data matrix
	if (!(fptr1=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}

	//size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
	fread(Imagedata, sizeof(unsigned char), TotalBytes, fptr1);
	fclose(fptr1);
	
	unsigned char Image2D_R[Width][Height]; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
	unsigned char Image2D_G[Width][Height];
	unsigned char Image2D_B[Width][Height];
	int i,j,count=0;
	
	while(count<TotalBytes)
	{
		for(i=0;i<Width;i++)
		{
			for(j=0;j<Height;j++)
			{
				Image2D_R[i][j]=Imagedata[count];
				Image2D_G[i][j]=Imagedata[count+1];
				Image2D_B[i][j]=Imagedata[count+2];
				count=count+3;
			}
		}
	}
	
	unsigned char Image2D_C[Width][Height];
	unsigned char Image2D_M[Width][Height];
	unsigned char Image2D_Y[Width][Height];
	unsigned char Grayscale_CMY[Width][Height];
	
	for(i=0;i<Width;i++)
	{
		for(j=0;j<Height;j++)
 		{
			Image2D_C[i][j]=(1 - (Image2D_R[i][j] / 255.0)) * 255;
			Image2D_M[i][j]=(1 - (Image2D_G[i][j] / 255.0)) * 255;
			Image2D_Y[i][j]=(1 - (Image2D_B[i][j] / 255.0)) * 255;
		//Grayscale_CMY[i][j]=(0.21 * Image2D_C[i][j]) + (0.72 * Image2D_M[i][j]) + (0.07 * Image2D_Y[i][j]);
		}
	}
	
	count = 0;
    while(count<Width*Height*3)
    {
        for(i=0;i<Width;i++)
        {
            for(j=0;j<Height;j++)
            {
                Imagedata[count] = Image2D_C[i][j];
                Imagedata[count+1] = Image2D_M[i][j];
                Imagedata[count+2] = Image2D_Y[i][j];
                count=count+3;
            }
        }
    }

	if (!(fptr2=fopen("Cyan_component.raw","wb"))) {
    	cout << "Cannot open file." << endl;
    	exit(1);
    }

    fwrite(Image2D_C, sizeof(unsigned char),Width*Height, fptr2);
    fclose(fptr2);
    if (!(fptr2=fopen("Magenta_component.raw","wb"))) {
    	cout << "Cannot open file." << endl;
    	exit(1);
    }
	fwrite(Image2D_M, sizeof(unsigned char),Width*Height, fptr2);
    fclose(fptr2);

        
	if (!(fptr2=fopen("Yellow_component.raw","wb"))) {
    	cout << "Cannot open file." << endl;
    	exit(1);
    }
	fwrite(Image2D_Y, sizeof(unsigned char),Width*Height, fptr2);
    fclose(fptr2);

        
	if (!(fptr2=fopen("CMY_output.raw","wb"))) {
    	cout << "Cannot open file." << endl;
    	exit(1);
    }
	fwrite(Imagedata, sizeof(unsigned char),Width*Height*3, fptr2);
    fclose(fptr2);

    return 0;
}

