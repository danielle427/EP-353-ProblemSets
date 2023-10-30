#include <stdio.h>
#include <math.h>

// Function to calculate frequency from MIDI note number
double midi_to_frequency(int note) {
    return 440 * pow(2, (note - 69) / 12.0);
}

// Function to calculate frequencies of MIDI notes in a chord
void frequencies_of_chord(int* chord, int size, float* frequencies) {
    for (int i = 0; i < size; i++) {
        frequencies[i] = midi_to_frequency(chord[i]);
    }
}

int main() {
    int size;

    // Prompt user to enter the number of MIDI notes
    printf("Enter the number of MIDI notes: ");
    scanf("%i", &size);

    int chord[size];
    float frequencies[size]; // Array to store frequencies

    // Prompt user to enter the MIDI notes of the chord
    printf("Enter the MIDI notes of the chord (separated by spaces): ");
    for (int i = 0; i < size; i++) {
        scanf("%i %i %i", &chord[0], &chord[1], &chord[2]);
    }

    // Call the function to calculate frequencies
    frequencies_of_chord(chord, size, frequencies);

    // Print the frequencies
    for (int i = 0; i < size; i++) {
        printf("The frequency of MIDI note %i is %.2f Hz.\n", chord[i], frequencies[i]);
    }


}
