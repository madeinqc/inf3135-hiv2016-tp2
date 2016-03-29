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

#define INITIAL_CAPACITY 8
#define ASSETS_PATH "./assets/"

struct mapsName {
  char** names;
  long count;
  long capacity;
};

void* sdl_img_loader(const char *path);

tmx_map* tp2tmx_loadRandomMap(SDL_Renderer *renderer);
void tp2tmx_mapFree(tmx_map *map);

long pseudoRandom(long max);

void tp2tmx_getAllMapsName(struct mapsName *mapsName);
void tp2tmx_freeAllMapsName(struct mapsName *mapsName);

void tp2tmx_drawLayer(SDL_Renderer *ren, tmx_map *map, tmx_layer *layer, int sectionX, int sectionY, int displacementX, int displacementY);
SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, tmx_map *map, int xSection, int ySection);

#endif
