// Author : Akshata Bhat
// USC ID : 9560895350
// Email : akshatab@usc.edu
// Submission Date : 2/4/2018

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "my_header_file.h"
using namespace std;

int main(int argc, char *argv[]) {
    FILE *fptr1, *fptr2; // Pointers to i/p and o/p files

    // Check for proper syntax
    if (argc != 7) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout
                << "Syntax : prob1_a1 <clean_image.raw> <noisy_img.raw> <denoised_image.raw> <width> <height> <bytes_per_pixel>"
                << endl;
        return 0;
    }

    int width = atoi(argv[4]);
    int height = atoi(argv[5]);
    int bytesPerPixel = atoi(argv[6]);
    int totalBytes = width * height * bytesPerPixel;

    // Allocate image data array
    unsigned char *origImagedata = NULL;
    origImagedata = new unsigned char[totalBytes];
    unsigned char *cleanImagedata = NULL;
    cleanImagedata = new unsigned char[totalBytes];


    // Read image (filename specified by first argument) into image data matrix
    if (!(fptr1 = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(cleanImagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    if (!(fptr1 = fopen(argv[2], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }
    fread(origImagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    int i, j, count = 0;
    //Separating the 1D Original Image array into 2D R, G, B arrays
    unsigned char **Image2D_R = new unsigned char*[height];
    unsigned char **Image2D_G = new unsigned char*[height];
    unsigned char **Image2D_B = new unsigned char*[height];
    for(i = 0; i < height; ++i) {
        Image2D_R[i] = new unsigned char[width];
        Image2D_G[i] = new unsigned char[width];
        Image2D_B[i] = new unsigned char[width];
    }

    while(count<totalBytes)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                Image2D_R[i][j]=origImagedata[count];
                Image2D_G[i][j]=origImagedata[count+1];
                Image2D_B[i][j]=origImagedata[count+2];
                count=count+3;
            }
        }
    }

    unsigned char Image2D_R_filter[width][height];
    unsigned char Image2D_G_filter[width][height];
    unsigned char Image2D_B_filter[width][height];

    memset(Image2D_R_filter,0,height*width*sizeof(unsigned char));
    memset(Image2D_G_filter,0,height*width*sizeof(unsigned char));
    memset(Image2D_B_filter,0,height*width*sizeof(unsigned char));

    int x, y, N=5, xStart, yStart, xLimit=0, yLimit=0, index=0;
    int median_value;
    int tempRows=0, tempCols=0;

    memset(Image2D_R_filter,0,width*height*sizeof(unsigned char));
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            xStart = i-(N/2);
            yStart = j-(N/2);
            yLimit = j+(N/2);
            xLimit = i+(N/2);

            //To account for the corner cases
            if(xStart < 0)
                xStart = 0;
            if(yStart < 0)
                yStart = 0;
            if(xLimit > height-1)
                xLimit = height-1;
            if(yLimit > width-1)
                yLimit = width-1;

            tempRows = xLimit-xStart+1;
            tempCols = yLimit-yStart+1;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_R[x][y];
                    ++index;
                }
            }
            median_value = median_value_calc(tempArray, tempRows*tempCols);
            Image2D_R_filter[i][j] = (unsigned char)median_value;
        }
    }

    median_value=0;
    memset(Image2D_G_filter,0,width*height*sizeof(unsigned char));
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            xStart = i-(N/2);
            yStart = j-(N/2);
            yLimit = j+(N/2);
            xLimit = i+(N/2);
            //To account for the corner cases
            if(xStart < 0)
                xStart = 0;
            if(yStart < 0)
                yStart = 0;
            if(xLimit > height-1)
                xLimit = height-1;
            if(yLimit > width-1)
                yLimit = width-1;
            tempRows = xLimit-xStart+1;
            tempCols = yLimit-yStart+1;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_G[x][y];
                    ++index;
                }
            }
            median_value = median_value_calc(tempArray, tempRows*tempCols);
            Image2D_G_filter[i][j] = (unsigned char)median_value;
        }
    }

    median_value=0;
    memset(Image2D_B_filter,0,width*height*sizeof(unsigned char));
    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            xStart = i-(N/2);
            yStart = j-(N/2);
            yLimit = j+(N/2);
            xLimit = i+(N/2);
            //To account for the corner cases
            if(xStart < 0)
                xStart = 0;
            if(yStart < 0)
                yStart = 0;
            if(xLimit > height-1)
                xLimit = height-1;
            if(yLimit > width-1)
                yLimit = width-1;
            tempRows = xLimit-xStart+1;
            tempCols = yLimit-yStart+1;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_B[x][y];
                    ++index;
                }
            }
            median_value = median_value_calc(tempArray, tempRows*tempCols);
            Image2D_B_filter[i][j] = (unsigned char)median_value;
        }
    }


    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            xStart = i-(N/2);
            yStart = j-(N/2);
            yLimit = j+(N/2);
            xLimit = i+(N/2);
            //To account for the corner cases
            if(xStart < 0)
                xStart = 0;
            if(yStart < 0)
                yStart = 0;
            if(xLimit > height-1)
                xLimit = height-1;
            if(yLimit > width-1)
                yLimit = width-1;
            tempRows = xLimit-xStart+1;
            tempCols = yLimit-yStart+1;
            int sumR = 0, sumG = 0, sumB = 0;
            int meanR = 0, meanG = 0, meanB = 0;
            for (x = xStart; x <= xLimit; ++x) {
                for (y = yStart; y <= yLimit ; ++y) {
                   // sumR = sumR + (int)Image2D_R_filter[x][y];
                   // sumG = sumG + (int)Image2D_G_filter[x][y];
                    sumB = sumB + (int)Image2D_B_filter[x][y];
                    ++index;
                }
            }
            //meanR = sumR/index;
            //meanG = sumG/index;
            meanB = sumB/index;
            //Image2D_R_filter[i][j] = (unsigned char)meanR;
            //Image2D_G_filter[i][j] = (unsigned char)meanG;
            Image2D_B_filter[i][j] = (unsigned char)meanB;
        }
    }

    unsigned char *denoisedImagedata = NULL;
    denoisedImagedata = new unsigned char[totalBytes];

    count = 0;
    while(count<totalBytes)
    {
        for(i=0;i<width;i++)
        {
            for(j=0;j<height;j++)
            {
                denoisedImagedata[count] =   Image2D_R_filter[i][j];
                denoisedImagedata[count+1] = Image2D_G_filter[i][j];
                denoisedImagedata[count+2] = Image2D_B_filter[i][j];
                count=count+3;
            }
        }
    }

    if (!(fptr2=fopen(argv[3],"wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(denoisedImagedata, sizeof(unsigned char),width*height*bytesPerPixel, fptr2);
    fclose(fptr2);


    unsigned char *Image1D_R_clean = NULL;
    unsigned char *Image1D_G_clean = NULL;
    unsigned char *Image1D_B_clean = NULL;
    Image1D_R_clean = new unsigned char[width * height];
    Image1D_G_clean = new unsigned char[width * height];
    Image1D_B_clean = new unsigned char[width * height];
    memset(Image1D_R_clean,0,width*height*sizeof(unsigned char));
    memset(Image1D_G_clean,0,width*height*sizeof(unsigned char));
    memset(Image1D_B_clean,0,width*height*sizeof(unsigned char));
    unsigned char *Image1D_R_denoised = NULL;
    unsigned char *Image1D_G_denoised = NULL;
    unsigned char *Image1D_B_denoised = NULL;
    Image1D_R_denoised = new unsigned char[width * height];
    Image1D_G_denoised = new unsigned char[width * height];
    Image1D_B_denoised = new unsigned char[width * height];
    memset(Image1D_R_denoised,0,width*height*sizeof(unsigned char));
    memset(Image1D_G_denoised,0,width*height*sizeof(unsigned char));
    memset(Image1D_B_denoised,0,width*height*sizeof(unsigned char));
    unsigned char *Image1D_R_noisy = NULL;
    unsigned char *Image1D_G_noisy = NULL;
    unsigned char *Image1D_B_noisy = NULL;
    Image1D_R_noisy = new unsigned char[width * height];
    Image1D_G_noisy = new unsigned char[width * height];
    Image1D_B_noisy = new unsigned char[width * height];
    memset(Image1D_R_noisy,0,width*height*sizeof(unsigned char));
    memset(Image1D_G_noisy,0,width*height*sizeof(unsigned char));
    memset(Image1D_B_noisy,0,width*height*sizeof(unsigned char));

    count = 0;
    for(i=0;i<width*height;++i)
    {
        Image1D_R_clean[i]=cleanImagedata[count];
        Image1D_G_clean[i]=cleanImagedata[count+1];
        Image1D_B_clean[i]=cleanImagedata[count+2];
        count=count+3;
        if(count > width*height*3)
            break;
    }

    count = 0;
    for(i=0;i<width*height;++i)
    {
        Image1D_R_denoised[i]=denoisedImagedata[count];
        Image1D_G_denoised[i]=denoisedImagedata[count+1];
        Image1D_B_denoised[i]=denoisedImagedata[count+2];
        count=count+3;
        if(count > width*height*3)
            break;
    }

    count = 0;
    for(i=0;i<width*height;++i)
    {
        Image1D_R_noisy[i]=origImagedata[count];
        Image1D_G_noisy[i]=origImagedata[count+1];
        Image1D_B_noisy[i]=origImagedata[count+2];
        count=count+3;
        if(count > width*height*3)
            break;
    }


    double PSNR_TOT = psnr_calc(cleanImagedata, origImagedata, width*3, height);
    cout << "PSNR for Clean vs mixed-noise image : " << PSNR_TOT << endl;

    double PSNR_R = psnr_calc(Image1D_R_clean, Image1D_R_denoised, width, height);
    double PSNR_G = psnr_calc(Image1D_G_clean, Image1D_G_denoised, width, height);
    double PSNR_B = psnr_calc(Image1D_B_clean, Image1D_B_denoised, width, height);
    double PSNR_TOTAL = psnr_calc(cleanImagedata, denoisedImagedata, width*3, height);
    cout << "PSNR for R component : " << PSNR_R << endl;
    cout << "PSNR for G component : " << PSNR_G << endl;
    cout << "PSNR for B component : " << PSNR_B << endl;
    cout << "PSNR for ALL components combined : " << PSNR_TOTAL << endl;

    delete [] Image1D_R_clean;
    delete [] Image1D_G_clean;
    delete [] Image1D_B_clean;
    delete [] Image1D_R_noisy;
    delete [] Image1D_G_noisy;
    delete [] Image1D_B_noisy;
    delete [] denoisedImagedata;
    delete [] cleanImagedata;
    delete [] origImagedata;


    return 0;
}
