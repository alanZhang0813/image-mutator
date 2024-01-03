//
// Created by alanz on 10/7/2023.
//

#ifndef IMAGELIB_PIXEL_H
#define IMAGELIB_PIXEL_H

class Pixel {
private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    unsigned char grey;
    unsigned char argCount;

public:
    //Constructor for four args
    Pixel(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    //Constructor for three args
    Pixel(unsigned char red, unsigned char green, unsigned char blue);
    //Constructor for two args
    Pixel(unsigned char grey, unsigned char alpha);
    //Constructor for one arg
    explicit Pixel(unsigned char grey);
    //Default Constructor
    Pixel() = default;
    //Destructor
    ~Pixel();

    void changeColor(const Pixel& otherPixel);

    unsigned char getRed() const;
    void setRed(unsigned char red);
    unsigned char getGreen() const;
    void setGreen(unsigned char green);
    unsigned char getBlue() const;
    void setBlue(unsigned char blue);
    unsigned char getAlpha() const;
    void setAlpha(unsigned char alpha);
    unsigned char getGrey() const;
    void setGrey(unsigned char grey);
    void setColor(const char* color);
};

#endif //IMAGELIB_PIXEL_H
