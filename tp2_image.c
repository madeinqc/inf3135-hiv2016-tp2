#include "tp2_image.h"

SDL_Surface* tp2image_load(struct Application *application, char *imagePath){
  SDL_Surface* newSurface = NULL;
  SDL_Surface* loadedSurface = IMG_Load(imagePath);
  if(loadedSurface == NULL){
    printf("Unable to load image %s! SDL Error : %s\n", imagePath, "Probleme...");
  } else {
    newSurface = SDL_ConvertSurface(loadedSurface, application->gScreenSurface->format, 0);
    if(newSurface == NULL){
      printf("Unable to optimize image %s! SDL Error: %s\n", imagePath, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newSurface;
}

