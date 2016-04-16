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

	char* selName = mapsName.names[tp2tmx_pseudoRandom(mapsName.count)];

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

  tp2tmx_initMapValues(carte);

	free(fullPath);

	tp2tmx_freeAllMapsName(&mapsName);
}

void tp2tmx_initMapValues(struct Carte *carte) {
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
}

long tp2tmx_pseudoRandom(long max) {
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
	if(carte->sprite->nextTimeShow < SDL_GetTicks()){
		carte->sprite->show = true;
	}
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			transit = false;
      tileX = i + carte->xSection * 15 - 1;
      tileY = j + carte->ySection * 15 - 1;

      if (tileX == -1 || tileY == -1 ||
          tileX >= carte->map->height || tileY >= carte->map->width)
        continue; // Skip border lines as they should be blank
      if(carte->sprite->show && carte->isSpriteInitialized && carte->sprite->currTile.tileY == j && carte->sprite->currTile.tileX == i){
				char layerSprite[7];
				tp2animSprite_layerToString(carte->sprite->currentLayer, layerSprite);
		    if(strcmp(layer->name, layerSprite) == 0){
					tp2animSprite_render(carte->sprite, ren);
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
          if(tp2tmx_isTileOK(carte)){
          	tp2tmx_updateCurrentTile(carte->sprite);
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

bool tp2tmx_findSectionHouse(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head->next;
	int i;
	int j;
	unsigned int caseCourrante;
	unsigned int gid;
	for(i = 0; i < carte->map->height; ++i){
		for(j = 0; j < carte->map->width; ++j){
			caseCourrante = (i*carte->map->width)+j;
			gid = layer->content.gids[caseCourrante];
			if(carte->map->tiles[gid] != NULL){
				if(carte->map->tiles[gid]->id == 16){
					carte->xSection = (i-1)/15;
					carte->ySection = (j-1)/15;
					break;
				}
			}
		}
	}
}

void tp2tmx_findNbRocks(struct Carte *carte){
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

bool tp2tmx_isTileOK(struct Carte *carte){
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
	if(!tp2tmx_setTileInformations(carte, layer)){
		return false;
	}
	int idTile = carte->sprite->futureTile.idTile;
	int idTileUp = carte->sprite->futureTile.idTilely;
	if(tp2tmx_gestionEscaliersUp(idTileUp, carte, layer)){
		return true;
	}else if(tp2tmx_gestionEscaliersDown(idTile, carte, layer)){
		return true;
	}
	if(idTile == 1 || idTile == 5 || idTile == 3 || idTile == 12 || idTile == 13){
		return false;
	}
	return tp2tmx_fromPositionToCoordinates(carte, layer);
}

bool tp2tmx_fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer){
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

bool tp2tmx_setTileInformations(struct Carte *carte, tmx_layer *layer){
	int newX = carte->sprite->futureTile.tileX + carte->xSection * 15 - 1;
	int newY = carte->sprite->futureTile.tileY + carte->ySection * 15 - 1;

	carte->sprite->futureTile.tileNumber = (newX * carte->map->width) + newY;
	if(carte->sprite->futureTile.tileNumber < 0){
		return false;
	}
	carte->sprite->futureTile.tileGID = layer->content.gids[carte->sprite->futureTile.tileNumber];
	carte->sprite->futureTile.tileGIDly = layer->next->content.gids[carte->sprite->futureTile.tileNumber];
	if(carte->sprite->futureTile.tileGID > 20 || carte->sprite->futureTile.tileGIDly > 20){
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

void tp2tmx_restartFutureTile(struct Sprite *sprite){
	sprite->futureTile.tileX = sprite->currTile.tileX;
	sprite->futureTile.tileY = sprite->currTile.tileY;
	sprite->futureTile.tileNumber = sprite->currTile.tileNumber;
	sprite->futureTile.tileGID = sprite->currTile.tileGID;
	sprite->futureTile.idTile = sprite->currTile.idTile;
}

void tp2tmx_updateCurrentTile(struct Sprite *sprite){
	sprite->currTile.tileX = sprite->futureTile.tileX;
	sprite->currTile.tileY = sprite->futureTile.tileY;
	sprite->currTile.tileNumber = sprite->futureTile.tileNumber;
	sprite->currTile.tileGID = sprite->futureTile.tileGID;
	sprite->currTile.tileGIDly = sprite->futureTile.tileGIDly;
	sprite->currTile.idTile = sprite->futureTile.idTile;
	sprite->currTile.idTilely = sprite->futureTile.idTilely;
}

bool tp2tmx_changeSousMap(struct Carte *carte){
  int caseX = carte->sprite->futureTile.tileX;
  int caseY = carte->sprite->futureTile.tileY;
  if(caseX == 16 && carte->sprite->lastDirection == EAST){
    carte->xSection += carte->xSection == carte->maxXSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX -16;
    return true;
  }else if(caseX == -1 && carte->sprite->lastDirection == WEST){
    carte->xSection -= carte->xSection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileX = carte->sprite->futureTile.tileX +16;
    return true;
  }else if(caseY == 16 && carte->sprite->lastDirection == SOUTH){
    carte->ySection += carte->ySection == carte->maxYSection - 1 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY -16;
    return true;
  }else if(caseY == -1 && carte->sprite->lastDirection == NORTH){
    carte->ySection -= carte->ySection == 0 ? 0 : 1;
    carte->sprite->futureTile.tileY = carte->sprite->futureTile.tileY +16;
    return true;
  }
  return false;
}

bool tp2tmx_minerRoche(struct Carte *carte){
	if(carte->sprite->futureTile.tileGIDly == 14){
		carte->sprite->nbRoches += 1;
		int currTime = SDL_GetTicks();
		int endTime = currTime + 3000;
		int nextSound = currTime + 50;
		while(currTime < endTime){
			currTime = SDL_GetTicks();
			if(nextSound < currTime){
				tp2Sound_playShort(carte->pickaxeSound);
				nextSound += 1000;
			}
			// Drop all events
			SDL_Event e;
			SDL_PollEvent(&e);
		}
		return true;
	}
	return false;
}

bool tp2tmx_boireEau(struct Carte *carte){
	int id = carte->sprite->futureTile.tileGID;
	if(id == 2 || id == 4){
		tp2jauge_refill(carte->waterJauge);
		int currTime = SDL_GetTicks();
		int endTime = currTime + 2000;
		int nextSound = currTime + 50;
		while(currTime < endTime){
			currTime = SDL_GetTicks();
			if(nextSound < currTime){
				tp2Sound_playShort(carte->drinkSound);
				nextSound += 1000;
			}
			// Drop all events
			SDL_Event e;
			SDL_PollEvent(&e);
		}
		return true;
	}
	return false;
}

bool tp2tmx_reposManger(struct Carte *carte){
	int id = carte->sprite->futureTile.tileGIDly;
	if(id == 17){
		tp2jauge_refill(carte->sleepJauge);
		tp2jauge_refill(carte->foodJauge);
		// In the house, victory condition is verfied 
		if(carte->nbRock == carte->sprite->nbRoches){
    	carte->allMined = true; 
    	return true;
  	}
		carte->sprite->show = false;
		tp2Sound_playShort(carte->snoringSound);
		carte->sprite->nextTimeShow = SDL_GetTicks() + 5000;
		return true;
	}
	return false;
}

void tp2tmx_setIdEnFace(struct Carte *carte, tmx_layer *layer){
	switch(carte->sprite->lastDirection){
		case EAST:
			carte->sprite->futureTile.tileX+=1;
			tp2tmx_setTileInformations(carte, layer);
			break;
		case WEST:
			carte->sprite->futureTile.tileX-=1;
			tp2tmx_setTileInformations(carte, layer);
			break;
		case SOUTH:
			carte->sprite->futureTile.tileY+=1;
			tp2tmx_setTileInformations(carte, layer);
			break;
		case NORTH:
			carte->sprite->futureTile.tileY-=1;
			tp2tmx_setTileInformations(carte, layer);
			break;
	}
}

bool tp2tmx_actions(struct Carte *carte) {
	bool toRet = false;
	tmx_layer *layer = carte->map->ly_head;
	int i;
	for(i = 0; i < carte->sprite->currentLayer-1; i++){
		layer = layer->next;
	}
	tp2tmx_setIdEnFace(carte, layer);
	if(tp2tmx_minerRoche(carte)){
		tp2tmx_destroyElement(layer->next, carte->sprite->futureTile.tileNumber);
		toRet = true;
	}else if(tp2tmx_boireEau(carte)){
		toRet = true;
	}else if(tp2tmx_reposManger(carte)){
		toRet = true;
	}
	tp2tmx_restartFutureTile(carte->sprite);
	return toRet;
}

bool tp2tmx_gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer){
	switch(id){
		case 11:
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileX+=1;
			break;
		case 8:

			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileX-=1;
			break;
		case 9:
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileY-=1;
			break;
		case 10:
			carte->sprite->currentLayer+=1;
			carte->sprite->futureTile.tileY+=1;
			break;
		default:
			return false;
			break;
	}
	tp2tmx_setTileInformations(carte, layer);
	tp2tmx_updateCurrentTile(carte->sprite);
	tp2tmx_setTileInformations(carte,layer->next);
	tp2tmx_updateCurrentTile(carte->sprite);
	tp2tmx_fromPositionToCoordinates(carte, layer->next);
	return true;
}

bool tp2tmx_gestionEscaliersDown(int id, struct Carte *carte, tmx_layer *layer){
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
	tp2tmx_setTileInformations(carte, layer);
	tp2tmx_updateCurrentTile(carte->sprite);
	tp2tmx_setTileInformations(carte,layer);
	tp2tmx_updateCurrentTile(carte->sprite);
	tp2tmx_fromPositionToCoordinates(carte, layer);
	return true;
}

void tp2tmx_destroyElement(tmx_layer *layer, int tileNumber){
	layer->content.gids[tileNumber] = 0;
}
