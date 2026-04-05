#include "../../include/music&sound/tones.h"

static bool is_music_on = true;

void turn_on_music(const bool music_flag) {
    is_music_on = music_flag;
}

bool get_music_setting() {

    return is_music_on;
}

//note | frequency

void pacman_intro_tune(){
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

uint16_t waka_waka(){
    static uint8_t counter = 0;
    const uint16_t notes[] = {
        // 4 8th notes per line
        F2,40, A2,40, D3,40, F4,40, 0,40,
        CS4_Db4,40, F4,40, D3,40, A2,40, 0,40,
    };
    counter++;
    if(counter >= 20) counter = 0;
    return notes[counter];
}


uint16_t fright_mode_sound(){
    static uint8_t counter = 0;
    const uint16_t notes[] = {
        // 4 8th notes per line
        F6, E6, CS6_Db6, 0,
        F6, E6, CS6_Db6, 0,
    };

    counter++;
    if(counter >= 8) counter = 0;
    return notes[counter];
}

void winning_music(){
    const uint16_t notes[] = {
        // 4 8th notes per line
        F6,40, E6,40, CS6_Db6,40, 0,40,
        F6,40, E6,40, CS6_Db6,40, 0,40,
        F6,40, E6,40, CS6_Db6,40, 0,40,
        F6,40, E6,40, CS6_Db6,40, 0,40,
    };

    for (uint16_t i = 0; i < 32; i+=2)
    {
        playNote(notes[i]);
        delay(notes[i + 1]);
    }   
}

void death_sound(){
    const uint16_t notes[] = {
        // 4 8th notes per line
        F6,40, FS6_Gb6,40, G6,40,
        E6,40, F6,40, FS6_Gb6,40,
        DS6_Eb6,40, E6,40, F6,40,
        D6,40, DS6_Eb6,40, E6,40,
        CS6_Db6,40, D6,40, DS6_Eb6,40,
        C6,40, CS6_Db6,40, D6,40,
        
        FS3_Gb3,40, AS3_Bb3,40, C6,60, E7,40, AS7_Bb7,40, C8,40,
        FS3_Gb3,40, AS3_Bb3,40, C6,60, E7,40, AS7_Bb7,40, C8,40,
        0,1
    };

    for (uint16_t i = 0; i < 62; i+=2)
    {
        playNote(notes[i]);
        delay(notes[i + 1]);
    }   
}