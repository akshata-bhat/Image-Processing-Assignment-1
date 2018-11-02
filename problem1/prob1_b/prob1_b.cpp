// Akshata Bhat
// USCID : 9560895350
// Email : akshatab@usc.edu
// Submission date: 2/4/18



#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[])
{
    FILE *fptr1, *fptr2;
    if (argc != 8){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "Syntax : prob1_b <input_img.raw> <output_image.raw> <orig_width> <orig_height> <bytes per pixel> <new_width> <new_height>" << endl;
        return 0;
    }

    int width1= atoi(argv[3]);
    int height1= atoi(argv[4]);
    int BytesPerPixel = atoi(argv[5]);
    int width2= atoi(argv[6]);
    int height2= atoi(argv[7]);
    int origTotalBytes=width1*height1*BytesPerPixel;
    unsigned int newTotalBytes=width2*height2*BytesPerPixel;
    unsigned char newImageData[newTotalBytes];

    // Allocate image data array
    unsigned char Imagedata[origTotalBytes];
    if (!(fptr1=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), origTotalBytes, fptr1);
    fclose(fptr1);

    unsigned char orig_Image2D_R[width1][height1]; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    unsigned char orig_Image2D_G[width1][height1];
    unsigned char orig_Image2D_B[width1][height1];
    int i,j,count=0;

    while(count<origTotalBytes)
    {
        for(i=0;i<height1;i++)
        {
            for(j=0;j<width1;j++)
            {
                orig_Image2D_R[i][j]=Imagedata[count];
                orig_Image2D_G[i][j]=Imagedata[count+1];
                orig_Image2D_B[i][j]=Imagedata[count+2];
                count=count+3;
            }
        }
    }

    unsigned char new_Image2D_R[width2][height2]; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    unsigned char new_Image2D_G[width2][height2];
    unsigned char new_Image2D_B[width2][height2];
    float ratio = float(width1)/float(width2);
    int x, y; // To store the integer values of a and b
    float a, b; // a and b in the formula

    for(int i=0;i<height2;i++)
    {
        for(int j=0;j<width2;j++)
        {
            x = (int)floor(i * ratio);
            y = (int)floor(j * ratio);
            a = (i * ratio) - x;
            b = (j * ratio) - y;
            new_Image2D_R[i][j] = (1 - b)*(1 - a)*int(orig_Image2D_R[x][y]) + (1 - b)*a*int(orig_Image2D_R[x+1][y]) + b*(1-a)*int(orig_Image2D_R[x][y+1]) + b*a*int(orig_Image2D_R[x+1][y+1]);
            new_Image2D_G[i][j] = (1 - b)*(1 - a)*int(orig_Image2D_G[x][y]) + (1 - b)*a*int(orig_Image2D_G[x+1][y]) + b*(1-a)*int(orig_Image2D_G[x][y+1]) + b*a*int(orig_Image2D_G[x+1][y+1]);
            new_Image2D_B[i][j] = (1 - b)*(1 - a)*int(orig_Image2D_B[x][y]) + (1 - b)*a*int(orig_Image2D_B[x+1][y]) + b*(1-a)*int(orig_Image2D_B[x][y+1]) + b*a*int(orig_Image2D_B[x+1][y+1]);
        }
    }

    count = 0;
    while(count<newTotalBytes)
    {
        for(i=0;i<height2;i++)
        {
            for(j=0;j<width2;j++)
            {
                newImageData[count] = new_Image2D_R[i][j];
                newImageData[count+1] = new_Image2D_G[i][j];
                newImageData[count+2] = new_Image2D_B[i][j];
                count=count+3;
            }
        }
    }

    if (!(fptr2=fopen(argv[2],"wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(newImageData, sizeof(unsigned char),width2*height2*BytesPerPixel, fptr2);
    fclose(fptr2);

    return 0;
}
