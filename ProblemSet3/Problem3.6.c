#include <stdio.h>

// Define a MIDI note structure.
typedef struct {
  int pitch;
  int velocity;
  int channel;
} MIDINote;

// Transpose the MIDI notes in the given array by the specified number of steps.
void transpose_notes(MIDINote* notes, int size, int steps) {
  for (int i = 0; i < size; i++) {
    notes[i].pitch += steps;
    // Keep the pitch within the valid range (0-127).
    if (notes[i].pitch < 0) {
      notes[i].pitch += 128;
    } else if (notes[i].pitch > 127) {
      notes[i].pitch -= 128;
    }
  }
}

int main() {
  // Ask the user how many MIDI notes to enter.
  int size;
  printf("How many MIDI notes to enter?: ");
  scanf("%i", &size);

  // Allocate an array of MIDI notes based on the user input.
  MIDINote notes[size];

  // Prompt the user to enter the MIDI notes.
  for (int i = 0; i < size; i++) {
    int pitch, velocity, channel;
    printf("Enter MIDI note %d (pitch velocity channel): ", i + 1);
    scanf("%i %i %i", &pitch, &velocity, &channel);

    // Store the MIDI note in the array.
    notes[i].pitch = pitch;
    notes[i].velocity = velocity;
    notes[i].channel = channel;
  }

  // Ask the user to enter the number of steps to transpose the notes.
  int steps;
  printf("Enter the number of steps to transpose the notes: ");
  scanf("%i", &steps);

  // Transpose the MIDI notes.
  transpose_notes(notes, size, steps);

  // Print out the transposed notes.
  printf("The transposed notes are (0 ~ 11):\n");
  for (int i = 0; i < size; i++) {
    printf("MIDI note %i: pitch %i, velocity %i, channel %i\n", i + 1, notes[i].pitch, notes[i].velocity, notes[i].channel);
  }

}
