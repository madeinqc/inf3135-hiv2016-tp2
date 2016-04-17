/**
 * @file
 * Description a venir... 
 *
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

void tp2animSprite_render(struct Sprite *sprite, SDL_Renderer *ren){
  int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
  int srcy = sprite->spriteHeight * (sprite->currentFrame / sprite->nbColumns);
  SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
  SDL_Rect dstrect = {sprite->posX, sprite->posY, sprite->spriteWidth, sprite->spriteHeight};
  SDL_RenderCopy(ren, sprite->texture, &srcrect, &dstrect);
}

void tp2animSprite_move(struct Sprite *sprite, struct Carte *carte){
  if (tp2tmx_isNextTileWalkable(sprite, carte)) {
    switch (sprite->direction) {
      case SOUTHEAST:
        sprite->futureTile.tileX += 1;
        break;
      case NORTHWEST:
        sprite->futureTile.tileX -= 1;
        break;
      case SOUTHWEST:
        sprite->futureTile.tileY -= 1;
        break;
      case NORTHEAST:
        sprite->futureTile.tileY += 1;
        break;
    }
  }
	tp2tmx_changeSousMap(carte);
  // TODO check this ???
//	if(tp2tmx_isTileOK(carte)){
//		tp2tmx_updateCurrentTile(sprite);
//	}else{
//		tp2tmx_restartFutureTile(sprite);
//	}
}

bool tp2animSprite_handleEvents(struct Sprite *sprite, SDL_Event *event, struct Application *app, struct Carte *carte){
	bool isConsumed = false;

  if (sprite->direction == NONE) {
    switch (event->type) {
      case SDL_KEYDOWN:
        switch (event->key.keysym.sym) {
          case SDLK_w:
            sprite->direction = NORTHEAST;
//            sprite->currentFrame = ((sprite->currentFrame + 1) % (sprite->nbFrames)) + (20 * NORTHEAST);
            isConsumed = true;
            break;
          case SDLK_a:
            sprite->direction = SOUTHWEST;
            isConsumed = true;
            break;
          case SDLK_q:
            sprite->direction = NORTHWEST;
            isConsumed = true;
            break;
          case SDLK_s:
            sprite->direction = SOUTHEAST;
            isConsumed = true;
            break;
        }
        break;
    }
  }

  if (sprite->direction != NONE) {
    tp2animSprite_move(sprite, carte);
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