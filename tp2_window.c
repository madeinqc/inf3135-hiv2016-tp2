/**
 * @file
 * Description a venir...
 *
*/
#include "tp2_window.h"

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
  SDL_UpdateWindowSurface(application->gWindow);
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
      // TODO Scene events
    }
    // TODO Scene rendering
    SDL_BlitSurface(application->gImage, NULL, application->gScreenSurface, NULL);
    SDL_UpdateWindowSurface(application->gWindow);

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
