/**
 * @file
 * Gestion de tout ce qui touche la fenetre
 *
*/
#include "tp2_window.h"

// Initialisation
bool initialize(struct Application *app) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  app->gWindow = SDL_CreateWindow(WINDOW_TITLE,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (app->gWindow == NULL) {
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
	if (!(app->gRenderer = SDL_CreateRenderer(app->gWindow, -1, SDL_RENDERER_ACCELERATED))) {
		printf("SDL create renderer not working: %s", SDL_GetError());
	}
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

<<<<<<< HEAD
    application->scene->drawScene(application, currentState);

    // Render les elements dans le renderer
    SDL_RenderClear(application->renderer);
    SDL_RenderCopy(application->renderer, application->texture, NULL, NULL);
    SDL_RenderPresent(application->renderer);
=======
    SDL_RenderClear(application->gRenderer);
    application->scene->drawScene(application, currentState);
    SDL_RenderPresent(application->gRenderer);
>>>>>>> c4508611f5e26231511c46d34dd0c02cce586ba5

    // Délais de 16ms pour avoir environ 60 fps
    SDL_Delay(16);
  }

  application->scene->releaseMedia(application, currentState);
}

void shutDown(struct Application *application) {
  SDL_DestroyRenderer(application->gRenderer);
  SDL_DestroyWindow(application->gWindow);
  application->gWindow = NULL;
  SDL_Quit();
}
