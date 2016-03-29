/**
 * @file
 * Description a venir... 
 *
*/
#include "tp2_animSprite.h"

/**
 * Creation du sprite anime
 */
bool CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, struct Application* app){
	struct Sprite *newSprite = (struct Sprite*)malloc(sizeof(struct Sprite));
	newSprite->nbRows = numRows;
	newSprite->nbColumns = numColumns;
	newSprite->nbFrames = numFrames;
	newSprite->currentFrame = initialFrame;
	newSprite->delayBetweenFrame = delayBetweenFrame;
	newSprite->lastUpdate = -1;
	newSprite->renderer = app->renderer;
	newSprite->texture = NULL;
	newSprite->posX = 20;
	newSprite->posY = 20;
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
  app->currSprite = newSprite;
  SDL_FreeSurface(surface);
	return true;
}

/**
 * Libere les ressources du sprite
 */
void DeleteSprite(struct Sprite *sprite, struct Application* app){
  free(sprite);
  app->currSprite = NULL;
}

/*
 * Ajoute le sprite a render dans le renderer
 */
void RenderSprite(struct Sprite *sprite){
	if (sprite->lastUpdate == -1) {
    sprite->lastUpdate = SDL_GetTicks();
  }
  int elapsed = SDL_GetTicks() - sprite->lastUpdate;
  if (elapsed > sprite->delayBetweenFrame) {
    int f = elapsed / sprite->delayBetweenFrame;
    sprite->currentFrame = ((sprite->currentFrame + f) % sprite->nbFrames)+(20*(sprite->lastDirection));
    sprite->lastUpdate += elapsed;
  }
  int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
  int srcy = sprite->spriteHeight * (sprite->currentFrame / sprite->nbColumns);
  SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
  SDL_Rect dstrect = {sprite->posX, sprite->posY, sprite->spriteWidth, sprite->spriteHeight};
	SDL_RenderCopy(sprite->renderer, sprite->texture, &srcrect, &dstrect);
}

void moveSprite(struct Sprite *sprite, int direction){
	int movement = 2;
	switch(direction){
		case EAST:
			sprite->posX-=movement;
			sprite->posY+=movement;
			break;
		case WEST:
			sprite->posX+=movement;
			sprite->posY-=movement;
			break;
		case SOUTH:
			sprite->posX+=movement;
			sprite->posY+=movement;
			break;
		case NORTH:
			sprite->posX-=movement;
			sprite->posY-=movement;
			break;
	}
}

void handleEventsSprite(struct Sprite *sprite, SDL_Event *event, struct Application *app){
	while(event->type == SDL_KEYDOWN){
		switch(event->key.keysym.sym){
			case SDLK_UP:
				moveSprite(sprite, NORTH);
				sprite->lastDirection = NORTH;
				break;
			case SDLK_DOWN:
				moveSprite(sprite, SOUTH);
				sprite->lastDirection = SOUTH;
				break;
			case SDLK_RIGHT:
				moveSprite(sprite, WEST);
				sprite->lastDirection = WEST;
				break;
			case SDLK_LEFT:
				moveSprite(sprite, EAST);
				sprite->lastDirection = EAST;
				break;
		}
		RenderSprite(sprite);
    SDL_RenderPresent(app->renderer);
		SDL_PollEvent(event);
		SDL_Delay(16);
	}
}