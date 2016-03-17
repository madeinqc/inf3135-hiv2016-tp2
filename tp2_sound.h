/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include "SDL_mixer.h"
#include <stdbool.h>

/**
 * Ouvre le canal de son
 */
void openSound();

/**
 * Load un nouveau son court
 * @param pathToSound Le chemin vers le sound a charger
 * @return Mix_Chunk* contenant le son charge
 */
Mix_Chunk* loadShortSound(const char *pathToSound);

/**
 * Load un nouveau son long
 * @param pathToSound Le chemin vers le sound a charger
 * @return Mix_Music* contenant le son charge
 */
Mix_Music* loadLongSound(const char *pathToSound);

/**
 * Joue un son court
 * @param Mix_Chunk* le son a jouer
 * 
 */
void playShortSound(Mix_Chunk* toPlay);

/**
 * Joue un son court
 * @param Mix_Chunk* le son a jouer
 * 
 */
void playLongSound(Mix_Music* toPlay);

/**
 * Libere la memoire d'un son court
 * @param Mix_Chunk* le son a liberer
 * 
 */
void freeShortSound(Mix_Chunk* toFree);