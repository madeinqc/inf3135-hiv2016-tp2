/**
 * @file
 * Description a venir...
 *
 */

#ifndef TP2_TMX_H
#define TP2_TMX_H

#include <dirent.h>
#include <time.h>
#include "tp2_animSprite.h"
#include "tp2_structCarte.h"

#define INITIAL_CAPACITY 8
#define ASSETS_PATH "./assets/"

struct Carte {
  tmx_map *map;
  Mix_Chunk* pickaxeSound;
  Mix_Chunk* snoringSound;
  Mix_Chunk* drinkSound;
  Mix_Music* gameMusic;
  int xSection;
  int ySection;
  int maxXSection;
  int maxYSection;
  int maxXDisplacement;
  int maxYDisplacement;
  struct Scene *pause;
  struct Pause *sPause; 
  struct Scene *defaite;
  struct Defaite *sDefaite; 
  struct Scene *victoire;
  struct Victoire *sVictoire; 
  bool allMined; 
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
void tp2tmx_initMapValues(struct Carte *carte);
void tp2tmx_mapFree(tmx_map *map);

long tp2tmx_pseudoRandom(long max);

void tp2tmx_getAllMapsName(struct mapsName *mapsName);
void tp2tmx_freeAllMapsName(struct mapsName *mapsName);

void tp2tmx_drawLayer(SDL_Renderer *ren, struct Carte *carte, tmx_layer *layer);
SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte);

bool tp2tmx_findSectionHouse(struct Carte *carte);

void tp2tmx_findNbRocks(struct Carte *carte);

bool tp2tmx_isTileOK(struct Carte *carte);

bool tp2tmx_setTileInformations(struct Carte *carte, tmx_layer *layer);

bool tp2tmx_fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer);

bool tp2tmx_transitionSprite(struct Carte *carte, int x, int y);

void tp2tmx_restartFutureTile(struct Sprite *sprite);

void tp2tmx_updateCurrentTile(struct Sprite *sprite);

bool tp2tmx_changeSousMap(struct Carte *carte);

bool tp2tmx_minerRoche(struct Carte *carte);

bool tp2tmx_boireEau(struct Carte *carte);

bool tp2tmx_reposManger(struct Carte *carte);

void tp2tmx_setIdEnFace(struct Carte *carte, tmx_layer *layer);

bool tp2tmx_gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer);

bool tp2tmx_gestionEscaliersDown(int idTile, struct Carte *carte, tmx_layer *layer);

void tp2tmx_destroyElement(tmx_layer *layer, int tileNumber);

bool tp2tmx_actions(struct Carte *carte);
#endif
