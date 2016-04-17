/**
 * @file
 * Description a venir...
 *
 */
#include "tp2_tmx.h"

static SDL_Renderer *ren = NULL;

void tp2tmx_loadRandomMap(SDL_Renderer *renderer, struct Carte *carte) {
  ren = renderer;

  tmx_img_load_func = (void *(*)(const char *)) sdl_img_loader;
  tmx_img_free_func = (void (*)(void *)) SDL_DestroyTexture;

  struct MapsName mapsName = {NULL, 0, 0};
  tp2tmx_getAllMapsName(&mapsName);

  srandom(clock());

  char *selName = mapsName.names[tp2tmx_pseudoRandom(mapsName.count)];

  int assetsLen = strlen(ASSETS_PATH);
  int nameLen = strlen(selName);
  char *fullPath = malloc(sizeof(char) * (nameLen + assetsLen + 1));
  strncpy(fullPath, ASSETS_PATH, assetsLen + 1);
  strncat(fullPath, selName, nameLen);

  carte->map = tmx_load(fullPath);
  if (!carte->map) {
    printf("Err: %s", tmx_strerr());
    return;
  }

  tp2tmx_initMapValues(carte);

  free(fullPath);

  tp2tmx_freeAllMapsName(&mapsName);
}

void tp2tmx_initMapValues(struct Carte *carte) {
  // Calculate max displacement
  tmx_layer *layer = carte->map->ly_head;
  int maxXDisplacement = 0, maxYDisplacement = 0;
  while (layer) {
    if (abs(layer->offsetx) > maxXDisplacement)
      maxXDisplacement = abs(layer->offsetx);
    if (abs(layer->offsety) > maxYDisplacement)
      maxYDisplacement = abs(layer->offsety);
    layer = layer->next;
  }
  maxYDisplacement += 1 * carte->map->tile_height; // Allow more space for higher layers

  carte->maxXDisplacement = maxXDisplacement;
  carte->maxYDisplacement = maxYDisplacement;

  // initialise the sections and max sections
  carte->xSection = 0;
  carte->ySection = 0;
  carte->maxXSection = (carte->map->height + 1) / 15;
  carte->maxYSection = (carte->map->width + 1) / 15;

  // Set allMined
  carte->allMined = false;

  // Set rocks number
  tp2tmx_setNbRocks(carte);

  // Set map initial sections to the house section
  // and save the coordinates of the house
  tp2tmx_initHouseValues(carte);

  // Detruire le personnage dans la carte et initialise le point de départ
  tp2tmx_initCharacterValues(carte);
}

void tp2tmx_initCharacterValues(struct Carte *carte) {
  carte->sprite->orientation = SOUTHWEST;

  tmx_layer *layer = carte->map->ly_head;
  if (layer == NULL) return;
  layer = layer->next; // The player can't be on the first layer
  int i;
  int j;
  unsigned int caseCourrante;
  unsigned int gid;
  printf("layer is null? %p", layer);
  while (layer) {
    for (i = 0; i < carte->map->height; ++i) {
      for (j = 0; j < carte->map->width; ++j) {
        tmx_tile *tile = tp2tmx_getAbsoluteTile(i, j, carte, layer);
        if (tile != NULL) {
          if (tile->id == PLAYER) {
            // Initialise character position
            carte->sprite->posX = i;
            carte->sprite->posY = j;
            // and map section accordingly
            carte->xSection = (i - 1) / 15;
            carte->ySection = (j - 1) / 15;

            tp2tmx_destroyElement(carte->map->ly_head->next, caseCourrante);
            return;
          }
        }
      }
    }
    layer = layer->next;
  }

  // If there is no player in the map, we start in front of the house
  carte->sprite->posX = (carte->houseX[0]);
  carte->sprite->posY = (carte->houseY[0] - 1);
  carte->xSection = (carte->sprite->posX - 1) / 15;
  carte->ySection = (carte->sprite->posX - 1) / 15;
}

