//Name : Akshata Bhat
//USC ID : 9560895350
//Email : akshatab@usc.edu
//Date : 2/4/2018


#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])

{
    FILE *fptr1, *fptr2; // Pointers to i/p and o/p files

    // Check for proper syntax
    if (argc != 6){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : prob2a_m1 <input_img.raw> <output_image.raw> <width> <height> <bytes per pixel>" << endl;
        return 0;
    }

    int width= atoi(argv[3]);
    int height= atoi(argv[4]);
    int bytesPerPixel = atoi(argv[5]);
    int totalBytes=width*height*bytesPerPixel;

    // Allocate image data array
    unsigned char Imagedata[totalBytes];

    // Read image (filename specified by first argument) into image data matrix
    if (!(fptr1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }

    //size_t fread ( void * ptr, size_t size, size_t count, FILE * stream );
    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    unsigned char Image1D_R[width*height] = { 0 }; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    unsigned char Image1D_G[width*height] = { 0 };
    unsigned char Image1D_B[width*height] = { 0 };
    int i,j,count=0;

    while(count<totalBytes)
    {
        for(i=0;i<width*height;i++)
        {
            Image1D_R[i]=Imagedata[count];
            Image1D_G[i]=Imagedata[count+1];
            Image1D_B[i]=Imagedata[count+2];
            count=count+3;
        }
    }


    int intensityCountRed[256];
    int intensityCountGreen[256];
    int intensityCountBlue[256];
    int newIntensityValuesRed[256];
    int newIntensityValuesGreen[256];
    int newIntensityValuesBlue[256];
    float probabR[256];
    float cum_probabR[256];
    float probabG[256];
    float cum_probabG[256];
    float probabB[256];
    float cum_probabB[256];
    unsigned char new_Image1D_R[width*height];
    unsigned char new_Image1D_G[width*height];
    unsigned char new_Image1D_B[width*height];
    for (int j = 0; j < 256; ++j)
    {
        int counterR = 0, counterG = 0, counterB = 0;
        for (int i = 0; i < width*height; ++i)
        {
            if((unsigned char)j == Image1D_R[i])
                ++counterR;
            if((unsigned char)j == Image1D_G[i])
                ++counterG;
            if((unsigned char)j == Image1D_B[i])
                ++counterB;
        }
        intensityCountRed[j]  = counterR;
        intensityCountGreen[j]  = counterG;
        intensityCountBlue[j]  = counterB;
        probabR[j] = float(intensityCountRed[j]) / float(width*height);
        probabG[j] = float(intensityCountGreen[j]) / float(width*height);
        probabB[j] = float(intensityCountBlue[j]) / float(width*height);
    }

    cum_probabR[0] = probabR[0];
    cum_probabG[0] = probabG[0];
    cum_probabB[0] = probabB[0];   //
    newIntensityValuesRed[0] = int(cum_probabR[0] * 255);
    newIntensityValuesGreen[0] = int(cum_probabG[0] * 255);
    newIntensityValuesBlue[0] = int(cum_probabB[0] * 255);
    for (int i = 1; i < 256; ++i)
    {
        cum_probabR[i] = cum_probabR[i-1] + probabR[i];
        cum_probabG[i] = cum_probabG[i-1] + probabG[i];
        cum_probabB[i] = cum_probabB[i-1] + probabB[i];
        newIntensityValuesRed[i] = int(cum_probabR[i] * 255);
        newIntensityValuesGreen[i] = int(cum_probabG[i] * 255);
        newIntensityValuesBlue[i] = int(cum_probabB[i] * 255);
    }

    FILE *histogram_orig, *transfer_function_orig;
    histogram_orig=fopen("Histogram_values_orig_method1.txt","w+");
    transfer_function_orig=fopen("Transfer_function_orig_method1.txt","w+");
    if(histogram_orig!=NULL)
    {
        for(int i=0;i<256;i++)
        {
            fprintf(histogram_orig,"%d\t%d\t%d\t%d\n",i,intensityCountRed[i],intensityCountGreen[i], intensityCountBlue[i]);
            fprintf(transfer_function_orig, "%d\t%d\t%d\t%d\n", i, newIntensityValuesRed[i], newIntensityValuesGreen[i], newIntensityValuesBlue[i]);
        }
    }
    fclose(histogram_orig);
    fclose(transfer_function_orig);

    for (int i = 0; i < width*height; ++i)
    {
        for (int j = 0; j < 256; ++j)
        {
            if (Image1D_R[i] == (unsigned char)j)
            {
                new_Image1D_R[i] = (unsigned char)newIntensityValuesRed[j];
                break;
            }
        }
    }
    for (int i = 0; i < width*height; ++i)
    {
        for (int j = 0; j < 256; ++j)
        {
            if (Image1D_G[i] == (unsigned char)j)
            {
                new_Image1D_G[i] = (unsigned char)newIntensityValuesGreen[j];
                break;
            }
        }
    }

    for (int i = 0; i < width*height; ++i)
    {
        for (int j = 0; j < 256; ++j)
        {
            if (Image1D_B[i] == (unsigned char)j)
            {
                new_Image1D_B[i] = (unsigned char)newIntensityValuesBlue[j];
                break;
            }
        }
    }

    unsigned char newImageData[totalBytes];

    for (int i = 0, j = 0; i < width*height && j < width*height*bytesPerPixel ; ++i, j=j+3) {
        newImageData[j] = new_Image1D_R[i];
        newImageData[j+1] = new_Image1D_G[i];
        newImageData[j+2] = new_Image1D_B[i];
    }


    if (!(fptr2=fopen(argv[2],"wb")))
    {
        cout << "Cannot open file." << endl;
        exit(1);
    }

    fwrite(newImageData, sizeof(unsigned char),width*height*bytesPerPixel, fptr2);
    fclose(fptr2);
    return 0;
}
