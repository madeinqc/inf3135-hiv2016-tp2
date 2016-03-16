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
    printf("Unable to load image %s! SDL Error : %s\n", IMAGE_PE, SDL_GetError());
    return false;
  }
  return true;
}

SDL_Surface* loadImage(struct Application *application){
  SDL_Surface* newSurface = NULL;
  SDL_Surface* loadedSurface = IMG_Load(IMAGE_PE);
  if(loadedSurface == NULL){
    printf("Unable to load image %s! SDL Error : %s\n", IMAGE_PE, "Probleme...");
  } else {
    newSurface = SDL_ConvertSurface(loadedSurface, application->gScreenSurface->format, 0);
    if(newSurface == NULL){
      printf("Unable to optimize image %s! SDL Error: %s\n", IMAGE_PE, SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
  }
  return newSurface;
}

bool loopMenu(struct Application *application){
	bool isRunning = true;
  while (isRunning) {
    // Boucle de lecture d'événement
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch(e.type){
      	case SDL_KEYDOWN:
      		switch(e.key.keysym.sym){
      			case SDLK_UP:
      			case SDLK_DOWN:
      			case SDLK_RIGHT:
      			case SDLK_LEFT:
      			case SDLK_RETURN:
      			default:
      				break;
      		}
      }
    }
    SDL_BlitSurface(application->gImage, NULL, application->gScreenSurface, NULL);
    SDL_UpdateWindowSurface(application->gWindow);
  }
}