long tp2tmx_pseudoRandom(long max) {
  return random() % max;
}

void tp2tmx_mapFree(tmx_map *map) {
  tmx_map_free(map);
}

void tp2tmx_getAllMapsName(struct MapsName *mapsName) {
  DIR *directory = opendir(ASSETS_PATH);

  mapsName->names = malloc(sizeof(char *) * INITIAL_CAPACITY);
  mapsName->count = 0;
  mapsName->capacity = INITIAL_CAPACITY;

  if (directory != NULL) {
    struct dirent *entry;

    while ((entry = readdir(directory)) != NULL) {
      if (!strcmp(entry->d_name, ".") ||
          !strcmp(entry->d_name, "..")) {
        continue;
      }

      char *ext = entry->d_name;
      ext += strlen(entry->d_name) - 4;
      if (strcmp(ext, ".tmx")) {
        continue;
      }

      if (mapsName->count >= mapsName->capacity) {
        mapsName->capacity *= 2;
        mapsName->names = realloc(mapsName->names, sizeof(char *) * mapsName->capacity);
      }

      mapsName->names[mapsName->count] = strdup(entry->d_name);

      mapsName->count++;
    }

    (void) closedir(directory);
  } else {
    /* TODO Handle error */
  }
}

void tp2tmx_freeAllMapsName(struct MapsName *mapsName) {
  long i;
  for (i = 0; i < mapsName->count; ++i) {
    free(mapsName->names[i]);
  }
  free(mapsName->names);
}

void *sdl_img_loader(const char *path) {
  SDL_Texture *texture = IMG_LoadTexture(ren, path);
  if (!texture) {
    printf("ERROR: Unable to load texture %s\n", path);
    return NULL;
  }
  return texture;
}

void tp2tmx_drawLayer(SDL_Renderer *ren, struct Carte *carte, tmx_layer *layer) {
  unsigned int i, j, tileX, tileY, modX, modY, halfMapWidth, halfMapHeight;
  unsigned int gid;
  tmx_tileset *tileset;
  tmx_tile *tile;
  tmx_image *image;
  SDL_Rect srcrect, dstrect;
  SDL_Texture *texture;
  for (i = 0; i < 16; i++) {
    for (j = 0; j < 16; j++) {
      if (carte->isSpriteInitialized && carte->sprite->currTile.tileY == j && carte->sprite->currTile.tileX == i) {
        char layerSprite[7];
        tp2animSprite_layerToString(carte->sprite->currentLayer, layerSprite);
        if (strcmp(layer->name, layerSprite) == 0) {
          tp2animSprite_render(carte->sprite, ren);
        }
      }

      tile = tp2tmx_getTile(i, j, carte, layer);
      if (tile == NULL) {
        continue; // Skip null tiles
      }

      tileset = tile->tileset;
      image = tile->image;
      srcrect.x = tile->ul_x;
      srcrect.y = tile->ul_y;
      srcrect.w = dstrect.w = image->width;
      srcrect.h = dstrect.h = image->height;

      halfMapWidth = carte->map->tile_width / 2;
      halfMapHeight = carte->map->tile_height / 2;

      dstrect.x =
          ((j - i) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement;
      dstrect.y = ((j + i) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64
                  + ((tileset->tile_height / image->height) - 1) * 64;

      // Initialise la position initial du personnage
      if (!carte->isSpriteInitialized && tile->id == 16) {
        carte->sprite->orientation = SOUTHWEST;
        carte->sprite->futureTile.tileX = i + 1;
        carte->sprite->futureTile.tileY = j;
        carte->isSpriteInitialized = true;
        if (tp2tmx_isTileOK(carte)) {
          tp2tmx_updateCurrentTile(carte->sprite);
        }
      }
      if (image) {
        texture = (SDL_Texture *) image->resource_image;
      }
      SDL_RenderCopy(ren, texture, &srcrect, &dstrect);
//      }
    }
  }
}

SDL_Texture *tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte) {
  SDL_Texture *res;
  tmx_layer *layer = carte->map->ly_head;
  int w, h;

  w = (carte->map->width < 16 ? carte->map->width : 16) * carte->map->tile_width;
  h = (carte->map->height < 16 ? carte->map->height : 16) * carte->map->tile_height;
  h += 1 * carte->map->tile_height; // Allow more space for higher layers

  w += carte->maxXDisplacement;
  h += carte->maxYDisplacement;
  if (!(res = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h)))
    printf("SDL create texture not working: %s", SDL_GetError());
  SDL_SetRenderTarget(ren, res);
  SDL_RenderClear(ren);
  SDL_RenderCopy(ren, carte->background, NULL, NULL);
  while (layer) {
    if (layer->visible)
      tp2tmx_drawLayer(ren, carte, layer);
    layer = layer->next;
  }
  SDL_SetRenderTarget(ren, NULL);
  return res;
}

