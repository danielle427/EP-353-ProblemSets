#include <stdio.h>

int main(){

    int MIDIpitch;
    int pitch;
    int value;
    while (MIDIpitch != -1){

    printf("Enter the MIDIpitch\n");
    scanf("%i",&MIDIpitch);

    int octave = MIDIpitch / 12 - 1;
    int note = MIDIpitch % 12;783
    char MIDInote;
   

    switch (note)    {

        case 1: MIDInote ='C'; break;
        case 2: printf("C#"); break;
        case 3: MIDInote ='D'; break;
        case 4: printf("D#"); break;
        case 5: MIDInote ='E'; break;
        case 6: MIDInote ='F'; break;
        case 7: MIDInote ='G'; break;
        case 8: printf("G#"); break;
        case 9: MIDInote ='A'; break;
        case 10: printf("A#"); break;
        case 11: MIDInote ='B'; break;
    default: printf("Invalid. The MIDI pitch must be between 0 and 127.\n"); return 0;
    }

    
    if (MIDIpitch >= 0 && MIDIpitch <= 127) {
        printf("The MIDI note %i is %c in octave %i\n", MIDIpitch, MIDInote, octave);

    }
    
    else{
        printf("Invalid. the MIDI pitch must be between 0 and 127.\n");

    }
    }
}