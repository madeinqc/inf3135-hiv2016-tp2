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

struct MapsName {
  char** names;
  long count;
  long capacity;
};

enum Tiles {
  SAND, WATER, WATER_SW_SE, WATER_SW, GRASS, WATER_SE, DIRT, STAIRCASE_NE = 8, STAIRCASE_NW, STAIRCASE_SE, STAIRCASE_SW, TREE, ROCK, HOUSE = 16, PLAYER = 18
};

void* sdl_img_loader(const char *path);

void tp2tmx_loadRandomMap(SDL_Renderer *renderer, struct Carte *carte);
void tp2tmx_initMapValues(struct Carte *carte);
void tp2tmx_mapFree(tmx_map *map);

long tp2tmx_pseudoRandom(long max);

void tp2tmx_getAllMapsName(struct MapsName *mapsName);
void tp2tmx_freeAllMapsName(struct MapsName *mapsName);

void tp2tmx_drawLayer(SDL_Renderer *ren, struct Carte *carte, tmx_layer *layer);
SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte);

bool tp2tmx_setInitialSectionToHouse(struct Carte *carte);

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

bool tp2tmx_isNextTileWalkable(struct Sprite *sprite, struct Carte *carte);

bool tp2tmx_isTileWalkable(int x, int y, int layerNumber, enum Direction orientation, struct Carte *carte);

void tp2tmx_initHouseValues(struct Carte *carte);
void tp2tmx_initCharacterValues(struct Carte *carte);
tmx_tile* tp2tmx_getTile(int x, int y, struct Carte *carte, tmx_layer *layer);
tmx_tile *tp2tmx_getAbsoluteTile(int x, int y, struct Carte *carte, tmx_layer *layer);
void tp2tmx_setNbRocks(struct Carte *carte);
#endif