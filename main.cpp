#include "Image.h"
#include "Driver.h"
#include <iostream>

//a sample controller, if you will
int main(int argc, char** argv) {
    Driver driver(argc, argv);
    if (argc == 1) {
        driver.runTerminal();
    } else if (argc == 4 || argc == 6){
        driver.runCommandLine();
    } else {
        std::cout << "Please enter an appropriate number of command line arguments or none at all" << std::endl;
    }
}