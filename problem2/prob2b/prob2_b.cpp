#include <cstdio>
#include <iostream>
#include <algorithm>
#include "my_header_file.h"
#include <cstring>
using namespace std;

int main(int argc, char *argv[]) {
    FILE *fptr1, *fptr2; // Pointers to i/p and o/p files

    // Check for proper syntax
    if (argc != 9) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout
                << "Syntax : prob2_b <input_img.raw> <output_image_quantized.raw> <output_image_oilPainting.raw> <width> <height> <bytes per pixel> <input_color_levels> <output_color_levels>"
                << endl;
        return 0;
    }

    const int width = atoi(argv[4]);
    const int height = atoi(argv[5]);
    const int bytesPerPixel = atoi(argv[6]);
    int in_color_lvl = atoi(argv[7]); // input color levels
    int out_color_lvl = atoi(argv[8]); // output color levels
    int totalBytes = width * height * bytesPerPixel;

    // Allocate image data array
    unsigned char Imagedata[totalBytes];

    // Read image (filename specified by first argument) into image data matrix
    if (!(fptr1 = fopen(argv[1], "rb"))) {
        cout << "Cannot open file: " << argv[1] << endl;
        exit(1);
    }

    fread(Imagedata, sizeof(unsigned char), totalBytes, fptr1);
    fclose(fptr1);

    unsigned char* Image1D_R = NULL; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    unsigned char* Image1D_G = NULL;
    unsigned char* Image1D_B = NULL;
    Image1D_R = new unsigned char[width*height];
    Image1D_G = new unsigned char[width*height];
    Image1D_B = new unsigned char[width*height];

    Image1D_R[width * height] = {0}; // Array to store the Image as a 3D array with 2D arrays - one each for R,G,B
    Image1D_G[width * height] = {0};
    Image1D_B[width * height] = {0};
    int i, j, count = 0;

    while (count < totalBytes) {
        for (i = 0; i < width * height; i++) {
            Image1D_R[i] = Imagedata[count];
            Image1D_G[i] = Imagedata[count + 1];
            Image1D_B[i] = Imagedata[count + 2];
            count = count + 3;
        }
    }

    int indexR = 0, indexG = 0, indexB = 0;
    int* sortedAddressRed = NULL;
    int* sortedAddressGreen = NULL;
    int* sortedAddressBlue = NULL;
    sortedAddressRed =   new int[width*height];
    sortedAddressGreen = new int[width*height];
    sortedAddressBlue =  new int[width*height];


    for (int j = 0; j < 256; ++j) {
        for (int i = 0; i < width * height; ++i) {
            if (Image1D_R[i] == (unsigned char) j) {
                sortedAddressRed[indexR] = i;
                indexR++;
            }
            if (Image1D_G[i] == (unsigned char) j) {
                sortedAddressGreen[indexG] = i;
                indexG++;
            }
            if (Image1D_B[i] == (unsigned char) j) {
                sortedAddressBlue[indexB] = i;
                indexB++;
            }
        }
    }

    unsigned char* new_Image1D_R = NULL;
    unsigned char* new_Image1D_G = NULL;
    unsigned char* new_Image1D_B = NULL;

    new_Image1D_R = new unsigned char[width * height];
    new_Image1D_G = new unsigned char[width * height];
    new_Image1D_B = new unsigned char[width * height];

    int index = 0;
    int binCount = in_color_lvl / out_color_lvl; // No of bins
    int pixelsPerBin = (int) (width * height) / binCount;
    unsigned char meanIntensitiesR[binCount];
    unsigned char meanIntensitiesG[binCount];
    unsigned char meanIntensitiesB[binCount];

    for (int i = 0; i < width * height; ++i) {
        int sumR = 0, sumG = 0, sumB = 0;
        for (int j = 0; j < pixelsPerBin ; ++j) {
            sumR = sumR + Image1D_R[sortedAddressRed[i]];
            sumG = sumG + Image1D_G[sortedAddressGreen[i]];
            sumB = sumB + Image1D_B[sortedAddressBlue[i]];
            ++i;
        }
        meanIntensitiesR[index] = (unsigned char) (int(sumR / pixelsPerBin));
        meanIntensitiesG[index] = (unsigned char) (int(sumG / pixelsPerBin));
        meanIntensitiesB[index] = (unsigned char) (int(sumB / pixelsPerBin));
        ++index;
        if (index == binCount)
            break;
    }

    count = 0;
    index = 0;
    while (count < width * height) {
        for (int i = 0; i < pixelsPerBin; ++i) {
            new_Image1D_R[(sortedAddressRed[count])] = meanIntensitiesR[index];
            new_Image1D_G[(sortedAddressGreen[count])] = meanIntensitiesG[index];
            new_Image1D_B[(sortedAddressBlue[count])] = meanIntensitiesB[index];
            count = count + 1;
        }
        index++;
        if (index == binCount)
            break;
    }

    unsigned char newImageData[totalBytes];

    for (int i = 0, j = 0; i < width * height && j < width * height * bytesPerPixel; ++i, j = j + 3) {
        newImageData[j] = new_Image1D_R[i];
        newImageData[j + 1] = new_Image1D_G[i];
        newImageData[j + 2] = new_Image1D_B[i];
    }

    delete [] new_Image1D_R;
    delete [] new_Image1D_G;
    delete [] new_Image1D_B;

    delete [] Image1D_R;
    delete [] Image1D_G;
    delete [] Image1D_B;

    delete [] sortedAddressRed;
    delete [] sortedAddressGreen;
    delete [] sortedAddressBlue;

    unsigned char Image2D_R[height][width];
    unsigned char Image2D_G[height][width];
    unsigned char Image2D_B[height][width];

    count = 0;

    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Image2D_R[i][j] = newImageData[count];
                Image2D_G[i][j] = newImageData[count + 1];
                Image2D_B[i][j] = newImageData[count + 2];
                count = count + 3;
            }
        }
    }

    if (!(fptr2=fopen(argv[2],"wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(newImageData, sizeof(unsigned char),width*height*bytesPerPixel, fptr2);
    fclose(fptr2);

    // Mask operation - Image Filtering step

    i=0, j=0; // image co-ordinates
    int x=0, y=0; // mask co-ordinates
    int N=5, xLimit=0, yLimit=0;
    int newArrayRed[height][width];
    memset(newArrayRed,0,width*height*sizeof(int));
    int newArrayGreen[height][width];
    memset(newArrayGreen,0,width*height*sizeof(int));
    int newArrayBlue[height][width];
    memset(newArrayBlue,0,width*height*sizeof(int));
    int frequentColor;
    int tempRows=0, tempCols=0;


    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            yLimit = j+N;
            xLimit = i+N;
            //To account for the corner cases
            if (i > height-N)
                xLimit = i + (height - i);
            if (j > width-N)
                yLimit = j + (width - j);

            tempRows = xLimit - i;
            tempCols = yLimit - j;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = i; x < xLimit; ++x) {
                for (y = j; y < yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_R[x][y];
                    ++index;
                }
            }
            frequentColor = mostFrequentValue(tempArray, tempRows*tempCols);
            newArrayRed[i][j] = frequentColor;
        }
    }

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            yLimit = j+N;
            xLimit = i+N;
            //To account for the corner cases
            if (i > height-N)
                xLimit = i + (height - i);
            if (j > width-N)
                yLimit = j + (width - j);

            tempRows = xLimit - i;
            tempCols = yLimit - j;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = i; x < xLimit; ++x) {
                for (y = j; y < yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_G[x][y];
                    ++index;
                }
            }
            frequentColor = mostFrequentValue(tempArray, tempRows*tempCols);
            newArrayGreen[i][j] = frequentColor;
        }
    }

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width ; ++j) {
            index =0;
            yLimit = j+N;
            xLimit = i+N;
            //To account for the corner cases
            if (i > height-N)
                xLimit = i + (height - i);
            if (j > width-N)
                yLimit = j + (width - j);

            tempRows = xLimit - i;
            tempCols = yLimit - j;
            int tempArray[tempRows * tempCols];
            memset(tempArray,0,tempRows*tempCols*sizeof(int));
            for (x = i; x < xLimit; ++x) {
                for (y = j; y < yLimit ; ++y) {
                    tempArray[index] = (int)Image2D_B[x][y];
                    ++index;
                }
            }
            frequentColor = mostFrequentValue(tempArray, tempRows*tempCols);
            newArrayBlue[i][j] = frequentColor;
        }
    }

    count = 0;

    while (count < totalBytes) {
        for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                Imagedata[count] = (unsigned char)newArrayRed[i][j];
                Imagedata[count + 1] = (unsigned char)newArrayGreen[i][j];
                Imagedata[count + 2] = (unsigned char)newArrayBlue[i][j];
                count = count + 3;
            }
        }
    }

    if (!(fptr1=fopen(argv[3],"wb"))) {
        cout << "Cannot open file." << endl;
        exit(1);
    }
    fwrite(Imagedata, sizeof(unsigned char),width*height*bytesPerPixel, fptr1);
    fclose(fptr1);

    return 0;
}
