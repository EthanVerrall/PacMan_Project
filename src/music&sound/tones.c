#include "../../include/music&sound/tones.h"

void play_rising_frequency(uint16_t start_pitch, uint16_t end_pitch, uint16_t grain){
    for (uint16_t i = start_pitch; i < end_pitch; i+=grain)
    {
        playNote(i);
        delay(3);
    }
    playNote(0);
}
void play_falling_frequency(uint16_t start_pitch, uint16_t end_pitch, uint16_t grain){
    for (uint16_t i = start_pitch; i < end_pitch; i-=grain)
    {
        playNote(i);
        delay(3);
    }
    playNote(0);
}

void _feed(){}

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

void waka_waka(){
    playNote(F2);
    delay(30);
    playNote(A2);
    delay(30);
    playNote(D3);
    delay(30);
    playNote(F4);
    delay(30);
    playNote(0);
    delay(30);

    playNote(CS4_Db4);
    delay(30);
    playNote(F4);
    delay(30);
    playNote(D3);
    delay(30);
    playNote(A2);
    delay(30);
    playNote(0);
    delay(30);
}

void fright_mode_sound(){
    playNote(CS6_Db6);
    delay(40);
    playNote(E6);
    delay(40);
    playNote(GS6_Ab6);
    delay(40);
    playNote(CS7_Db7);
    delay(40);
    playNote(0);
}

void pacman_eating_ghost_sound(){
    play_rising_frequency(A1, E6, 5);
}

// UNFINISHED
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

    for (uint16_t i = 0; i < 64; i+=2)
    {
        playNote(notes[i]);
        delay(notes[i + 1]);
    }   
}