#include <stdio.h>

//define a structure MIDINote
struct MIDINote {
    int pitch;
    int velocity;
    int channel;
};

//input MIDI notes and store them in the array
void input_notes(struct MIDINote notes[], int size) {
    // Prompt the user to enter the MIDI notes.
    printf("Enter the MIDI notes (pitch velocity channel, separated by commas and spaces):\n");

    //recieve the MIDI notes from the user
    for (int i = 0; i < size; i++) {
        scanf("%i %i %i", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);

        //pitch range 0-127
        if (notes[i].pitch < 0) {
            notes[i].pitch = 0;
        } else if(notes[i].pitch > 127) {
            notes[i].pitch = 127;
        }

        //velocity range 0-127
        if (notes[i].velocity < 0) {
            notes[i].velocity = 0;
        } else if (notes[i].velocity > 127) {
            notes[i].velocity = 127;
        }

        //channel range 1-16
        if (notes[i].channel < 1) {
            notes[i].channel = 1;
        } else if (notes[i].channel > 16) {
             notes[i].channel = 16;
        }
    }
}

//transpose the notes
void transpose_notes(struct MIDINote notes[], int size, int steps) {
    for (int i = 0; i < size; i++) {
        //transpose pitch by adding the number of steps
        notes[i].pitch += steps;

        // pitch range 0-127
        if(notes[i].pitch < 0) {
            notes[i].pitch = 0;} 
            else if (notes[i].pitch > 127) {
            notes[i].pitch = 127;
        }
    }
}

//print a MIDINote
void print_note(struct MIDINote note) {
    printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", note.pitch, note.velocity, note.channel);
}

int main() {
    int size;
    int step;

    //the user to enter the number of MIDI notes.
    printf("How many MIDI notes to enter?: ");
    scanf("%i", &size);

    struct MIDINote notes[size]; //declare array MIDINotes 

    //input the MIDI notes
    input_notes(notes, size);

    //the user to enter the number of steps to transpose
    printf("Enter the number of steps to transpose (0 ~ 11): ");
    scanf("%i", &step);

    //transpose the notes
    transpose_notes(notes, size, step);

    //print the transposed notes
    printf("\n");
    for (int i = 0; i < size; i++) {
        print_note(notes[i]);
    }

}
