//
// Created by alanz on 10/18/2023.
//
#include "Image.h"
#ifndef IMAGELIB_DRIVER_H
#define IMAGELIB_DRIVER_H

class Driver {
private:
    int argc;
    char** argv;
    void processInput(Image &image, char input);
public:
    Driver(int argc, char** argv);
    void runCommandLine();
    void runTerminal();
};

#endif //IMAGELIB_DRIVER_H
