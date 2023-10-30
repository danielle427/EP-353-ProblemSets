#include <stdio.h>

char* IntervalName(int interval) {
    switch (interval) {
        case 0: return "unison";
        case 1: return "minor second";
        case 2: return "major second";
        case 3: return "minor third";
        case 4: return "major third";
        case 5: return "perfect fourth";
        case 6: return "tritone";
        case 7: return "perfect fifth";
        case 8: return "minor sixth";
        case 9: return "major sixth";
        case 10: return "minor seventh";
        case 11: return "major seventh";
        default: return "unknown interval";
    }
}

int main() {
    char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    int num_notes = 12;

    printf("The interval from note 0 to note 0 is a unison.\n");

    for (int i = 0; i < num_notes; i++) {
        for (int j = 0; j < num_notes; j++) {
            int interval = (j - i + num_notes) % num_notes;
            printf("The interval from note %d to note %d is a %s.\n", i, j, IntervalName(interval));
        }
        printf("\n");
    }

}



