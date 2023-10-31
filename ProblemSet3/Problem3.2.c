#include <stdio.h>
#include <math.h>

//calculate frequency from MIDI note
double midi_to_frequency(int note) {
    return 440.0 * pow(2.0, (note - 69) / 12.0);
}

//print chord frequencies
void print_chord_frequencies(int chord[], int size) {
    for (int i = 0; i < size; i++) {
        // Print the frequency of each MIDI note in the chord
        printf("The frequency of MIDI note %i is %.2f Hz.\n", chord[i], midi_to_frequency(chord[i]));
    }
}

int main() {
    int size;

    //the user to enter the number of MIDI notes
    printf("Enter the number of MIDI notes: ");
    scanf("%i", &size);

    int chord[size];

    //enter the MIDI notes of the chord (separated by spaces)
    printf("Enter the MIDI notes of the chord (separated by spaces): ");
    for (int i = 0; i < size; i++) {
        scanf("%i", &chord[i]);
    }

    //calculate and print the frequencies of the entered MIDI notes
    print_chord_frequencies(chord, size);
}
