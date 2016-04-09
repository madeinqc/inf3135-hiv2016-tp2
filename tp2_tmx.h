/**
 * @file
 * Description a venir...
 *
 */

#ifndef TP2_TMX_H
#define TP2_TMX_H

#include <tmx.h>
#include <dirent.h>
#include <time.h>
#include <stdbool.h>
#include "sdl2.h"
#include "tp2_carte.h"
#include "tp2_animSprite.h"

#define INITIAL_CAPACITY 8
#define ASSETS_PATH "./assets/"

struct Carte {
  tmx_map *map;
  Mix_Chunk* pickaxeSound;
  int xSection;
  int ySection;
  int maxXSection;
  int maxYSection;
  int maxXDisplacement;
  int maxYDisplacement;
  struct Scene *pause;
  struct Pause *sPause; 
  bool isSpriteInitialized;
  struct Sprite *sprite;
};

struct mapsName {
  char** names;
  long count;
  long capacity;
};

void* sdl_img_loader(const char *path);

void tp2tmx_loadRandomMap(SDL_Renderer *renderer, struct Carte *carte);
void tp2tmx_mapFree(tmx_map *map);

long pseudoRandom(long max);

void tp2tmx_getAllMapsName(struct mapsName *mapsName);
void tp2tmx_freeAllMapsName(struct mapsName *mapsName);

void tp2tmx_drawLayer(SDL_Renderer *ren, struct Carte *carte, tmx_layer *layer);
SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte);

bool isWallOK(struct Sprite *sprite);
#endif
