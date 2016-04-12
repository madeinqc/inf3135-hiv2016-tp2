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

			gid = layer->content.gids[(tileX * carte->map->width) + tileY];
			//printf("%d\n", (tileX * carte->map->width) + tileY);
			tile = carte->map->tiles[gid];
			if (tile != NULL) {
        if (carte->map->tiles[gid]->id == 18) continue; // Skip rendering the character as it will be rendered differently
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
        	carte->sprite->futureTile.tileX = 10;
        	carte->sprite->futureTile.tileX = 10;
        	carte->isSpriteInitialized = true;
        }
        /*
        // Render le personnage sur le level dessous celui ou il est
        char layerSprite[7];
        layerToString(carte->sprite->currentLayer -1, layerSprite);
        if(strcmp(layer->name, layerSprite) == 0){
        	int tileID = carte->map->tiles[gid]->id;
        	if(isTileOK(carte->sprite, layer, carte)){
        		carte->sprite->posX = carte->sprite->futureX;
        		carte->sprite->posY = carte->sprite->futureY;
        	}else{
        		carte->sprite->futureX = carte->sprite->posX;
        		carte->sprite->futureY = carte->sprite->posY;
        	}
        	if(carte->isSpriteInitialized){
        		renderSprite(carte->sprite, ren);
        	}
        	// Liste les cases transitives
        	if(i%15 == 0 || j%15 == 0){
						if(tileID != 3 && tileID != 1){
							transit = transitionSprite(carte, dstrect.x, dstrect.y);
						}
					}
        }*/

				if (image) {
					texture = (SDL_Texture*)image->resource_image;
				}
				SDL_RenderCopy(ren, texture, &srcrect, &dstrect);
			}
		}
	}
	if(carte->isSpriteInitialized){
		char layerSprite[7];
    layerToString(carte->sprite->currentLayer -1, layerSprite);
    if(strcmp(layer->name, layerSprite) == 0){
  		isTileOK(carte);
  		renderSprite(carte->sprite, ren);
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
	//printf("Sous-section x : %d, Sous-section y : %d\n", carte->xSection, carte->ySection);
	while (layer) {
		if (layer->visible)
			//printf("Layer : %s\n", layer->name);
			tp2tmx_drawLayer(ren, carte, layer);
			//printf("-----------------------------\n");
		layer = layer->next;
	}
	SDL_SetRenderTarget(ren, NULL);
	//printf("===================================\n");
	return res;
}

bool findSectionHouse(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head->next;
	int i;
	int j;
	unsigned int caseCourrante;
	unsigned int gid;
	int nbRoches = 0;
	for(i = 0; i < carte->map->height; ++i){
		for(j = 0; j < carte->map->width; ++j){
			caseCourrante = (i*carte->map->width)+j;
			gid = layer->content.gids[caseCourrante];
			if(carte->map->tiles[gid] != NULL){
				if(carte->map->tiles[gid]->id == 16){
					carte->xSection = (i-1)/15;
					carte->ySection = (j-1)/15;
					break;
				}else if(carte->map->tiles[gid]->id == 8){
					nbRoches+=1;
				}
			}
		}
	}
}

bool isTileOK(struct Carte *carte){
	tmx_layer *layer = carte->map->ly_head;
	int i;
	for(i = 0; i < carte->sprite->currentLayer-1; i++){
		layer = layer->next;
	}
	setTileInformations(carte, layer);
	int idTile = carte->sprite->futureTile.idTile;
	if(idTile != 0){
		fromPositionToCoordinates(carte, layer);
		return true;
	}
	return false;
}

void fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer){
	int halfMapWidth = carte->map->tile_width/2;
  int halfMapHeight = carte->map->tile_height/2;
  int i = carte->sprite->futureTile.tileX;
  int j = carte->sprite->futureTile.tileY;
  int gid = carte->sprite->futureTile.tileGID;
  tmx_tile *tile;
  tile = carte->map->tiles[gid];
  if(tile != NULL){
  	tmx_tileset *tileset = carte->map->tiles[gid]->tileset;
  	tmx_image *image = carte->map->tiles[carte->sprite->futureTile.tileGID]->image;
  	carte->sprite->posX = ((j - i) * halfMapWidth + layer->offsetx) + 75 * carte->map->tile_width / 10 + carte->maxXDisplacement;
  	carte->sprite->posY = ((j + i) * halfMapHeight + layer->offsety) + carte->maxYDisplacement - 64
    		+ ((tileset->tile_height / image->height) - 1) * 64 +25;
  	carte->sprite->currTile = carte->sprite->futureTile;
  }else{
  	carte->sprite->futureTile = carte->sprite->currTile;
  }
}