void tp2tmx_initHouseValues(struct Carte *carte) {
  tmx_layer *layer = carte->map->ly_head->next;
  int i;
  int j;
  unsigned int caseCourrante;
  unsigned int gid;
  for (i = 0; i < carte->map->height; ++i) {
    for (j = 0; j < carte->map->width; ++j) {
      caseCourrante = (i * carte->map->width) + j;
      gid = layer->content.gids[caseCourrante];
      if (carte->map->tiles[gid] != NULL) {
        if (carte->map->tiles[gid]->id == 16) {
          carte->houseX[0] = i;
          carte->houseY[0] = j;
          carte->houseX[1] = i + 1;
          carte->houseY[1] = j;
          carte->houseX[2] = i;
          carte->houseY[2] = j + 1;
          carte->houseX[3] = i + 1;
          carte->houseY[3] = j + 1;
          return;
        }
      }
    }
  }
}

void tp2tmx_setNbRocks(struct Carte *carte) {
  tmx_layer *layer = carte->map->ly_head->next;
  int i;
  int j;
  unsigned int caseCourrante;
  unsigned int gid;
  int nbRocks = 0;
  while (layer) {
    for (i = 0; i < carte->map->height; ++i) {
      for (j = 0; j < carte->map->width; ++j) {
        caseCourrante = (i * carte->map->width) + j;
        gid = layer->content.gids[caseCourrante];
        if (carte->map->tiles[gid] != NULL) {
          if (carte->map->tiles[gid]->id == 13) {
            nbRocks += 1;
          }
        }
      }
    }
    layer = layer->next;
  }
  carte->nbRock = nbRocks;
}

bool tp2tmx_isNextTileWalkable(struct Sprite *sprite, struct Carte *carte) {
  return tp2tmx_isTileWalkable(sprite->posX, sprite->posY, sprite->currentLayer, sprite->direction, carte);

//  if (tp2tmx_gestionEscaliersUp(idTileUp, carte, layer)) {
//    return true;
//  } else if (tp2tmx_gestionEscaliersDown(idTile, carte, layer)) {
//    return true;
//  }
//  if (idTile == 1 || idTile == 5 || idTile == 3) {
//    return false;
//  }
//  return tp2tmx_fromPositionToCoordinates(carte, layer);
}


