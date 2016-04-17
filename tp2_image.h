#ifndef TP2_IMAGE_H
#define TP2_IMAGE_H

#include "sdl2.h"
#include "tp2_window.h"

/**
 * Charge une image dans un SDL_Texture.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param	imagePath Le chemin vers l'image à charger.
 * @return SDL_Surface contenant l'image ou NULL.
 */
SDL_Texture* tp2image_load(struct Application *app, char *imagePath);

#endif
