/**
 * @file
 * Description a venir...
 *
 */
#include "tp2_tmx.h"

static SDL_Renderer *ren = NULL;

tmx_map* tp2tmx_loadRandomMap(SDL_Renderer *renderer) {
  tmx_map *map = NULL;

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

	map = tmx_load(fullPath);
  if (!map) {
    printf("Err: %s", tmx_strerr());
  }

	free(fullPath);

	tp2tmx_freeAllMapsName(&mapsName);

  return map;
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

void tp2tmx_drawLayer(SDL_Renderer *ren, tmx_map *map, tmx_layer *layer, int sectionX, int sectionY,
                      int displacementX, int displacementY) {
	unsigned int i, j, tileX, tileY, modX, modY, halfMapWidth, halfMapHeight;
	unsigned int gid;
	tmx_tileset *tileset;
	tmx_tile *tile;
	tmx_image *image;
	SDL_Rect srcrect, dstrect;
	SDL_Texture* texture;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {

      tileX = i + sectionX * 15 - 1;
      tileY = j + sectionY * 15 - 1;

      if (tileX == -1 || tileY == -1 ||
          tileX >= map->height || tileY >= map->width)
        continue; // Skip border lines as they should be blank

			gid = layer->content.gids[(tileX * map->width) + tileY];

			tile = map->tiles[gid];
			if (tile != NULL) {
        if (map->tiles[gid]->id == 18) continue; // Skip rendering the character as it will be rendered differently

				tileset = map->tiles[gid]->tileset;
				image = map->tiles[gid]->image;
				srcrect.x = map->tiles[gid]->ul_x;
				srcrect.y = map->tiles[gid]->ul_y;
				srcrect.w = dstrect.w = image->width;
				srcrect.h = dstrect.h = image->height;
        
        halfMapWidth = map->tile_width/2;
        halfMapHeight = map->tile_height/2;

        dstrect.x = ((j - i) * halfMapWidth + layer->offsetx) + 75 * map->tile_width / 10 + displacementX;
        dstrect.y = ((j + i) * halfMapHeight + layer->offsety) + displacementY - 64 
           + ((tileset->tile_height / image->height) - 1) * 64;

				if (image) {
					texture = (SDL_Texture*)image->resource_image;
				}
				SDL_RenderCopy(ren, texture, &srcrect, &dstrect);
			}
		}
	}
}

SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, tmx_map *map, int xSection, int ySection) {
	SDL_Texture *res;
	tmx_layer *layer = map->ly_head;
	int w, h, maxXDisplacement = 0, maxYDisplacement = 0;

	w = (map->width < 16 ? map->width : 16) * map->tile_width;
	h = (map->height < 16 ? map->height : 16) * map->tile_height;
  h += 1 * map->tile_height; // Allow more space for higher layers

  // TODO Calculate max displacement once
  while (layer) {
    if (abs(layer->offsetx) > maxXDisplacement)
      maxXDisplacement = abs(layer->offsetx);
    if (abs(layer->offsety) > maxYDisplacement)
      maxYDisplacement = abs(layer->offsety);
    layer = layer->next;
  }
  layer = map->ly_head;
  maxYDisplacement += 1 * map->tile_height; // Allow more space for higher layers

  w += maxXDisplacement;
  h += maxYDisplacement;

	if (!(res = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h)))
		printf("SDL create texture not working: %s", SDL_GetError());
	SDL_SetRenderTarget(ren, res);
	SDL_RenderClear(ren);
	while (layer) {
		if (layer->visible)
			tp2tmx_drawLayer(ren, map, layer, xSection, ySection, maxXDisplacement, maxYDisplacement);
		layer = layer->next;
	}
	SDL_SetRenderTarget(ren, NULL);
	return res;
}