bool tp2tmx_isTileWalkable(int x, int y, int layerNumber, enum Direction orientation, struct Carte *carte) {
  // Calculate future position
  int newX = x - (orientation == NORTHWEST ? 1 : 0) + (orientation == SOUTHEAST ? 1 : 0);
  int newY = y - (orientation == NORTHEAST ? 1 : 0) + (orientation == SOUTHWEST ? 1 : 0);

  tmx_layer *layer = carte->map->ly_head;

  // Position stays in the range of map
  if (newX < 0 || newY < 0 || newX > 15 || newY > 15) {
    return false;
  }

  // Get the current layer
  int i;
  for (i = 0; i < layerNumber - 1; i++) {
    layer = layer->next;
  }

  // Get tile of the lower layer and the tile of the same layer
  tmx_tile *tile = tp2tmx_getTile(newX, newY, carte, layer);
  tmx_tile *tileAbove = tp2tmx_getTile(newX, newY, carte, layer->next);

  enum Tiles tileAboveId = NONE;
  enum Tiles tileId = NONE;

  if (tile != NULL) {
    tileId = tile->id;
  }
  if (tileAbove != NULL) {
    tileAboveId = tileAbove->id;
  }

  // Check for unwalkable tiles around house


  switch (tileId) {
    case WATER:
    case WATER_SW_SE:
    case WATER_SW:
    case WATER_SE:
    case TREE:
    case ROCK:
    case HOUSE:
      return false;
  }

  // Check for staircases
  //// Check same direction
  //// Check if tile above staircase is free

  // Check if tile above is free
}


tmx_tile *tp2tmx_getTile(int x, int y, struct Carte *carte, tmx_layer *layer) {
  if (carte == NULL || layer == NULL) {
    return NULL;
  }

  int newX = x + carte->xSection * 15 - 1;
  int newY = y + carte->ySection * 15 - 1;

  return tp2tmx_getAbsoluteTile(newX, newY, carte, layer);
}

tmx_tile *tp2tmx_getAbsoluteTile(int x, int y, struct Carte *carte, tmx_layer *layer) {
  if (layer == NULL) {
    return NULL;
  }

  if (x < 0 || y < 0 || x > carte->map->height || y > carte->map->width) {
    return NULL;
  }

  int tileNumber = (x * carte->map->width) + y;
  if (tileNumber < 0) {
    return NULL;
  }

  int tileGID = layer->content.gids[tileNumber];

  return tmx_get_tile(carte->map, tileGID);
}

bool tp2tmx_isTileOK(struct Carte *carte) {
  tmx_layer *layer = carte->map->ly_head;

  // Position stays in the range of map
  if (carte->sprite->futureTile.tileX < 0 || carte->sprite->futureTile.tileY < 0 ||
      carte->sprite->futureTile.tileX > 15 || carte->sprite->futureTile.tileY > 15) {
    return false;
  }
  // Find current layer
  int i;
  for (i = 0; i < carte->sprite->currentLayer - 1; i++) {
    layer = layer->next;
  }
  // Sets new tile informations
  if (!tp2tmx_setTileInformations(carte, layer)) {
    return false;
  }
  int idTile = carte->sprite->futureTile.idTile;
  int idTileUp = carte->sprite->futureTile.idTilely;
  if (tp2tmx_gestionEscaliersUp(idTileUp, carte, layer)) {
    return true;
  } else if (tp2tmx_gestionEscaliersDown(idTile, carte, layer)) {
    return true;
  }
  if (idTile == 1 || idTile == 5 || idTile == 3) {
    return false;
  }
  return tp2tmx_fromPositionToCoordinates(carte, layer);
}

