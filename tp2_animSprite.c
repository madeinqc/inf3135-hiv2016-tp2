/**
 * @file
 * Fichier permettant de gérer le personnage principal.
*/
#include "tp2_animSprite.h"

bool tp2animSprite_create(const char* filename, int numRows, int numColumns, int numFrames,
		int initialFrame, int delayBetweenFrame, int speed, struct Application* app){

	struct Sprite *newSprite = (struct Sprite*)malloc(sizeof(struct Sprite));

	// Image informations et frames
	newSprite->nbRows = numRows;
	newSprite->nbColumns = numColumns;
	newSprite->nbFrames = numFrames;
	newSprite->currentFrame = initialFrame;
	newSprite->delayBetweenFrame = delayBetweenFrame;

	// Position
	newSprite->futureTile.tileX = 10;
	newSprite->futureTile.tileY = 10;
	newSprite->speed = speed;
	newSprite->currentLayer = 1;
	newSprite->nbRoches = 0;
	newSprite->show = true;
    newSprite->xOffset = 0;
    newSprite->yOffset = 0;
    newSprite->lastDirection = EAST;

	// Load Image
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

void tp2animSprite_delete(struct Sprite *sprite, struct Application* app){
  free(sprite);
  app->currSprite = NULL;
}

void tp2animSprite_render(struct Carte *carte, struct Sprite *sprite, SDL_Renderer *ren) {
  if (sprite->isAnimating) {
    if (sprite->currentFrame % 20 == 19) {
      sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*sprite->lastDirection);
      sprite->isAnimating = false;
      tp2tmx_updateCurrentTile(sprite);
      sprite->xOffset = 0;
      sprite->yOffset = 0;
      printf("\n");
    } else {
      sprite->currentFrame++;
      tp2animSprite_updateOffsets(carte, sprite);
    }
  }

  int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
  int srcy = sprite->spriteHeight * (sprite->currentFrame / sprite->nbColumns);
  SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
  SDL_Rect dstrect = {sprite->posX + sprite->xOffset, sprite->posY + sprite->yOffset, sprite->spriteWidth, sprite->spriteHeight};
  SDL_RenderCopy(ren, sprite->texture, &srcrect, &dstrect);
}

void tp2animSprite_updateOffsets(struct Carte *carte, struct Sprite *sprite) {
  sprite->xOffset = carte->map->tile_width / 2 - (sprite->currentFrame % sprite->nbColumns * (carte->map->tile_width / 2) / sprite->nbColumns);
  sprite->yOffset = carte->map->tile_height / 2 - (sprite->currentFrame % sprite->nbColumns * (carte->map->tile_height / 2) / sprite->nbColumns);

  switch (sprite->lastDirection) {
    case EAST:
      sprite->xOffset *= 1;
      sprite->yOffset *= -1;
      break;
    case SOUTH:
      sprite->xOffset *= -1;
      sprite->yOffset *= -1;
      break;
    case WEST:
      sprite->xOffset *= -1;
      sprite->yOffset *= 1;
      break;
    case NORTH:
      sprite->xOffset *= 1;
      sprite->yOffset *= 1;
    default:
      break;
  }

  printf("%d, %d\n", sprite->xOffset, sprite->yOffset);
  //sprite->xOffset = 0;
  //sprite->yOffset = 0;
}

void tp2animSprite_move(struct Sprite *sprite, int direction, struct Carte *carte) {
  switch (direction) {
    case EAST:
      sprite->futureTile.tileX += 1;
      break;
    case WEST:
      sprite->futureTile.tileX -= 1;
      break;
    case SOUTH:
      sprite->futureTile.tileY += 1;
      break;
    case NORTH:
      sprite->futureTile.tileY -= 1;
      break;
  }
  // Vérifie si la nouvelle case est valide
  if (!tp2tmx_changeSousMap(carte)) {
    if (tp2tmx_isTileOK(carte)) {
      // Start animation
      sprite->isAnimating = true;
    } else {
      tp2tmx_restartFutureTile(sprite);
    }
  } else {
    if (tp2tmx_isTileOK(carte)) {
      tp2tmx_updateCurrentTile(sprite);
    } else {
      tp2tmx_restartFutureTile(sprite);
    }
  }
}

bool tp2animSprite_handleEvents(struct Sprite *sprite, SDL_Event *event, struct Application *app, struct Carte *carte){
  if (sprite->isAnimating) {
    return false;
  }

	bool isConsumed = false;
	if(!carte->sprite->show){
		return false;
	}
	switch(event->type){
		case SDL_KEYDOWN:
			switch(event->key.keysym.sym){
				case SDLK_UP:
					tp2animSprite_move(sprite, NORTH, carte);
					sprite->lastDirection = NORTH;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*NORTH);
					isConsumed = true;
					break;
				case SDLK_DOWN:
					tp2animSprite_move(sprite, SOUTH, carte);
					sprite->lastDirection = SOUTH;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*SOUTH);
					isConsumed = true;
					break;
				case SDLK_RIGHT:
					tp2animSprite_move(sprite, WEST, carte);
					sprite->lastDirection = WEST;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*WEST);
					isConsumed = true;
					break;
				case SDLK_LEFT:
					tp2animSprite_move(sprite, EAST, carte);
					sprite->lastDirection = EAST;
					sprite->currentFrame = ((sprite->currentFrame+1)%(sprite->nbFrames))+(20*EAST);
					isConsumed = true;
					break;
			}
			break;
		case SDL_KEYUP:
			sprite->currentFrame = sprite->lastDirection*20;
			isConsumed = true;
			break;
	}
	return isConsumed;
}

void tp2animSprite_layerToString(int layer, char* string){
	switch(layer){
		case 0:
			strcpy(string,"Level0");
			break;
		case 1:
			strcpy(string,"Level1");
			break;
		case 2:
			strcpy(string,"Level2");
			break;
		case 3:
			strcpy(string,"Level3");
			break;
		default:
			break;
	}
}