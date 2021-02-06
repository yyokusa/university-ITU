#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct rectangle
{
    int height;
    int width;
    int thickness;
} Rectangle;

bool get_possibility(int, int, int);
void draw_rectangle(int, int, int);

int main()
{
    Rectangle rectangle;
    int answer = 0;
    do
    {
        fprintf(stdout, "enter height: ");
        fscanf(stdin, "%d", &(rectangle.height));
        fprintf(stdout, "enter width: ");
        fscanf(stdin, "%d", &(rectangle.width));
        fprintf(stdout, "enter thickness: ");
        fscanf(stdin, "%d", &(rectangle.thickness));

        bool is_possible = get_possibility(rectangle.height, rectangle.width, rectangle.thickness);
        if (is_possible)
        {
            draw_rectangle(rectangle.height, rectangle.width, rectangle.thickness);
        }
        else
        {
            fprintf(stdout, "It is not possible to draw your rectangle with the specified thickness.\n");
            draw_rectangle(rectangle.height, rectangle.width, rectangle.thickness);
        }

        fprintf(stdout, "1 for another, 0 for exit: ");
        fscanf(stdin, "%d", &answer);
    } while (answer);

    return EXIT_SUCCESS;
}

bool get_possibility(int height, int width, int thickness)
{
    int temp = thickness * 2;
    if (temp >= height && temp >= width)
    {
        return false;
    }
    return true;
}

void draw_rectangle(int height, int width, int thickness)
{
    int temp = thickness * 2;
    if (temp < height && temp < width)
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (i < thickness || j < thickness ||j > width - 1 - thickness || i > height - 1 - thickness)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        
    }
    else if (temp < height && !(temp < width))
    {
        int tempThickness = thickness;
        while (!(tempThickness * 2 < width))
        {
            tempThickness -= 1; 
        }
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (i < thickness || j < tempThickness ||j > width - 1 - tempThickness || i > height - 1 - thickness)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    else if (!(temp < height) && temp < width)
    {
        int tempThickness = thickness;
        while (!(tempThickness * 2 < width))
        {
            tempThickness -= 1; 
        }
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                if (i < tempThickness || j < thickness ||j > width - 1 - thickness || i > height - 1 - tempThickness)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    else
    {
        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
            {
                printf("*");
            }
            printf("\n");
        }
    }
    
}

// BIL 105E – Introduction to Scientific and Engineering Computing (C)
// Spring 2014-2015
// Homework 1
// You will write a C program (rectangle.c) that uses “*” character to draw a rectangle of a given height,
//  width and thickness. The program first asks the user to enter the height, width and thickness of the shape.
// If the user want to draw a rectangle, all three parameters should be given by the user.
// The thickness of a shape indicates the number of stars(*) between the inner space and the outer shell of a shape.

//  You need to make a calculation beforehand to inform the user if it is feasible to draw a shape with the thickness value provided.
// If it is not possible to draw a rectangle with the specified thickness value, the user should be informed with a message
//  “It is not possible to draw your rectangle with the specified thickness.
//  The rectangle without the thickness option is drawn below:” and the rectangle should be drawn without any thickness (see the example below).
// Notice that thickness cannot be achieved in all four sides of a rectangle. For example, when the rectangle
// is 7 (h) x 5 (w) with a thickness of 3, you can draw a rectangle whose upper and lower sides have a thickness of 3, but the
//  left and right sides would have a thickness of 2 at maximum (see the example below).
// After the first drawing, the program asks the user if he/she wants to continue drawing more rectangles.
//  If the user wants to continue, 1 is given, otherwise 0 is given. When 0 is given by the user, the program terminates.
//  When 1 is given by the user, the program asks the user to enter height, width and thickness of the rectangle again.
// You can assume that the inputs are valid integers from 1 to 20 (inclusive). Based on the user inputs,
//  you will draw the shape to the console.

// Below are sample outputs from the execution of the program:
// Enter the height for your rectangle: 10
// Enter the width for your rectangle: 7
// Enter the thickness: 2
// ********
// ********
// **    **
// **    **
// **    **
// **    **
// **    **
// **    **
// ********
// ********

// Do you want to continue? (1 for Yes, 0 for No): 1

// Enter the height for your rectangle: 7

// Enter the width for your rectangle: 5

// Enter the thickness: 3

// *****

// *****

// *****

// ** **

// *****

// *****

// *****

// Do you want to continue? (1 for Yes, 0 for No): 1

// Enter the height for your rectangle: 5

// Enter the width for your rectangle: 4

// Enter the thickness: 2

// ****

// ****

// *  *

// ****

// ****

// Do you want to continue? (1 for Yes, 0 for No): 1

// Enter the height for your rectangle: 3

// Enter the width for your rectangle: 3

// Enter the thickness: 2

// It is not possible to draw your rectangle with the specified thickness. The rectangle without the thickness option is drawn below:

// ***

// ***

// ***

// Do you want to continue? (1 for Yes, 0 for No): 0

// }