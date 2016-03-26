/**
 * @file
 * Description a venir... 
 *
*/
#include "tp2_animSprite.h"

Sprite *CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, struct Application* app){
	Sprite *newSprite = (Sprite*)malloc(sizeof(Sprite));
	newSprite->nbRows = numRows;
	newSprite->nbColumns = numColumns;
	newSprite->nbFrames = numFrames;
	newSprite->currentFrame = initialFrame;
	newSprite->delayBetweenFrame = delayBetweenFrame;
	newSprite->lastUpdate = -1;
	newSprite->renderer = app->renderer;
	newSprite->texture = NULL;
	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
	  printf("Unable to load image %s! SDL_image Error: %s\n",filename, IMG_GetError());
	} else {
      newSprite->texture = SDL_CreateTextureFromSurface(app->renderer, surface);
		if (newSprite->texture == NULL) {
		  printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
    }
    newSprite->spriteWidth = surface->w / numColumns;
    newSprite->spriteHeight = surface->h / numRows;
	}
	app->renderer = SDL_CreateRenderer(app->gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (app->renderer == NULL){
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    return false;
  }
  SDL_SetRenderDrawColor(app->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	return newSprite;
}

void DeleteSprite(Sprite *sprite){
  free(sprite);
}

void RenderSprite(Sprite *sprite, int x, int y){
	if (sprite->lastUpdate == -1){
		sprite->lastUpdate == SDL_GetTicks();
	}
	int elapsed = SDL_GetTicks() - sprite->lastUpdate;
	if (elapsed > sprite->delayBetweenFrame){
		int f = elapsed / sprite->delayBetweenFrame;
		sprite->currentFrame = (sprite->currentFrame + f) & sprite->nbFrames;
		sprite->lastUpdate += elapsed;
	}
	int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
	int srcy = sprite->spriteHeight * (sprite->nbFrames / sprite->nbColumns);
	SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
	SDL_Rect dstrect = {x, y, sprite->spriteWidth, sprite->spriteHeight};
	SDL_RenderCopy(sprite->renderer, sprite->texture, &srcrect, &dstrect);
}