bool tp2tmx_fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer) {
  int halfMapWidth = carte->map->tile_width / 2;
  int halfMapHeight = carte->map->tile_height / 2;
  int i = carte->sprite->futureTile.tileX;
  int j = carte->sprite->futureTile.tileY;
  int gid = carte->sprite->futureTile.tileGID;
  int offset = 25; // Decalage visuel su sprite
  tmx_tile *tile;
  tile = carte->map->tiles[gid];
  if (tile == NULL) {
    return false;
  }
  tmx_tileset *tileset = carte->map->tiles[gid]->tileset;
  tmx_image *image = carte->map->tiles[carte->sprite->futureTile.tileGID]->image;
  carte->sprite->posX =
      ((j - i) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement;
  carte->sprite->posY = ((j + i) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64
                        + ((tileset->tile_height / image->height) - 1) * 64 + offset;
  return true;
}

bool tp2tmx_setTileInformations(struct Carte *carte, tmx_layer *layer) {
  int newX = carte->sprite->futureTile.tileX + carte->xSection * 15 - 1;
  int newY = carte->sprite->futureTile.tileY + carte->ySection * 15 - 1;

  carte->sprite->futureTile.tileNumber = (newX * carte->map->width) + newY;
  if (carte->sprite->futureTile.tileNumber < 0) {
    return false;
  }
  carte->sprite->futureTile.tileGID = layer->content.gids[carte->sprite->futureTile.tileNumber];
  carte->sprite->futureTile.tileGIDly = layer->next->content.gids[carte->sprite->futureTile.tileNumber];
  if (carte->sprite->futureTile.tileGID > 100 || carte->sprite->futureTile.tileGIDly > 100) {
    return false;
  }
  tmx_tile *tile = carte->map->tiles[carte->sprite->futureTile.tileGID];
  tmx_tile *tileUp = carte->map->tiles[carte->sprite->futureTile.tileGIDly];
  if (tile == NULL) {
    return false;
  } else if (tileUp != NULL) {
    carte->sprite->futureTile.idTilely = carte->map->tiles[carte->sprite->futureTile.tileGIDly]->id;
    // Verification si ce sont des marches
    if (carte->sprite->futureTile.idTilely >= 8 && carte->sprite->futureTile.idTilely <= 11) {
      return true;
    }
    return false;
  }
  carte->sprite->futureTile.idTile = carte->map->tiles[carte->sprite->futureTile.tileGID]->id;
  return true;
}

void tp2tmx_restartFutureTile(struct Sprite *sprite) {
  sprite->futureTile.tileX = sprite->currTile.tileX;
  sprite->futureTile.tileY = sprite->currTile.tileY;
  sprite->futureTile.tileNumber = sprite->currTile.tileNumber;
  sprite->futureTile.tileGID = sprite->currTile.tileGID;
  sprite->futureTile.idTile = sprite->currTile.idTile;
}

void tp2tmx_updateCurrentTile(struct Sprite *sprite) {
  sprite->currTile.tileX = sprite->futureTile.tileX;
  sprite->currTile.tileY = sprite->futureTile.tileY;
  sprite->currTile.tileNumber = sprite->futureTile.tileNumber;
  sprite->currTile.tileGID = sprite->futureTile.tileGID;
  sprite->currTile.tileGIDly = sprite->futureTile.tileGIDly;
  sprite->currTile.idTile = sprite->futureTile.idTile;
  sprite->currTile.idTilely = sprite->futureTile.idTilely;
}

bool tp2tmx_changeSousMap(struct Carte *carte) {
  int caseX = carte->sprite->futureTile.tileX;
  int caseY = carte->sprite->futureTile.tileY;
  if (caseX == 16 && carte->sprite->orientation == SOUTHEAST) {
    carte->xSection += carte->xSection == carte->maxXSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX - 15;
    return true;
  } else if (caseX == -1 && carte->sprite->orientation == NORTHWEST) {
    carte->xSection -= carte->xSection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX + 15;
    return true;
  } else if (caseY == 16 && carte->sprite->orientation == SOUTHWEST) {
    carte->ySection += carte->ySection == carte->maxYSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY - 15;
    return true;
  } else if (caseY == -1 && carte->sprite->orientation == NORTHEAST) {
    carte->ySection -= carte->ySection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY + 15;
    return true;
  }
  return false;
}

bool tp2tmx_minerRoche(struct Carte *carte) {
  if (carte->sprite->futureTile.tileGIDly == 14) {
    carte->sprite->nbRoches += 1;
    return true;
  }
  return false;
}

bool tp2tmx_boireEau(struct Carte *carte) {
  int id = carte->sprite->futureTile.tileGID;
  if (id == 2 || id == 4) {
    tp2jauge_refill(carte->waterJauge);
    return true;
  }
  return false;
}

bool tp2tmx_reposManger(struct Carte *carte) {
  int id = carte->sprite->futureTile.tileGIDly;
  if (id == 17) {
    tp2jauge_refill(carte->sleepJauge);
    tp2jauge_refill(carte->foodJauge);
    // In the house, victory condition is verfied
    if (carte->nbRock == carte->sprite->nbRoches) {
      carte->allMined = true;
    }
    return true;
  }
  return false;
}

void tp2tmx_setIdEnFace(struct Carte *carte, tmx_layer *layer) {
  switch (carte->sprite->orientation) {
    case SOUTHEAST:
      carte->sprite->futureTile.tileX += 1;
      tp2tmx_setTileInformations(carte, layer);
      break;
    case NORTHWEST:
      carte->sprite->futureTile.tileX -= 1;
      tp2tmx_setTileInformations(carte, layer);
      break;
    case SOUTHWEST:
      carte->sprite->futureTile.tileY += 1;
      tp2tmx_setTileInformations(carte, layer);
      break;
    case NORTHEAST:
      carte->sprite->futureTile.tileY -= 1;
      tp2tmx_setTileInformations(carte, layer);
      break;
  }
}

bool tp2tmx_actions(struct Carte *carte) {
  bool toRet = false;
  tmx_layer *layer = carte->map->ly_head;
  int i;
  for (i = 0; i < carte->sprite->currentLayer - 1; i++) {
    layer = layer->next;
  }
  tp2tmx_setIdEnFace(carte, layer);
  if (tp2tmx_minerRoche(carte)) {
    tp2tmx_destroyElement(layer->next, carte->sprite->futureTile.tileNumber);
    toRet = true;
  } else if (tp2tmx_boireEau(carte)) {
    toRet = true;
  } else if (tp2tmx_reposManger(carte)) {
    toRet = true;
  }
  tp2tmx_restartFutureTile(carte->sprite);
  return toRet;
}

bool tp2tmx_gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer) {
  switch (id) {
    case 11:
      carte->sprite->currentLayer += 1;
      carte->sprite->futureTile.tileX += 1;
      break;
    case 8: // Fonctionne
      carte->sprite->currentLayer += 1;
      carte->sprite->futureTile.tileX -= 1;
      break;
    case 9: // Fonctionne
      carte->sprite->currentLayer += 1;
      carte->sprite->futureTile.tileY -= 1;
      break;
    case 10: // Fonctionne
      carte->sprite->currentLayer += 1;
      carte->sprite->futureTile.tileY += 1;
      break;
    default:
      return false;
      break;
  }
  tp2tmx_setTileInformations(carte, layer);
  tp2tmx_updateCurrentTile(carte->sprite);
  tp2tmx_setTileInformations(carte, layer->next);
  tp2tmx_updateCurrentTile(carte->sprite);
  tp2tmx_fromPositionToCoordinates(carte, layer->next);
  return true;
}

bool tp2tmx_gestionEscaliersDown(int id, struct Carte *carte, tmx_layer *layer) {
  switch (id) {
    case 11:
      carte->sprite->currentLayer -= 1;
      carte->sprite->futureTile.tileX -= 1;
      break;
    case 8:
      carte->sprite->currentLayer -= 1;
      carte->sprite->futureTile.tileX += 1;
      break;
    case 9:
      carte->sprite->currentLayer -= 1;
      carte->sprite->futureTile.tileY += 1;
      break;
    case 10:
      carte->sprite->currentLayer -= 1;
      carte->sprite->futureTile.tileY -= 1;
      break;
    default:
      return false;
      break;
  }
  layer = carte->map->ly_head;
  int i;
  for (i = 0; i < carte->sprite->currentLayer - 1; ++i) {
    layer = layer->next;
  }
  tp2tmx_setTileInformations(carte, layer);
  tp2tmx_updateCurrentTile(carte->sprite);
  tp2tmx_setTileInformations(carte, layer);
  tp2tmx_updateCurrentTile(carte->sprite);
  tp2tmx_fromPositionToCoordinates(carte, layer);
  return true;
}

void tp2tmx_destroyElement(tmx_layer *layer, int tileNumber) {
  layer->content.gids[tileNumber] = 0;
}
