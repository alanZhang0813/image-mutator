//
// Created by alanz on 10/18/2023.
//
#include "Driver.h"
#include "Image.h"
#include <cstring>
#include <iostream>

Driver::Driver(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
}

void Driver::runCommandLine() {
    const char *inputName = argv[1];
    const char *outputName = argv[2];
    Image image(inputName, outputName);
    const char *transformationType = argv[3];

    if (argc == 6 && strcmp(transformationType, "6") == 0) {
        const char *size = argv[4];
        const char *color = argv[5];
        image.addBorder(size, color);
    }

    if (strcmp(transformationType, "1") == 0) {
        image.vertFlip();
    } else if (strcmp(transformationType, "2") == 0) {
        image.horizFlip();
    } else if (strcmp(transformationType, "3") == 0) {
        image.rotateCW();
    } else if (strcmp(transformationType, "4") == 0) {
        image.rotateCCW();
    } else if (strcmp(transformationType, "5") == 0) {
        image.pointillate();
    }
    image.writeImage();
}

void Driver::runTerminal() {
    char* inputPath = new char[100];
    char* outputPath = new char[100];
    std::cout << "Enter the path to your input image:" << std::endl;
    std::cin >> inputPath;
    std::cout << "Enter the path to where you want to output the image:" << std::endl;
    std::cin >> outputPath;
    Image image(inputPath, outputPath);
    char transformationType;
    while (transformationType != '7') {
        std::cout << "Here are your available transformations:" << std::endl
                  << "1: Flip vertically (x-axis reflection)" << std::endl
                  << "2: Flip horizontally (y-axis reflection)" << std::endl
                  << "3: Rotate clockwise" << std::endl
                  << "4: Rotate counterclockwise" << std::endl
                  << "5: Pointillate" << std::endl
                  << "6: Add border" << std::endl
                  << "7: End process" << std::endl;
        std::cin >> transformationType;
        processInput(image, transformationType);
    }
    image.writeImage();

    delete[] inputPath;
    delete[] outputPath;
}

void Driver::processInput(Image &image, char input) {
    if (input == '1') {
        image.vertFlip();
    }
    if (input == '2') {
        image.horizFlip();
    }
    if (input == '3') {
        image.rotateCW();
    }
    if (input == '4') {
        image.rotateCCW();
    }
    if (input == '5') {
        image.pointillate();
    }
    if (input == '6') {
        char* size = new char[5];
        char* color = new char[5];
        std::cout << "Enter a size for your border:" << std::endl;
        std::cin >> size;
        std::cout << "Enter a color for your border:" << std::endl;
        std::cin >> color;
        image.addBorder(size, color);
        delete[] size;
        delete[] color;
    }
}