//Name : Akshata Bhat
//USC ID : 9560895350
//Email : akshatab@usc.edu
//Date : 2/4/18

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
    FILE *fptr1, *fptr2; // Pointers to i/p and o/p files

    // Check for proper syntax
    if (argc != 6){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : prob2a_m2 <input_img.raw> <output_image.raw> <width> <height> <bytes per pixel>" << endl;
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

    unsigned char Image1D_R[width*height]; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    unsigned char Image1D_G[width*height];
    unsigned char Image1D_B[width*height];
    memset(Image1D_R,'0',width*height*sizeof(unsigned char));
    memset(Image1D_G,'0',width*height*sizeof(unsigned char));
    memset(Image1D_B,'0',width*height*sizeof(unsigned char));
    int count = 0;

    for(int i=0;i<width*height;++i)
    {
        count = i * 3;
        Image1D_R[i]=Imagedata[count];
        Image1D_G[i]=Imagedata[count+1];
        Image1D_B[i]=Imagedata[count+2];
    }

    int indexR = 0, indexG = 0, indexB = 0;
    int sortedAddressRed[width*height];
    int sortedAddressGreen[width*height];
    int sortedAddressBlue[width*height];

    for (int j = 0; j < 256; ++j)
    {
        for (int i = 0; i < width*height; ++i)
        {
            if(Image1D_R[i] == (unsigned char)j)
            {
                sortedAddressRed[indexR] = i;
                indexR++;
            }
            if(Image1D_G[i] == (unsigned char)j)
            {
                sortedAddressGreen[indexG] = i;
                indexG++;
            }
            if(Image1D_B[i] == (unsigned char)j)
            {
                sortedAddressBlue[indexB] = i;
                indexB++;
            }
        }
    }

    int intensity = 0;
    count=0;
    int pixelsPerBin = ceil(float(width*height)/256.0);
    unsigned char new_Image1D_R[width*height];
    memset(new_Image1D_R,'0',width*height*sizeof(unsigned char));
    unsigned char new_Image1D_G[width*height];
    memset(new_Image1D_G,'0',width*height*sizeof(unsigned char));
    unsigned char new_Image1D_B[width*height];
    memset(new_Image1D_B,'0',width*height*sizeof(unsigned char));
    count=0;
    while(count < width*height)
    {
        for (int i = 0; i < pixelsPerBin; ++i)
        {
            new_Image1D_R[(sortedAddressRed[count])] = (unsigned char)intensity;
            new_Image1D_G[(sortedAddressGreen[count])] = (unsigned char)intensity;
            new_Image1D_B[(sortedAddressBlue[count])] = (unsigned char)intensity;
            count = count + 1;
        }
        intensity++;
        if(intensity == 256)
            break;
        if(intensity == 255) {
            for (int i = 0; i <= (width*height-pixelsPerBin*255); ++i) {
                new_Image1D_R[(sortedAddressRed[count])] = (unsigned char) intensity;
                new_Image1D_G[(sortedAddressGreen[count])] = (unsigned char) intensity;
                new_Image1D_B[(sortedAddressBlue[count])] = (unsigned char) intensity;
                count = count + 1;
            }
            break;
        }
    }

    int newIntensityValuesRed[256];
    int newIntensityValuesGreen[256];
    int newIntensityValuesBlue[256];
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
        newIntensityValuesRed[j]  = counterR;
        newIntensityValuesGreen[j]  = counterG;
        newIntensityValuesBlue[j]  = counterB;
    }

    int cum_intensityR[256];
    int cum_intensityG[256];
    int cum_intensityB[256];
    cum_intensityR[0] = newIntensityValuesRed[0];
    cum_intensityG[0] = newIntensityValuesGreen[0];
    cum_intensityB[0] = newIntensityValuesBlue[0];
    for (int i = 1; i < 256; ++i)
    {
        cum_intensityR[i] = cum_intensityR[i-1] + newIntensityValuesRed[i];
        cum_intensityG[i] = cum_intensityG[i-1] + newIntensityValuesGreen[i];
        cum_intensityB[i] = cum_intensityB[i-1] + newIntensityValuesBlue[i];
    }

    FILE *transfer_function_orig;
    transfer_function_orig=fopen("Transfer_function_orig_method2.txt","w+");
    if(transfer_function_orig!=NULL)
    {
        for(int i=0;i<256;i++)
        {
            fprintf(transfer_function_orig,"%d\t%d\t%d\t%d\n",i,cum_intensityR[i],cum_intensityG[i], cum_intensityB[i]);
        }
    }
    fclose(transfer_function_orig);

    unsigned char newImageData[totalBytes];
    memset(newImageData,'0',totalBytes*sizeof(unsigned char));

    for (int i = 0, j = 0; i < width*height && j < width*height*bytesPerPixel ; ++i, j+=3) {
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
