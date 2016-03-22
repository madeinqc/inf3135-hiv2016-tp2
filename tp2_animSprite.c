/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_animSprite.h"

Sprite *CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
														int initialFrame, int delayBetweenFrame, SDL_Renderer* renderer){
	Sprite *newSprite = (Sprite*)malloc(sizeof(Sprite));
	newSprite->nbRows = numRows;
	newSprite->nbColumns = numColumns;
	newSprite->nbFrames = numFrames;
	newSprite->currentFrame = initialFrame;
	newSprite->delayBetweenFrame = delayBetweenFrame;
	newSprite->lastUpdate = -1;
	newSprite->renderer = renderer;
	newSprite->texture = NULL;
	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n",filename, IMG_GetError());
	} else {
        newSprite->texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (newSprite->texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
    }
        newSprite->spriteWidth = surface->w / numColumns;
        newSprite->spriteHeight = surface->h / numRows;
	}


	return newSprite;
}

void DeleteSprite(Sprite *sprite){

}

void RenderSprite(Sprite *sprite, int x, int y){

}