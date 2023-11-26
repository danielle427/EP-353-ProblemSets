/*
    Program: Musical Scale Printer
    Purpose: This program allows the user to select a musical scale mode (Ionian, Dorian, or Phrygian)
             and a root note. It then prints the seven pitches in the selected scale, considering
             the specified root note. The program uses enums, structs, and functions for a clear
             and modular structure.

    How to Run:
    1. Compile the program using a C compiler (e.g., gcc).
       Example: gcc musical_scale_printer.c -o musical_scale_printer
    2. Run the executable.
       Example: ./musical_scale_printer
    3. Follow the prompts to enter the scale mode and root note.
       The program will then display the corresponding musical notes.
*/

#include <stdio.h>

// Enum defining the scale modes
typedef enum Mode {
    Ionian, Dorian, Phrygian
} Mode;

// Struct representing a musical note
typedef struct Note {
    unsigned char pitch;
    unsigned char velocity;
    unsigned char channel;
} Note;

// Struct representing a musical scale
typedef struct Scale {
    Note notes[7];
    unsigned char rootNote;
} Scale;

// Function prototypes
void printScale(const Scale *scale);

int main() {
    // Declaration and initialization of scale modes
    Scale ionian = {{
        {0, 127, 1},
        {2, 127, 1},
        {4, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {9, 127, 1},
        {11, 127, 1}},
        60};

    Scale dorian = {{
        {0, 127, 1},
        {2, 127, 1},
        {3, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {9, 127, 1},
        {10, 127, 1}},
        60};

    Scale phrygian = {{
        {0, 127, 1},
        {1, 127, 1},
        {3, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {8, 127, 1},
        {10, 127, 1}},
        60};

    // User input for scale mode selection
    int selectedMode;
    printf("Enter the scale mode (0 for Ionian, 1 for Dorian, 2 for Phrygian): ");
    scanf("%i", &selectedMode);

    Scale selectedScale;

    // Switch statement to select the appropriate scale based on user input
    switch (selectedMode) {
        case Ionian:
            selectedScale = ionian;
            break;
        case Dorian:
            selectedScale = dorian;
            break;
        case Phrygian:
            selectedScale = phrygian;
            break;
        default:
            printf("Invalid mode selection\n");
            return 1; // Exit with an error code
    }

    // User input for root note selection
    printf("Enter the root note (0 ~ 127): ");
    scanf("%hhu", &selectedScale.rootNote);

    // Printing the notes in the selected scale with the provided root note
    printf("Notes: ");
    printScale(&selectedScale);

    return 0;
}

// Function to print the seven pitches in the selected Scale variable
void printScale(const Scale *scale) {
    for (int i = 0; i < 7; i++) {
        printf("%d ", (scale->notes[i].pitch + scale->rootNote) % 128);
    }
    printf("\n");
}
