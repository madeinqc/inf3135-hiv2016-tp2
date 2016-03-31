#include "tp2_image.h"

SDL_Texture* tp2image_load(struct Application *application, char *imagePath){
  SDL_Texture* loadedSurface = IMG_LoadTexture(application->gRenderer, imagePath);
  if(loadedSurface == NULL){
    printf("Unable to load image %s! SDL Error : %s\n", imagePath, "Probleme...");
  }
  return loadedSurface;
}

