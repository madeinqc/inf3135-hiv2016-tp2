#include <stdbool.h>
#ifdef Darwin
  #include <SDL2/SDL.h>
#else
  #include <SDL.h>
#endif

// Application data structure
struct Application {
  SDL_Window* gWindow;
  SDL_Surface* gScreenSurface;
};


// Initialisation
bool initialize(struct Application *application);

// Boucle de jeu
void gameLoop(struct Application *application);

// Chargement des ressources
bool loadMedia(struct Application *application);

// Liberation des ressources et de SDL
void shutDown(struct Application *application);
