[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/zpqZ1nWS)
# CS3520 - PA02 - Image Processing in C++

Developer Name: _Alan Zhang_

## How to Run the Program

To run this program, there are two modes.

In the command line argument mode, you will need to input command line arguments in a specific order.
First, the image's relative input path. Second, the output image's path. 
The third argument denotes which kind of transformation the user desires. After transforming, the output is written.

1: The image flips vertically (x-axis reflection).

2: The image flips horizontally (y-axis reflection).

3: The image rotates clockwise.

4: The image rotates counterclockwise.

5: The image is drawn in a way inspired by pointillism

If the input number is 6, the image is given a border, which requires two more command line arguments.
The two extra arguments are first the size of the border, and then the color which can be red, green, or blue.

In the terminal input mode, which is caused when there are zero command line arguments, the terminal will have prompts.