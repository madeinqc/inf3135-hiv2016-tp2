/**
 * @file
 * Description a venir... 
 *
*/
#include "tp2_animSprite.h"

bool CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, int speed, struct Application* app){
	struct Sprite *newSprite = (struct Sprite*)malloc(sizeof(struct Sprite));
	newSprite->nbRows = numRows;
	newSprite->nbColumns = numColumns;
	newSprite->nbFrames = numFrames;
	newSprite->currentFrame = initialFrame;
	newSprite->delayBetweenFrame = delayBetweenFrame;
	newSprite->texture = NULL;
	newSprite->posX = 20;
	newSprite->posY = 20;
	newSprite->speed = speed;
	SDL_Surface *surface = IMG_Load(filename);
	if (surface == NULL) {
	  printf("Unable to load image %s! SDL_image Error: %s\n",filename, IMG_GetError());
	} else {
      newSprite->texture = SDL_CreateTextureFromSurface(app->gRenderer, surface);
		if (newSprite->texture == NULL) {
		  printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
    }
    newSprite->spriteWidth = surface->w / numColumns;
    newSprite->spriteHeight = surface->h / numRows;
	}
  app->currSprite = newSprite;
  SDL_FreeSurface(surface);
	return true;
}

void DeleteSprite(struct Sprite *sprite, struct Application* app){
  free(sprite);
  app->currSprite = NULL;
}

void RenderSprite(struct Sprite *sprite, struct Application *app){
  int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
  int srcy = sprite->spriteHeight * (sprite->currentFrame / sprite->nbColumns);
  SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
  SDL_Rect dstrect = {sprite->posX, sprite->posY, sprite->spriteWidth, sprite->spriteHeight};
  SDL_RenderCopy(app->gRenderer, sprite->texture, &srcrect, &dstrect);
}

void moveSprite(struct Sprite *sprite, int direction){
	switch(direction){
		case EAST:
			sprite->posX-=sprite->speed;
			sprite->posY+=sprite->speed;
			break;
		case WEST:
			sprite->posX+=sprite->speed;
			sprite->posY-=sprite->speed;
			break;
		case SOUTH:
			sprite->posX+=sprite->speed;
			sprite->posY+=sprite->speed;
			break;
		case NORTH:
			sprite->posX-=sprite->speed;
			sprite->posY-=sprite->speed;
			break;
	}
}

void handleEventsSprite(struct Sprite *sprite, SDL_Event *event, struct Application *app){
	switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
				case SDLK_UP:
					moveSprite(sprite, NORTH);
					sprite->lastDirection = NORTH;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*NORTH);
					break;
				case SDLK_DOWN:
					moveSprite(sprite, SOUTH);
					sprite->lastDirection = SOUTH;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*SOUTH);
					break;
				case SDLK_RIGHT:
					moveSprite(sprite, WEST);
					sprite->lastDirection = WEST;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*WEST);
					break;
				case SDLK_LEFT:
					moveSprite(sprite, EAST);
					sprite->lastDirection = EAST;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*EAST);
					break;
			}
			break;
		case SDL_KEYUP:
			sprite->currentFrame = sprite->lastDirection*20;
			break;
	}
}