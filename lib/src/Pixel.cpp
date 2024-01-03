#include "Pixel.h"
#include <cstring>

//
// Created by alanz on 10/8/2023.
//

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
    grey = 0;
    argCount = 4;
}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    alpha = 1;
    grey = 0;
    argCount = 3;
}

Pixel::Pixel(unsigned char grey, unsigned char alpha) {
    this->grey = grey;
    this->alpha = alpha;
    red = 0;
    green = 0;
    blue = 0;
    argCount = 2;
}

Pixel::Pixel(unsigned char grey) {
    this->grey = grey;
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
    argCount = 1;
}

Pixel::~Pixel() {
    red = 0;
    green = 0;
    blue = 0;
    alpha = 0;
    grey = 0;
    argCount = 0;
}

void Pixel::changeColor(const Pixel& otherPixel) {
    if (otherPixel.argCount == 4) {
        this->red = otherPixel.red;
        this->green = otherPixel.green;
        this->blue = otherPixel.blue;
        this->alpha = otherPixel.alpha;
    } else if (otherPixel.argCount == 3) {
        this->red = otherPixel.red;
        this->green = otherPixel.green;
        this->blue = otherPixel.blue;
    } else if (otherPixel.argCount == 2) {
        this->grey = otherPixel.grey;
        this->alpha = otherPixel.alpha;
    } else if (otherPixel.argCount == 1) {
        this->grey = otherPixel.grey;
    }
}

unsigned char Pixel::getRed() const {
    return red;
}

void Pixel::setRed(unsigned char red) {
    Pixel::red = red;
}

unsigned char Pixel::getGreen() const {
    return green;
}

void Pixel::setGreen(unsigned char green) {
    Pixel::green = green;
}

unsigned char Pixel::getBlue() const {
    return blue;
}

void Pixel::setBlue(unsigned char blue) {
    Pixel::blue = blue;
}

unsigned char Pixel::getAlpha() const {
    return alpha;
}

void Pixel::setAlpha(unsigned char alpha) {
    Pixel::alpha = alpha;
}

unsigned char Pixel::getGrey() const {
    return grey;
}

void Pixel::setGrey(unsigned char grey) {
    Pixel::grey = grey;
}

void Pixel::setColor(const char *color) {
    if (strcasecmp(color, "red") == 0) {
        setRed(255);
        setGreen(0);
        setBlue(0);
        setAlpha(1);
        setGrey(0);
    } else if (strcasecmp(color, "green") == 0) {
        setRed(0);
        setGreen(255);
        setBlue(0);
        setAlpha(1);
        setGrey(0);
    } else if (strcasecmp(color, "green") == 0) {
        setRed(0);
        setGreen(255);
        setBlue(0);
        setAlpha(1);
        setGrey(0);
    }
}