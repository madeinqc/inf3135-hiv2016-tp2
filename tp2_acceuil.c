/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_acceuil.h"

// Chargement des ressources
bool loadMedia(struct Application *application) {
  application->gImage = loadImage(application, PE);
  if(application->gImage == NULL){
    printf("Unable to load image %s! SDL Error : %s\n",  PE, SDL_GetError());
    return false;
  }
  return loopMenu(application);
}

SDL_Surface* loadImage(struct Application *application, char *imagePath){
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

bool loopMenu(struct Application *application){
	struct Menu menu = {PLAY, EASY, {PE, PM, PH, DE, DM, DH, QE, QM, QH}};
	Mix_Chunk* choiceSound = loadShortSound(SOUND_PICKAXE);
	bool isRunning = true;
	bool isPlay = true;

	int i = 0;
	int j = 0;

  while (isRunning) {
    // Boucle de lecture d'événement
    SDL_Event e;
    while (SDL_PollEvent(&e) && isRunning) {
      switch(e.type){
      	case SDL_KEYDOWN:
      		switch(e.key.keysym.sym){
      			case SDLK_UP:
      				if(i != 0){
      					i--;
      					playShortSound(choiceSound);
      				}
      				break;
      			case SDLK_DOWN:
      				if(i != 2){
      					i++;
      					playShortSound(choiceSound);
      				}
      				break;
      			case SDLK_RIGHT:
      				if(i == 1){
      					if(j != 2){
      						j++;
      						playShortSound(choiceSound);
      					}
      				}
      				break;
      			case SDLK_LEFT:
      				if(i == 1){
      					if(j != 0){
      						j--;
      						playShortSound(choiceSound);
      					}
      				}
      				break;
      			case SDLK_RETURN:
      				if(i == 2){
      					isPlay = false;
      				}
      				isRunning = false;
      				break;
      			case SDLK_ESCAPE:
      				isRunning = false;
      				break;
      			default: break;
      		}
      		break;
      	default: break;
      }
      application->gImage = loadImage(application, menu.tabImages[(i*3)+j]);
      SDL_BlitSurface(application->gImage, NULL, application->gScreenSurface, NULL);
    	SDL_UpdateWindowSurface(application->gWindow);
    }
  }
  freeShortSound(choiceSound);
  return isPlay;
}