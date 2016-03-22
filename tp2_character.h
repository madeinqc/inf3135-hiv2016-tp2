/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_CHARACTER_H
#define TP2_CHARACTER_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"


/*
	Image du personnage principal
*/
#define IMG_PERSO "assets/character.png"

/*
	Structure de la sprite
*/
struct{
	int nbColumns;
	int nbRows;
	int nbFrames;
	int spriteWidth;
	int spriteHeight;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
}Sprite;



#endif