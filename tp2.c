/**
 * @file
 * Le module TP2 est le module par défaut.
 * C'est lui qui s'occupe du chargement, de la boucle de jeu et de la fermeture.
 */

#include "tp2.h"

int main() {
  struct Application app;
  if (initialize(&app)) {
    loadMedia(&app);
    gameLoop(&app);
    shutDown(&app);
  } else {
    printf("Could not initialize SDL");
  }
}

// Initialisation
bool initialize(struct Application *application) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  application->gWindow = SDL_CreateWindow(WINDOW_TITLE,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (application->gWindow == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  application->gScreenSurface = SDL_GetWindowSurface(application->gWindow);
  SDL_FillRect(application->gScreenSurface, NULL,
      SDL_MapRGB(application->gScreenSurface->format, 0xFF, 0xFF, 0xFF));
  return true;
}

// Chargement des ressources
bool loadMedia(struct Application *application) {
  return true;
}

// Boucle de jeu
void gameLoop(struct Application *application) {
  bool isRunning = true;
  while (isRunning) {

    // Boucle de lecture d'événement
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    // Délais de 16ms pour avoir environ 60 fps
    SDL_Delay(16);
  }
}

// Liberation des ressources et de SDL
void shutDown(struct Application *application) {
  SDL_DestroyWindow(application->gWindow);
  application->gWindow = NULL;
  SDL_Quit();
}
