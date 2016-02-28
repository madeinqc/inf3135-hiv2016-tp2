#include "tp2.h"
#include <unistd.h>
#include <stdio.h>

#define WINDOW_TITLE "Bob le mineur"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

void gameLoop(struct Application *application) {
  bool isRunning = true;
  while (isRunning) {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        isRunning = false;
      }
    }

    SDL_Delay(16);
  }
}

// Chargement des ressources
bool loadMedia(struct Application *application) {
  return true;
}

// Liberation des ressources et de SDL
void shutDown(struct Application *application) {
  SDL_DestroyWindow(application->gWindow);
  application->gWindow = NULL;
  SDL_Quit();
}
