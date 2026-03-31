#ifndef PACMAN_MUSIC_H
#define PACMAN_MUSIC_H

#include "musical_notes.h"
#include "sound.h"
#include <stdint.h>

/**
 *  contains the constants and music files in note format
 * 
 * NOTE: the const arrays store the files in a note | frequency format,
 * therefore transversals would be in 
*/

//
void _feed();

void pacman_intro_tune();

//void pacman_eating_pellet_sound();

//void fright_mode_siren();

void pacman_eating_ghost_sound();

void death_sound();

void waka_waka();

void fright_mode_sound();

#endif //!PACMAN_MUSIC_H