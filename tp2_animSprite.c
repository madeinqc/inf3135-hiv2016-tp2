/**
 * @file
 * Description a venir... 
 *
*/
#include "tp2_animSprite.h"

bool tp2animSprite_create(const char *filename, int numRows, int numColumns,
                          int initialFrame, int delayBetweenFrame, struct Application *app) {

  struct Sprite *newSprite = (struct Sprite *) malloc(sizeof(struct Sprite));

  // Image informations et frames
  newSprite->nbRows = numRows;
  newSprite->nbColumns = numColumns;
  newSprite->currentFrame = initialFrame;
  newSprite->delayBetweenFrame = delayBetweenFrame;

  // Position
  newSprite->posX = 10;
  newSprite->posY = 10;
  newSprite->orientation = SOUTHWEST;
  newSprite->nextDirection = NONE;
  newSprite->currentLayer = 1;

  // Rendering offsets
  newSprite->xOffset = 0;
  newSprite->yOffset = 0;

  // Animation
  newSprite->walkingToward = NONE;
  newSprite->lastFrameTime = -1;

  // Roches minées
  newSprite->nbRoches = 0;

  // Load Image
  SDL_Surface *surface = IMG_Load(filename);
  if (surface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", filename, IMG_GetError());
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

void tp2animSprite_delete(struct Sprite *sprite, struct Application *app) {
  free(sprite);
  app->currSprite = NULL;
}

void tp2animSprite_render(struct Carte *carte, struct Sprite *sprite, SDL_Renderer *ren) {
  // Update sprite movement
  tp2animSprite_move(sprite, carte);

  int srcx = sprite->spriteWidth * (sprite->currentFrame % sprite->nbColumns);
  int srcy = sprite->spriteHeight * (sprite->currentFrame / sprite->nbColumns);

  tmx_layer *layer = tp2tmx_getCurrentLayer(carte)->next;

  srcx = sprite->spriteWidth * sprite->currentFrame;
  srcy = sprite->spriteHeight * (sprite->orientation - 1);
  SDL_Rect srcrect = {srcx, srcy, sprite->spriteWidth, sprite->spriteHeight};
  SDL_Rect dstrect = {0, 0, sprite->spriteWidth, sprite->spriteHeight};

  unsigned int halfMapWidth = carte->map->tile_width / 2;
  unsigned int halfMapHeight = carte->map->tile_height / 2;

  unsigned int x = sprite->posX + 2 - carte->xSection * 15;
  unsigned int y = sprite->posY + 2 - carte->ySection * 15;

  dstrect.x = ((y - x) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement + sprite->xOffset;
  dstrect.y = ((y + x) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64 + sprite->yOffset;

//  SDL_Rect dstrect = {sprite->posX, sprite->posY, sprite->spriteWidth, sprite->spriteHeight};
  SDL_RenderCopy(ren, sprite->texture, &srcrect, &dstrect);
}

void tp2animSprite_move(struct Sprite *sprite, struct Carte *carte) {
  if (sprite->walkingToward != NONE) {
    // Update the animation
    if (sprite->lastFrameTime == -1) {
      sprite->lastFrameTime = SDL_GetTicks();
    }

    if (sprite->lastFrameTime + sprite->delayBetweenFrame <= SDL_GetTicks()) {
      sprite->currentFrame = (sprite->currentFrame + 1) % sprite->nbColumns;

      // if done walking, update the animation state (offsets, walkingToward, the position, should change submap)
      if (sprite->currentFrame % sprite->nbColumns == 0) {
        sprite->walkingToward = NONE;
        int newX, newY;
        tp2tmx_getNextPosition(sprite->posX, sprite->posY, &newX, &newY, sprite->orientation);
        sprite->posX = newX;
        sprite->posY = newY;
        sprite->xOffset = 0;
        sprite->yOffset = 0;
      }
    }

    tp2animSprite_updateOffsets(sprite, carte);

  } else if (sprite->nextDirection != NONE) {
    sprite->orientation = sprite->nextDirection;

    if (tp2tmx_isNextTileWalkable(sprite, carte)) {
      // Start walking animation
      sprite->lastFrameTime = SDL_GetTicks();
      sprite->currentFrame = 0;
      sprite->walkingToward = sprite->nextDirection;
    }
  }

  tp2tmx_changeSousMap(carte);
}

void tp2animSprite_updateOffsets(struct Sprite *sprite, struct Carte *carte) {
  sprite->xOffset = sprite->currentFrame * (carte->map->tile_width / 2) / sprite->nbColumns;
  sprite->yOffset = sprite->currentFrame * (carte->map->tile_height / 2) / sprite->nbColumns;

  switch (sprite->orientation) {
    case NORTHEAST:
      sprite->yOffset *= -1;
      break;
    case NORTHWEST:
      sprite->xOffset *= -1;
      sprite->yOffset *= -1;
      break;
    case SOUTHWEST:;
      sprite->xOffset *= -1;
      break;
    default:
      break;
  }
}

bool tp2animSprite_handleEvents(struct Sprite *sprite, SDL_Event *event, struct Application *app, struct Carte *carte) {
  bool isConsumed = false;

  switch (event->type) {
    case SDL_KEYDOWN:
      switch (event->key.keysym.sym) {
        case SDLK_w:
          sprite->nextDirection = NORTHEAST;
          isConsumed = true;
          break;
        case SDLK_a:
          sprite->nextDirection = SOUTHWEST;
          isConsumed = true;
          break;
        case SDLK_q:
          sprite->nextDirection = NORTHWEST;
          isConsumed = true;
          break;
        case SDLK_s:
          sprite->nextDirection = SOUTHEAST;
          isConsumed = true;
          break;
      }
      break;
    case SDL_KEYUP:
      isConsumed = true;
      switch (event->key.keysym.sym) {
        case SDLK_w:
          if (sprite->nextDirection == NORTHEAST) {
            sprite->nextDirection = NONE;
          }
          break;
        case SDLK_a:
          if (sprite->nextDirection == SOUTHWEST) {
            sprite->nextDirection = NONE;
          }
          break;
        case SDLK_q:
          if (sprite->nextDirection == NORTHWEST) {
            sprite->nextDirection = NONE;
          }
          break;
        case SDLK_s:
          if (sprite->nextDirection == SOUTHEAST) {
            sprite->nextDirection = NONE;
          }
          break;
        default:
          isConsumed = false;
          break;
      }
  }

  return isConsumed;
}

void tp2animSprite_layerToString(int layer, char *string) {
  switch (layer) {
    case 0:
      strcpy(string, "Level0");
      break;
    case 1:
      strcpy(string, "Level1");
      break;
    case 2:
      strcpy(string, "Level2");
      break;
    case 3:
      strcpy(string, "Level3");
      break;
    default:
      break;
  }
}