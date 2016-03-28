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
  application->renderer = SDL_CreateRenderer(application->gWindow, -1, SDL_RENDERER_ACCELERATED);
  if (application->renderer == NULL) {
      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
      return false;
  }
  application->gScreenSurface = SDL_GetWindowSurface(application->gWindow);
  SDL_FillRect(application->gScreenSurface, NULL,
      SDL_MapRGB(application->gScreenSurface->format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(application->gWindow);
  return true;
}

void initMainScene(struct Application *app) {
  app->nextScene = tp2Accueil_getScene(app);
}

// Boucle de jeu
void gameLoop(struct Application *application) {
  application->isRunning = true;
  void* currentState = NULL;

  while (application->isRunning) {

    // Charge un scène au besoin
    if (application->nextScene != NULL) {
      if (application->scene != NULL) {
        application->scene->releaseMedia(application, currentState);
      }
      application->scene = application->nextScene;
      application->nextScene = NULL;

      currentState = application->scene->initScene(application);
      if (application->scene->loadMedia(application, currentState)) {
        application->scene->viewWillAppear(application, currentState);
      } else {
        printf("Could not load scene");
        application->isRunning = false;
        application->scene->releaseMedia(application, currentState);
        break;
      }
    }

    // Boucle de lecture d'événement
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        application->isRunning = false;
      }
      application->scene->handleEvents(application, currentState, &e);
    }
    // TODO Scene rendering
    SDL_SetRenderDrawColor(application->renderer, 0x00, 0x00, 0x00, 0xFF);

    application->scene->drawScene(application, currentState);
    //SDL_UpdateWindowSurface(application->gWindow);

    SDL_RenderClear(application->renderer);
    SDL_RenderCopy(application->renderer, application->texture, NULL, NULL);
    RenderSprite(application->currSprite, 100, 200, SOUTH);
    SDL_RenderPresent(application->renderer);
    // Délais de 16ms pour avoir environ 60 fps
    SDL_Delay(16);
  }

  application->scene->releaseMedia(application, currentState);
}

// Liberation des ressources et de SDL
void shutDown(struct Application *application) {
  SDL_DestroyWindow(application->gWindow);
  application->gWindow = NULL;
  SDL_Quit();
}
