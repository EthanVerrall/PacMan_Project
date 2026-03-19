#ifndef PACMAN_MUSIC_H
#define PACMAN_MUSIC_H

#include "musical_notes.h"
#include <stdint.h>

/**
 *  contains the constants and music files in note format
 * 
 * NOTE: the const arrays store the files in a note | frequency format,
 * therefore transversals would be in 
*/

//
void _feed();

void pacman_intro();

void pacman_eating_pellet();

void _in_fright_mode();

void pacman_eating_ghost();

#endif //!PACMAN_MUSIC_H