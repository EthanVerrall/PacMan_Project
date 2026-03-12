#include "../../include/music&sound/tones.h"

void _feed(){}

//note | frequency


uint16_t pacman_intro(){

    static uint8_t pointer = 0;

    if (pointer == 70)
    {
        pointer = 0;
    }
    
    const uint16_t notes[] = {
        C3, 500, C6,500, G6,500, E6,500, C6,500, G6,500, E6,500,
        D3,500, D6,500, A6,500, FS6_Gb6,500, D6,500, A6,500, FS6_Gb6,500,
        C3,500, C6,500, G6,500, E6,500, C6,500, G6,500, E6,500,
        
        FS6_Gb6,50,G6,50,GS6_Ab6,50,A6,200,
        G6,50,GS6_Ab6,50,A6,50,AS6_Bb6,200,
        GS6_Ab6,50,A6,50,AS6_Bb6,50,B6,200,
        C7,200,C7, 200
    };

    pointer++;

    return notes[pointer];
}

void pacman_eating_pellet(){}

void _in_fright_mode(){}

void pacman_eating_ghost(){}