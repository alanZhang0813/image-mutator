//
// Created by alanz on 10/8/2023.
//
#include "Pixel.h"
#ifndef IMAGELIB_IMAGE_H
#define IMAGELIB_IMAGE_H

class Image {
private:
    char const *inputName;
    char const *outputName;
    unsigned int width{};
    unsigned int height{};
    int argCount{};
    unsigned char *data{};
    Pixel **pixels{};
    void transpose();
    Pixel** convertTo2D(unsigned char *data, int width, int height, int args);
    unsigned char* convertTo1D(Pixel** data, int width, int height, int args);
public:
    Image(char const *input, char const *output);
    ~Image();
    void readImage();
    void vertFlip();
    void horizFlip();
    void rotateCW();
    void rotateCCW();
    void addBorder(char const *size, char const *color);
    void pointillate();
    void writeImage();
    void setWidth(unsigned int width);
    void setHeight(unsigned int height);
    void setArgCount(unsigned int argCount);
    void setPixels(Pixel **pixels);
};

#endif //IMAGELIB_IMAGE_H
