/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include "SDL_mixer.h"
#include <stdbool.h>

/**
 * 
 * @param pathToSound Le chemin vers le sound a charger
 * @return Mix_Chunk* contenant le son charge
 */
Mix_Chunk* loadShortSound(const char *pathToSound);

/**
 * 
 * @param Mix_Chunk* le son a jouer
 * 
 */
void playShortSound(Mix_Chunk* toPlay);