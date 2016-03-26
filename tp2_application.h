#ifndef TP2_APPLICATION_H
#define TP2_APPLICATION_H

/**
 * La structure Application contient toutes les informations requises par la SDL.
 */
struct Application {
  /**
   * La fenêtre utilisée par le jeu.
   */
  SDL_Window* gWindow;
  /**
   * La surface de rendu.
   */
  SDL_Surface* gScreenSurface;
  /**
   * L'image chargée sur la surface.
   */
  SDL_Surface* gImage;
  /**
   * Renderer pour les sprites
   */
  SDL_Renderer* renderer;
  /**
   * Is the game running
   */ 
  bool isRunning;
  /**
   * The current scene
   */
  struct Scene *scene;
  /**
   * The scene to load
   */
  struct Scene *nextScene;
};

#endif
