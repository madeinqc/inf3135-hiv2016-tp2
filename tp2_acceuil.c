/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_acceuil.h"

// Chargement des ressources
bool loadMedia(struct Application *application) {
  application->gImage = loadImage(application);
  if(application->gImage == NULL){
    printf("Unable to load image %s! SDL Error : %s\n", IMAGE_MENU, SDL_GetError());
    return false;
  }
  return true;
}

SDL_Surface* loadImage(struct Application *application){
  SDL_Surface* newSurface = NULL;
  SDL_Surface* loadedSurface = IMG_Load(IMAGE_MENU);
  if(loadedSurface == NULL){
    printf("Unable to load image %s! SDL Error : %s\n", IMAGE_MENU, "Probleme...");
  } else {
    newSurface = SDL_ConvertSurface(loadedSurface, application->gScreenSurface->format, 0);
    if(newSurface == NULL){
      printf("Unable to optimize image %s! SDL Error: %s\n", IMAGE_MENU, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newSurface;
}