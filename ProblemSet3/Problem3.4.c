#include <stdio.h>

//Define a structure MIDINote
struct MIDINote {
    int pitch;
    int velocity;
    int channel; };

//Function to print a MIDINote
void print_note(struct MIDINote note) {
    printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", note.pitch, note.velocity, note.channel);
}

int main() {
    struct MIDINote note; //Declare a MIDINote variable. the user to enter pitch, velocity, and channel
    printf("Enter pitch: ");
    scanf("%i", &note.pitch);
    printf("Enter velocity: ");
    scanf("%i", &note.velocity);
    printf("Enter channel: ");
    scanf("%i", &note.channel);

    //call the function to print the details of the note
    print_note(note);


}
