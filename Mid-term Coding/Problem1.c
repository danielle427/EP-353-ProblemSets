/*
    Program: Matrix Pattern Printer
    Purpose: This program takes user input for the width and height of a matrix and prints a pattern 
             based on the specified rules. The matrix values are calculated using the position of each
             element, providing a unique pattern. The program uses functions for modularity and clarity.

    How to Run:
    1. Compile the program using a C compiler (e.g., gcc).
       Example: gcc matrix_pattern_printer.c -o matrix_pattern_printer
    2. Run the executable.
       Example: ./matrix_pattern_printer
    3. Follow the prompts to enter the width and height.
       The program will then display the corresponding matrix pattern.
*/
#include <stdio.h>

// Function prototype
void printMatrix(int width, int height);

int main() {
    int width, height;

    // Ask the user for width and height
    printf("Enter the width: ");
    scanf("%i", &width);
    printf("Enter the height: ");
    scanf("%i", &height);

    // Call the printMatrix function
    printMatrix(width, height);

    return 0;
}

// Function to print the number matrix
void printMatrix(int width, int height) {
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Calculate the value based on the position
            int value = (i + j) % height + 1;
            
            // Print the value
            if(value<height){
                printf("%i", value);
            } else{
                printf("%i", value%height);
            }
        }
        printf("\n");
    }
}
