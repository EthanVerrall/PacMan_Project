#include "../../include/music&sound/tones.h"

void _feed(){}

//note | frequency


void pacman_intro(){
    const uint16_t notes[] = {
        // 4 8th notes per line
        C4,150 , C5,150, G4,150, E4,150, C5,75, G4,150, 0,75, E4,150, 0, 150,
        CS4_Db4,150, CS5_Db5,150, GS4_Ab4,150, F4,150, CS5_Db5,75, GS4_Ab4,150, 0,75, F4,150, 0, 150,
        C4,150, C5,150, G4,150, E4,150, C5,75, G4,150, 0,75, E4,150, 0, 150,
		
		// 4 16th notes per line (except last)
        F4,75, FS4_Gb4,75, G4,75, 0,75,
        FS4_Gb4,75, G4,75, GS4_Ab4,75, 0,75,
        GS4_Ab4,75, A4,75, AS4_Bb4,75, 0,75,
        C5,150, 0,150 
    };

    for (uint16_t i = 0; i < 82; i+=2)
    {
        playNote(notes[i]);
        delay(notes[i + 1]);
    }
}

void pacman_eating_pellet(){}

void _in_fright_mode(){}

void pacman_eating_ghost(){}