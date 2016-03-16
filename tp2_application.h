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
};