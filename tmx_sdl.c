#include <stdio.h>
#include <tmx.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define DISPLAY_HEIGHT  600
#define DISPLAY_WIDTH   900
#define MAX_PATH_LENGTH 100

static SDL_Renderer *ren = NULL;

/**
 * Function used by the TMX library for loading images.
 *
 * Assumes that all assets are in the same folder than the map.
 * Otherwise, this function must be customized.
 *
 * @param  The path of the image
 */
void* sdl_img_loader(const char *path) {
    return IMG_LoadTexture(ren, path);
}

/**
 * Draws the given layer.
 *
 * @param map    The map whose layer is drawn
 * @param layer  The layer to be drawn
 */
void draw_layer(tmx_map *map, tmx_layer *layer) {
    unsigned int i, j;
    unsigned int gid;
    tmx_tileset *tileset;
    tmx_tile *tile;
    tmx_image *image;
    SDL_Rect srcrect, dstrect;
    SDL_Texture* texture;
    for (i = 0; i < map->height; i++) {
        for (j = 0; j < map->width; j++) {
            gid = layer->content.gids[(i * map->width) + j];
            tile = map->tiles[gid];
            if (tile != NULL) {
                tileset = map->tiles[gid]->tileset;
                image = map->tiles[gid]->image;
                srcrect.x = map->tiles[gid]->ul_x;
                srcrect.y = map->tiles[gid]->ul_y;
                srcrect.w = dstrect.w = tileset->tile_width;
                srcrect.h = dstrect.h = tileset->tile_height;
                dstrect.x = j * tileset->tile_width;
                dstrect.y = i * tileset->tile_height;
                if (image) {
                    texture = (SDL_Texture*)image->resource_image;
                }
                SDL_RenderCopy(ren, texture, &srcrect, &dstrect);
            }
        }
    }
}

/**
 * Renders the complete map on a texture.
 *
 * @param map  The map to be rendered
 * @return     The texture of the rendered map
 */
SDL_Texture* render_map(tmx_map *map) {
    SDL_Texture *res;
    tmx_layer *layer = map->ly_head;
    int w, h;

    w = map->width  * map->tile_width;
    h = map->height * map->tile_height;

    if (!(res = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h)))
        printf("SDL create texture not working: %s", SDL_GetError());
    SDL_SetRenderTarget(ren, res);
    SDL_RenderClear(ren);
    while (layer) {
        if (layer->visible)
            draw_layer(map, layer);
        layer = layer->next;
    }
    SDL_SetRenderTarget(ren, NULL);
    return res;
}

/**
 * Main.
 */
int main(int argc, char **argv) {
    tmx_map *map = NULL;
    SDL_Window *win;
    SDL_Event e;
    SDL_Texture *map_bmp;
    SDL_Rect map_rect;
    int key_state[2] = {0, 0};

    if (argc != 2) {
        printf("This program expects 1 argument");
        return 1;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL init not working: %s", SDL_GetError());
        return 2;
    }

    if (!(win = SDL_CreateWindow("Tiled example",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_SHOWN))) {
        printf("SDL create window not working: %s", SDL_GetError());
        return 2;
    }

    if (!(ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
        printf("SDL create renderer not working: %s", SDL_GetError());
        return 3;
    }

    // Custom function for TMX loader
    tmx_img_load_func = (void* (*)(const char*))sdl_img_loader;
    tmx_img_free_func = (void  (*)(void*))      SDL_DestroyTexture;

    if (!(map = tmx_load(argv[1]))) {
        printf("TMX map could not be loaded properly: %s", tmx_strerr());
        return 4;
    }

    if (!(map_bmp = render_map(map))) {
        printf("TMX map could not be rendered: %s", SDL_GetError());
        return 5;
    }

    while (SDL_WaitEvent(&e)) {

        if (e.type == SDL_QUIT) break;

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, map_bmp, NULL, NULL);
        SDL_RenderPresent(ren);
    }

    tmx_map_free(map);

    SDL_DestroyTexture(map_bmp);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
