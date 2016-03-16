/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>
#include "tp2_window.h"

/**
 * Image du menu principal
 */
#define IMAGE_MENU "assets/imagesAccueil/PlayEasy.png"

/**
 * Charge les ressources graphiques en mémoire.
 * @param application Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool loadMedia(struct Application *application);

/**
 * Charge une image dans un SDL_Surface.
 * @params application Un pointeur vers la structure Application à utiliser.
 * @return SDL_Surface contenant l'image ou NULL.
 */
SDL_Surface* loadImage(struct Application *application);