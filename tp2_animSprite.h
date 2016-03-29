/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_ANIMSPRITE_H
#define TP2_ANIMSPRITE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_image.h"
#include "tp2_window.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_sound.h"



/*
	Image du personnage principal
*/
#define IMG_PERSO "assets/walking.png"
/*
	Enumeration des directions
*/
enum Direction{EAST,SOUTH,WEST,NORTH};
/*
	Structure de la sprite
*/
struct Sprite{
	int nbColumns;
	int nbRows;
	int nbFrames;
	int spriteWidth;
	int spriteHeight;
	int currentFrame;
	int delayBetweenFrame;
	int lastUpdate;
	int posX;
	int posY;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

/*
	Creer un spritesheet
*/
bool CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, struct Application* app);

void DeleteSprite(struct Sprite *sprite, struct Application* app);

void RenderSprite(struct Sprite *sprite, int direction);
#endif