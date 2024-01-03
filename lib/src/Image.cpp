//
// Created by alanz on 10/8/2023.
//
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>
#include "Image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(char const *input, char const *output) {
    inputName = input;
    outputName = output;
    readImage();
}

Image::~Image() {
    delete[] data;
    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
    }
    delete[] pixels;
}

void Image::readImage() {
    int w,h,args;
    unsigned char *imageData = stbi_load(inputName, &w, &h, &args, 0);
    setPixels(convertTo2D(imageData, w, h, args));
    setWidth(w);
    setHeight(h);
    setArgCount(args);

    stbi_image_free(imageData);
}

Pixel** Image::convertTo2D(unsigned char *data, int width, int height, int args) {
    Pixel** resultPixels;
    if (data != nullptr) {
        resultPixels = new Pixel*[height];
        for (int i = 0; i < height; i++) {
            resultPixels[i] = new Pixel[width];
            for (int j = 0; j < width; j++) {
                int margin = (i * width + j) * args;
                // Create a Pixel object based on the color channel values
                if (args == 3) {
                    resultPixels[i][j] = Pixel(data[margin], data[margin + 1], data[margin + 2]);
                } else if (args == 4) {
                    resultPixels[i][j] = Pixel(data[margin], data[margin + 1], data[margin + 2],
                                         data[margin + 3]);
                } else if (args == 1) {
                    resultPixels[i][j] = Pixel(data[margin]);
                } else if (args == 2) {
                    resultPixels[i][j] = Pixel(data[margin], data[margin + 1]);
                }
            }
        }
    }
    return resultPixels;
}

//Also known as the x-axis reflection
void Image::vertFlip() {
    for (int r = 0; r < height / 2; r++) {
        for (int c = 0; c < width; c++) {
            Pixel temp = pixels[r][c];
            pixels[r][c] = pixels[height- r - 1][c];
            pixels[height- r - 1][c] = temp;
        }
    }
}

//Also known as the y-axis reflection
void Image::horizFlip() {
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width / 2; c++) {
            Pixel temp = pixels[r][c];
            pixels[r][c] = pixels[r][width - 1 - c];
            pixels[r][width - 1 - c] = temp;
        }
    }
}

//Transpose the image, swapping width and height
void Image::transpose() {
    auto** rotatedPixels = new Pixel*[width];
    for (int c = 0; c < width; c++) {
        rotatedPixels[c] = new Pixel[height];
        for (int r = 0; r < height; r++) {
            rotatedPixels[c][r] = pixels[r][c];
        }
    }
    unsigned int temp = width;
    setWidth(height);
    setHeight(temp);
    setPixels(rotatedPixels);
}

//Y-axis reflection, then transpose
void Image::rotateCCW() {
    this->horizFlip();
    this->transpose();
}

//X-axis reflection, then transpose
void Image::rotateCW() {
    this->vertFlip();
    this->transpose();
}

//Adds a border, where size and color are additional program arguments
void Image::addBorder(char const *size, char const *color) {
    std::stringstream sizeString;
    sizeString << size;
    unsigned int sizeValue;
    sizeString >> sizeValue;
    unsigned int newHeight = height + sizeValue * 2;
    unsigned int newWidth = width + sizeValue * 2;
    //allocating memory for a new, larger 2D array of pixels
    auto **newPixels = new Pixel*[newHeight];
    for (int i = 0; i < newHeight; i++) {
        newPixels[i] = new Pixel[newWidth];
    }
    //moving every original pixel over, leaving space in the borders
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            newPixels[r + sizeValue][c + sizeValue] = pixels[r][c];
        }
    }
    //coloring in the border
    for (int r = 0; r < newHeight; r++) {
        for (int c = 0; c < newWidth; c++) {
            if (r < sizeValue || r > newHeight - sizeValue || c < sizeValue || c > newWidth - sizeValue) {
                newPixels[r][c].setColor(color);
            }
        }
    }
    //deallocating the memory and reassigning values
    for (int i = 0; i < height; i++) {
        delete[] pixels[i];
    }
    delete[] pixels;
    setPixels(newPixels);
    setHeight(newHeight);
    setWidth(newWidth);
}

void Image::pointillate() {
    unsigned int numIterations = width + height;
    for (int i = 0; i < numIterations; i++) {
        unsigned int randRadius = 1 + (rand() % (int)sqrt(height + width) / 2);
        unsigned int randRow = rand() % height;
        unsigned int randCol = rand() % width;
        Pixel randPixel = pixels[randRow][randCol];

        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                if (((randRow - r) * (randRow - r) + (randCol - c) * (randCol - c)) <= (randRadius * randRadius)) {
                    pixels[r][c].changeColor(randPixel);
                }
            }
        }
    }
}

unsigned char* Image::convertTo1D(Pixel **data, int width, int height, int argCount) {
    auto* pixelData = new unsigned char[height*width*argCount];
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int index2D = r * width + c;
            int index1D = index2D * argCount;
            if (argCount == 3) {
                pixelData[index1D] = pixels[r][c].getRed();
                pixelData[index1D + 1] = pixels[r][c].getGreen();
                pixelData[index1D + 2] = pixels[r][c].getBlue();
            } else if (argCount == 4) {
                pixelData[index1D] = pixels[r][c].getRed();
                pixelData[index1D + 1] = pixels[r][c].getGreen();
                pixelData[index1D + 2] = pixels[r][c].getBlue();
                pixelData[index1D + 3] = pixels[r][c].getAlpha();
            } else if (argCount == 2) {
                pixelData[index1D] = pixels[r][c].getGrey();
                pixelData[index1D + 1] = pixels[r][c].getAlpha();
            } else if (argCount == 1) {
                pixelData[index1D] = pixels[r][c].getGrey();
            }
        }
    }
    return pixelData;
}

void Image::writeImage() {
    unsigned char* pixelData = convertTo1D(pixels, width, height, argCount);
    char const* fileType = outputName + std::strlen(outputName) - 3;
    if (strcmp(fileType, "png") == 0) {
        stbi_write_png(outputName, width, height, argCount, pixelData, 0);
    } else if (strcmp(fileType, "bmp") == 0) {
        stbi_write_bmp(outputName, width, height, argCount, pixelData);
    } else if (strcmp(fileType, "jpg") == 0) {
        stbi_write_jpg(outputName, width, height, argCount, pixelData, 0);
    } else if (strcmp(fileType, "hdr") == 0) {
        stbi_write_hdr(outputName, width, height, argCount, reinterpret_cast<const float *>(pixelData));
    } else if (strcmp(fileType, "tga") == 0) {
        stbi_write_tga(outputName, width, height, argCount, pixelData);
    }
    delete[] pixelData;
}

void Image::setWidth(unsigned int width) {
    Image::width = width;
}

void Image::setHeight(unsigned int height) {
    Image::height = height;
}

void Image::setArgCount(unsigned int argCount) {
    Image::argCount = argCount;
}

void Image::setPixels(Pixel **pixels) {
    Image::pixels = pixels;
}
