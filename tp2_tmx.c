/**
 * @file
 * Description a venir...
 *
 */
#include "tp2_tmx.h"

static SDL_Renderer *ren = NULL;

void tp2tmx_loadRandomMap(SDL_Renderer *renderer, struct Carte *carte) {
  ren = renderer;

	tmx_img_load_func = (void* (*)(const char*))sdl_img_loader;
	tmx_img_free_func = (void  (*)(void*))      SDL_DestroyTexture;

	struct mapsName mapsName = {NULL, 0, 0};
	tp2tmx_getAllMapsName(&mapsName);

	srandom(clock());

	char* selName = mapsName.names[pseudoRandom(mapsName.count)];

	int assetsLen = strlen(ASSETS_PATH);
	int nameLen = strlen(selName);
	char* fullPath = malloc(sizeof(char) * (nameLen + assetsLen + 1));
	strncpy(fullPath, ASSETS_PATH, assetsLen + 1);
	strncat(fullPath, selName, nameLen);

	carte->map = tmx_load(fullPath);
  if (!carte->map) {
    printf("Err: %s", tmx_strerr());
    return;
  }

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

	free(fullPath);

	tp2tmx_freeAllMapsName(&mapsName);
}

long pseudoRandom(long max) {
	return random() % max;
}

void tp2tmx_mapFree(tmx_map *map) {
	tmx_map_free(map);
}

void tp2tmx_getAllMapsName(struct mapsName *mapsName) {
	DIR *directory = opendir(ASSETS_PATH);

	mapsName->names = malloc(sizeof(char*) * INITIAL_CAPACITY);
	mapsName->count = 0;
	mapsName->capacity = INITIAL_CAPACITY;

	if (directory != NULL) {
		struct dirent *entry;

		while ((entry = readdir(directory)) != NULL) {
			if (!strcmp(entry->d_name, ".") ||
					!strcmp(entry->d_name, "..")) {
				continue;
			}

			char* ext = entry->d_name;
			ext += strlen(entry->d_name) - 4;
			if (strcmp(ext, ".tmx")) {
				continue;
			}

			if (mapsName->count >= mapsName->capacity) {
				mapsName->capacity *= 2;
				mapsName->names = realloc(mapsName->names, sizeof(char*) * mapsName->capacity);
			}

			mapsName->names[mapsName->count] = strdup(entry->d_name);

			mapsName->count++;
		}

		(void) closedir(directory);
	} else {
		/* TODO Handle error */
	}
}

void tp2tmx_freeAllMapsName(struct mapsName *mapsName) {
	long i;
	for (i = 0; i < mapsName->count; ++i) {
		free(mapsName->names[i]);
	}
	free(mapsName->names);
}

void* sdl_img_loader(const char *path) {
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
	SDL_Texture* texture;
	bool transit = false;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			transit = false;
      tileX = i + carte->xSection * 15 - 1;
      tileY = j + carte->ySection * 15 - 1;

      if (tileX == -1 || tileY == -1 ||
          tileX >= carte->map->height || tileY >= carte->map->width)
        continue; // Skip border lines as they should be blank
      if(carte->isSpriteInitialized && carte->sprite->currTile.tileY == j && carte->sprite->currTile.tileX == i){
				char layerSprite[7];
		    layerToString(carte->sprite->currentLayer, layerSprite);
		    if(strcmp(layer->name, layerSprite) == 0){
		  		renderSprite(carte->sprite, ren);
		  	}
		  }
			gid = layer->content.gids[(tileX * carte->map->width) + tileY];
			tile = carte->map->tiles[gid];
			if (tile != NULL) {
				tileset = carte->map->tiles[gid]->tileset;
				image = carte->map->tiles[gid]->image;
				srcrect.x = carte->map->tiles[gid]->ul_x;
				srcrect.y = carte->map->tiles[gid]->ul_y;
				srcrect.w = dstrect.w = image->width;
				srcrect.h = dstrect.h = image->height;
        
        halfMapWidth = carte->map->tile_width/2;
        halfMapHeight = carte->map->tile_height/2;

        dstrect.x = ((j - i) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement;
        dstrect.y = ((j + i) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64
           + ((tileset->tile_height / image->height) - 1) * 64;

        // Initialise la position initial du personnage
        if(!carte->isSpriteInitialized && carte->map->tiles[gid]->id == 16){
        	carte->sprite->lastDirection = WEST;
          carte->sprite->futureTile.tileX = i + 1;
          carte->sprite->futureTile.tileY = j;
        	carte->isSpriteInitialized = true;
          if(isTileOK(carte)){
          	updateCurrentTile(carte->sprite);
          }
        }
    		if (image) {
    			texture = (SDL_Texture*)image->resource_image;
    		}
		    SDL_RenderCopy(ren, texture, &srcrect, &dstrect);
			}
		}
	}
}

SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte) {
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

bool findSectionHouse(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head->next;
	int i;
	int j;
	unsigned int caseCourrante;
	unsigned int gid;
	printf("Height : %d, Width : %d\n",carte->map->height, carte->map->width);
	for(i = 0; i < carte->map->height; ++i){
		for(j = 0; j < carte->map->width; ++j){
			caseCourrante = (i*carte->map->width)+j;
			gid = layer->content.gids[caseCourrante];
			if(carte->map->tiles[gid] != NULL){
				if(carte->map->tiles[gid]->id == 16){
					printf("i : %d, j : %d, Case : %d\n", i, j, caseCourrante);
					carte->xSection = (i-1)/15;
					carte->ySection = (j-1)/15;
					//layer->content.gids[caseCourrante-carte->map->width] = 3;
					//layer->content.gids[caseCourrante-(carte->map->width*2)] = 3;
					break;
				}
			}
		}
	}
}

void findNbRocks(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head->next;
	int i;
	int j;
	unsigned int caseCourrante;
	unsigned int gid;
	int nbRocks = 0;
	while(layer){
		for(i = 0; i < carte->map->height; ++i){
			for(j = 0; j < carte->map->width; ++j){
				caseCourrante = (i*carte->map->width)+j;
				gid = layer->content.gids[caseCourrante];
				if(carte->map->tiles[gid] != NULL){
					if(carte->map->tiles[gid]->id == 13){
						nbRocks+=1;
					}
				}
			}
		}
		layer = layer->next;
	}
	carte->nbRock = nbRocks;
}

bool isTileOK(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head;

	// Position stays in the range of map
	if(carte->sprite->futureTile.tileX < 0 || carte->sprite->futureTile.tileY < 0 ||
		 carte->sprite->futureTile.tileX > 15 || carte->sprite->futureTile.tileY > 15){
		return false;
	}
	// Find current layer
	int i;
	for(i = 0; i < carte->sprite->currentLayer-1; i++){
		layer = layer->next;
	}
	// Sets new tile informations
	if(!setTileInformations(carte, layer)){
		return false;
	}
	int idTile = carte->sprite->futureTile.idTile;
	int idTileUp = carte->sprite->futureTile.idTilely;
	if(gestionEscaliersUp(idTileUp, carte, layer)){
		return true;
	}else if(gestionEscaliersDown(idTile, carte, layer)){
		return true;
	}
	if(idTile == 1 || idTile == 5 || idTile == 3){
		return false;
	}
	return fromPositionToCoordinates(carte, layer);
}

bool fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer){
	int halfMapWidth = carte->map->tile_width/2;
  int halfMapHeight = carte->map->tile_height/2;
  int i = carte->sprite->futureTile.tileX;
  int j = carte->sprite->futureTile.tileY;
  int gid = carte->sprite->futureTile.tileGID;
  int offset = 25; // Decalage visuel su sprite
  tmx_tile *tile;
  tile = carte->map->tiles[gid];
  if(tile == NULL){
  	return false;
  }
	tmx_tileset *tileset = carte->map->tiles[gid]->tileset;
	tmx_image *image = carte->map->tiles[carte->sprite->futureTile.tileGID]->image;
	carte->sprite->posX = ((j - i) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement;
	carte->sprite->posY = ((j + i) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64
  		+ ((tileset->tile_height / image->height) - 1) * 64 + offset;
  return true;
}

bool setTileInformations(struct Carte *carte, tmx_layer *layer){
	int newX = carte->sprite->futureTile.tileX + carte->xSection * 15 - 1;
	int newY = carte->sprite->futureTile.tileY + carte->ySection * 15 - 1;
	
	carte->sprite->futureTile.tileNumber = (newX * carte->map->width) + newY;
	if(carte->sprite->futureTile.tileNumber < 0){
		return false;
	}
	carte->sprite->futureTile.tileGID = layer->content.gids[carte->sprite->futureTile.tileNumber];
	carte->sprite->futureTile.tileGIDly = layer->next->content.gids[carte->sprite->futureTile.tileNumber];
	if(carte->sprite->futureTile.tileGID > 100 || carte->sprite->futureTile.tileGIDly > 100){
		return false;
	}
	tmx_tile *tile = carte->map->tiles[carte->sprite->futureTile.tileGID];
	tmx_tile *tileUp = carte->map->tiles[carte->sprite->futureTile.tileGIDly];
	if(tile == NULL){
		return false;
	}else if(tileUp != NULL){
		carte->sprite->futureTile.idTilely = carte->map->tiles[carte->sprite->futureTile.tileGIDly]->id;
		// Verification si ce sont des marches
		if(carte->sprite->futureTile.idTilely >= 8 && carte->sprite->futureTile.idTilely <= 11){
			return true;
		}
		return false;
	}
	carte->sprite->futureTile.idTile = carte->map->tiles[carte->sprite->futureTile.tileGID]->id;
	return true;
}

void restartFutureTile(struct Sprite *sprite){
	sprite->futureTile.tileX = sprite->currTile.tileX;
	sprite->futureTile.tileY = sprite->currTile.tileY;
	sprite->futureTile.tileNumber = sprite->currTile.tileNumber;
	sprite->futureTile.tileGID = sprite->currTile.tileGID;
	sprite->futureTile.idTile = sprite->currTile.idTile;
}

void updateCurrentTile(struct Sprite *sprite){
	sprite->currTile.tileX = sprite->futureTile.tileX;
	sprite->currTile.tileY = sprite->futureTile.tileY;
	sprite->currTile.tileNumber = sprite->futureTile.tileNumber;
	sprite->currTile.tileGID = sprite->futureTile.tileGID;
	sprite->currTile.tileGIDly = sprite->futureTile.tileGIDly;
	sprite->currTile.idTile = sprite->futureTile.idTile;
	sprite->currTile.idTilely = sprite->futureTile.idTilely;
}

bool changeSousMap(struct Carte *carte){
  int caseX = carte->sprite->futureTile.tileX;
  int caseY = carte->sprite->futureTile.tileY;
  if(caseX == 16 && carte->sprite->lastDirection == EAST){
    carte->xSection += carte->xSection == carte->maxXSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX -15;
    return true;
  }else if(caseX == -1 && carte->sprite->lastDirection == WEST){
    carte->xSection -= carte->xSection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX +15;
    return true;
  }else if(caseY == 16 && carte->sprite->lastDirection == SOUTH){
    carte->ySection += carte->ySection == carte->maxYSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY -15;
    return true;
  }else if(caseY == -1 && carte->sprite->lastDirection == NORTH){
    carte->ySection -= carte->ySection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY +15;
    return true;
  }
  return false;
}

bool minerRoche(struct Carte *carte){
	if(carte->sprite->futureTile.tileGIDly == 14){
		carte->sprite->nbRoches += 1;
		return true;
	}
	return false;
}

bool boireEau(struct Carte *carte){
	int id = carte->sprite->futureTile.tileGID;
	if(id == 2 || id == 4){
		refillJauge(carte->waterJauge);
		return true;
	}
	return false;
}

bool reposManger(struct Carte *carte){
	int id = carte->sprite->futureTile.tileGIDly;
	if(id == 17){
		refillJauge(carte->sleepJauge);
		refillJauge(carte->foodJauge);
		// In the house, victory condition is verfied 
		if(carte->nbRock == carte->sprite->nbRoches){
    	carte->allMined = true; 
  	}
		return true;
	}
	return false;
}

void setIdEnFace(struct Carte *carte, tmx_layer *layer){
	switch(carte->sprite->lastDirection){
		case EAST:
			carte->sprite->futureTile.tileX+=1;
			setTileInformations(carte, layer);
			break;
		case WEST:
			carte->sprite->futureTile.tileX-=1;
			setTileInformations(carte, layer);
			break;
		case SOUTH:
			carte->sprite->futureTile.tileY+=1;
			setTileInformations(carte, layer);
			break;
		case NORTH:
			carte->sprite->futureTile.tileY-=1;
			setTileInformations(carte, layer);
			break;
	}
}

bool actions(struct Carte *carte){
	bool toRet = false;
	tmx_layer *layer = carte->map->ly_head;
	int i;
	for(i = 0; i < carte->sprite->currentLayer-1; i++){
		layer = layer->next;
	}
	setIdEnFace(carte, layer);
	if(minerRoche(carte)){
		destroyElement(layer->next, carte->sprite->futureTile.tileNumber);
		toRet = true;
	}else if(boireEau(carte)){
		toRet = true;
	}else if(reposManger(carte)){
		toRet = true;
	}
	restartFutureTile(carte->sprite);
	return toRet;
}

bool gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer){
	switch(id){
		case 11:
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileX+=1;
			break;
		case 8: // Fonctionne
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileX-=1;
			break;
		case 9: // Fonctionne
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileY-=1;
			break;
		case 10: // Fonctionne
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileY+=1;
			break;
		default:
			return false;
			break;
	}
	setTileInformations(carte, layer);
	updateCurrentTile(carte->sprite);
	setTileInformations(carte,layer->next);
	updateCurrentTile(carte->sprite);
	fromPositionToCoordinates(carte, layer->next);
	return true;
}

bool gestionEscaliersDown(int id, struct Carte *carte, tmx_layer *layer){
	switch(id){
		case 11:
			carte->sprite->currentLayer-=1;
			carte->sprite->futureTile.tileX-=1;
			break;
		case 8:
			carte->sprite->currentLayer-=1;
			carte->sprite->futureTile.tileX+=1;
			break;
		case 9:
			carte->sprite->currentLayer-=1;
			carte->sprite->futureTile.tileY+=1;
			break;
		case 10:
			carte->sprite->currentLayer-=1;
			carte->sprite->futureTile.tileY-=1;
			break;
		default:
			return false;
			break;
	}
	layer = carte->map->ly_head;
	int i;
	for (i = 0; i < carte->sprite->currentLayer-1; ++i)
	{
		layer = layer->next;
	}
	setTileInformations(carte, layer);
	updateCurrentTile(carte->sprite);
	setTileInformations(carte,layer);
	updateCurrentTile(carte->sprite);
	fromPositionToCoordinates(carte, layer);
	return true;
}

void destroyElement(tmx_layer *layer, int tileNumber){
	layer->content.gids[tileNumber] = 0;
}
