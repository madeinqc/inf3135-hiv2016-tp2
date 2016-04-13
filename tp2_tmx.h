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
  struct Jauge *foodJauge; 
  struct Jauge *waterJauge; 
  struct Jauge *sleepJauge; 
  bool isSpriteInitialized;
  struct Sprite *sprite;
  SDL_Texture *background;
  int nbRock;
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

bool findSectionHouse(struct Carte *carte);

void findNbRocks(struct Carte *carte);

bool isTileOK(struct Carte *carte);

bool setTileInformations(struct Carte *carte, tmx_layer *layer);

bool fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer);

bool transitionSprite(struct Carte *carte, int x, int y);

void restartFutureTile(struct Sprite *sprite);

void updateCurrentTile(struct Sprite *sprite);

bool changeSousMap(struct Carte *carte);

bool minerRoche(struct Carte *carte);

bool boireEau(struct Carte *carte);

bool reposManger(struct Carte *carte);

void setIdEnFace(struct Carte *carte, tmx_layer *layer);

bool gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer);

bool gestionEscaliersDown(int idTile, struct Carte *carte, tmx_layer *layer);

void destroyElement(tmx_layer *layer, int tileNumber);
#endif