void setTileInformations(struct Carte *carte, tmx_layer *layer){
	int newX = carte->sprite->futureTile.tileX + carte->xSection * 15 - 1;
	int newY = carte->sprite->futureTile.tileY + carte->ySection * 15 - 1;
	
	printf("X : %d, Y : %d, Original X : %d, Y : %d\n", newX, newY, carte->sprite->futureTile.tileX, carte->sprite->futureTile.tileY);
	if(newX >= 0 && newY >= 0){
		carte->sprite->futureTile.tileNumber = (newX * carte->map->width) + newY;
		printf("Tile Number : %d\n", carte->sprite->futureTile.tileNumber);
		carte->sprite->futureTile.tileGID = layer->content.gids[carte->sprite->futureTile.tileNumber];
		tmx_tile *tile = carte->map->tiles[carte->sprite->futureTile.tileGID];
		if(tile != NULL){
			carte->sprite->futureTile.idTile = carte->map->tiles[carte->sprite->futureTile.tileGID]->id;
			printf("Tile ID : %d\n", carte->sprite->futureTile.idTile);
			//printf("Source : %s\n", carte->map->tiles[carte->sprite->futureTile.tileGID]->image->source);
		}
	}
}

/*bool isTileOK(struct Sprite *sprite, tmx_layer *layer, struct Carte *carte){
	// Verification pour les 4 cotes de la map
	int x = sprite->futureX;
	float y = sprite->futureY;

	// Ne permet pas d'aller sur l'eau

	float YtoComp;
	// Haut gauche
	YtoComp = abs(0.5*x - 370);
	if(y < YtoComp) return false;
	// Bas droit
	YtoComp = abs(0.5*x - 806);
	if(y > YtoComp) return false;
	// Bas gauche
	YtoComp = abs(-0.5*x - 322);
	if(y > YtoComp) return false;
	// Haut droit
	YtoComp = abs(-0.5*x + 114);
	if(y < YtoComp) return false;
	return true;
}*/

/*bool transitionSprite(struct Carte *carte, int x, int y){
	int spriteX = carte->sprite->posX;
	int spriteY = carte->sprite->posY;
	int buff = 30;
	int diff;
	if(y < 354){
		if(x < 472){
			// Transition haut gauche
			if(spriteX > x && spriteX < (x+40)){
				diff = abs(abs(0.5*spriteX - 370) - spriteY);
				if(diff < 4 && carte->sprite->lastDirection == NORTH){
					carte->ySection -= carte->ySection == 0 ? 0 : 1;
					carte->sprite->futureX = spriteX + 436;
					carte->sprite->futureY = spriteY + 218;
					return true;
				}
			}
		}else{
			// Transition haut droit
			if(spriteX < x && spriteX > (x-40)){
				diff = abs(abs(-0.5*spriteX + 114) - spriteY);
				if(diff < 4 && carte->sprite->lastDirection == WEST){
					carte->xSection -= carte->xSection == 0 ? 0 : 1;
					carte->sprite->futureX = spriteX - 436;
					carte->sprite->futureY = spriteY + 218;
					return true;
				}
			}
		}
	}else{
		if(x < 472){
			// Transition bas gauche
			if(spriteX > x && spriteX < (x+40)){
				diff = abs(-0.5*spriteX - 322) - spriteY;
				if(diff < 4 && carte->sprite->lastDirection == EAST){
					carte->xSection += carte->xSection == carte->maxXSection - 1 ? 0 : 1;
					carte->sprite->futureX = spriteX + 436;
					carte->sprite->futureY = spriteY - 218;
					return true;
				}
			}
		}else{
			// Transition bas droit
			if(spriteX < x && spriteX > (x-40)){
				diff = abs(abs(0.5*spriteX - 806) - spriteY);
				if(diff < 4 && carte->sprite->lastDirection == SOUTH){
					carte->ySection += carte->ySection == carte->maxYSection - 1 ? 0 : 1;
					carte->sprite->futureX = spriteX - 436;
					carte->sprite->futureY = spriteY - 218;
					return true;
				}
			}
		}
	}
}*/