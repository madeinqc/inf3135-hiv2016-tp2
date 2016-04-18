/**
 * @file
 * Structure de la carte.
 */
#ifndef TP2_STRUCTCARTE_H
#define TP2_STRUCTCARTE_H

#include <stdbool.h>
#include <tmx.h>
#include "sdl2.h"

/**
 * Structure carte contenant les différentes informations relatives au jeu. 
 */
struct Carte {
  tmx_map *map;
  Mix_Chunk *pickaxeSound;
  Mix_Chunk *snoringSound;
  Mix_Chunk *drinkSound;
  Mix_Music *gameMusic;
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

#endif