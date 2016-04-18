/**
 * @file
 * Fichier contenant les méthodes nécessaires au chargement des sons.
*/
#include "sdl2.h"
#include <stdbool.h>

/**
 * Ouvre le canal de son
 */
void tp2Sound_openChannel();

/**
 * Load un nouveau son court.
 * @param pathToSound Le chemin vers le son à charger.
 * @return Mix_Chunk* Contenant le son chargé.
 */
Mix_Chunk *tp2Sound_loadShort(const char *pathToSound);

/**
 * Charge un nouveau son long.
 * @param pathToSound Le chemin vers le sound a charger.
 * @return Mix_Music* Contenant le son charge.
 */
Mix_Music *tp2Sound_loadLong(const char *pathToSound);

/**
 * Joue un son court.
 * @param Mix_Chunk* Le son à jouer.
 */
void tp2Sound_playShort(Mix_Chunk *toPlay);

/**
 * Joue un son long.
 * @param Mix_Chunk* Le son a jouer.
 */
void tp2Sound_playLong(Mix_Music *toPlay);

/**
 * Libère la mémoire d'un son court.
 * @param Mix_Chunk* Le son a libérer.
 */
void tp2Sound_freeShort(Mix_Chunk *toFree);

/**
 * Libère la mémoire d'un son long.
 * @param Mix_Music* Le son a liberer.
 */
void tp2Sound_freeLong(Mix_Music *toFree);
