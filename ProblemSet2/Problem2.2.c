#include <stdio.h>
#include <math.h>

int main(){
    int C4 = 60;
    int A4 = 69;
    
    
    double Cfreq = pow(2, ((double)C4 - 69)/12)*440;
    double Afreq = pow(2, ((double)A4 - 69)/12)*440;

    printf("The frequency for MIDI pitch %i (C4): %f Hz\n", C4, Cfreq);
    printf("The frequency for MIDI pitch %i (A4): %f Hz\n", A4, Afreq);




}