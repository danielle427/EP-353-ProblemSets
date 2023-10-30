#include <stdio.h>

//Define a structure MIDINote
struct MIDINote {
    int pitch;
    int velocity;
    int channel;
};

//Function to print a single MIDINote
void print_note(struct MIDINote note) {
    printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", note.pitch, note.velocity, note.channel);
}

//Function to input MIDI notes and store them in the array
void input_notes(struct MIDINote notes[], int size) {
    int pitch[size], velocity[size], channel[size];

    //Get the MIDI note values from the user.
    printf("Enter MIDI pitch velocity channel values at once using space and comma: ");
    scanf("%i %i %i", &pitch[0], &velocity[0], &channel[0]);

    for (int i = 1; i < size; i++) {
        scanf(", %i %i %i", &pitch[i], &velocity[i], &channel[i]);
    }

    //Copy the MIDI note values to the `notes` array.
    for (int i = 0; i < size; i++) {
        notes[i].pitch = pitch[i];
        notes[i].velocity = velocity[i];
        notes[i].channel = channel[i];
    }
}


int main() {
    int size;

    //Prompt the user to enter the number of MIDI notes
    printf("How many MIDI notes to enter? ");

    scanf("%i", &size);

    struct MIDINote notes[size]; //Declare an array of MIDINotes

    //Input MIDI notes and store them in the array
    input_notes(notes, size);

    //Print the entered MIDI notes
    for (int i = 0; i < size; i++) {
        print_note(notes[i]);
    }


}
