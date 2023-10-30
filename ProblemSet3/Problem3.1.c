#include <stdio.h>
#include <math.h> // import math header to use pow function

// Function to convert MIDI note number to frequency in Hz
float midi_to_frequency(int note) {
    // MIDI note frequency calculation using the formula: frequency = 440.0 * 2^((note - 69) / 12.0)
    double result = 440.0 * pow(2.0, (note - 69) / 12.0);
    return result; // Return the calculated frequency
}

// Main function where the program starts execution
int main() {
    int MidiNote; // Variable to store the MIDI note number

    // Prompt the user to enter the MIDI note number
    printf("Enter the MidiNote: ");

    // Read the user input and validate it
    if (scanf("%i", &MidiNote) != 1) {
        printf("Invalid. Enter a valid MidiNote.\n"); // Print an error message for invalid input
        return 1; // Return error code 1 to indicate an issue
    }

    // Calculate the frequency corresponding to the MIDI note
    float frequency = midi_to_frequency(MidiNote);

    // Print the MIDI note number and its corresponding frequency in Hertz
    printf("The frequency of MIDI note %i is %.2f Hz.\n", MidiNote, frequency);

    return 0; // Return 0 to indicate successful execution
}
