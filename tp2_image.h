#ifndef TP2_IMAGE_H
#define TP2_IMAGE_H

#include "sdl2.h"
#include "tp2_window.h"

/**
 * Charge une image dans un SDL_Surface.
 * @params application Un pointeur vers la structure Application à utiliser.
 * @return SDL_Surface contenant l'image ou NULL.
 */
SDL_Surface* tp2image_load(struct Application *application, char *imagePath);

#endif
