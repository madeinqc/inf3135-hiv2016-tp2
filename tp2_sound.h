/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>

/**
 * Ouvre le canal de son
 */
void tp2Sound_openChannel();

/**
 * Load un nouveau son court
 * @param pathToSound Le chemin vers le sound a charger
 * @return Mix_Chunk* contenant le son charge
 */
Mix_Chunk* tp2Sound_loadShort(const char *pathToSound);

/**
 * Load un nouveau son long
 * @param pathToSound Le chemin vers le sound a charger
 * @return Mix_Music* contenant le son charge
 */
Mix_Music* tp2Sound_loadLong(const char *pathToSound);

/**
 * Joue un son court
 * @param Mix_Chunk* le son a jouer
 * 
 */
void tp2Sound_playShort(Mix_Chunk* toPlay);

/**
 * Joue un son court
 * @param Mix_Chunk* le son a jouer
 * 
 */
void tp2Sound_playLong(Mix_Music* toPlay);

/**
 * Libere la memoire d'un son court
 * @param Mix_Chunk* le son a liberer
 * 
 */
void tp2Sound_freeShort(Mix_Chunk* toFree);

/**
 * Libere la memoire d'un son long
 * @param Mix_Music* le son a liberer
 * 
 */
void tp2Sound_freeLong(Mix_Music* toFree);
