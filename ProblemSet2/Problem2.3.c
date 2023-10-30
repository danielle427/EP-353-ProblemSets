#include <stdio.h>

int main(){
    int MIDIpitch;
    printf("Enter MIDI pitch");
    scanf("%i",&MIDIpitch);

    if (MIDIpitch >= 0 && MIDIpitch <= 127) {
        int octav = MIDIpitch / 12 - 1;
        printf("The octave for MIDI pitch %i: %i\n", MIDIpitch, octav);
            }
    else {
        printf("Invalid. the MIDI pitch must be between 0 and 127.");
    }

}