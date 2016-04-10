#ifndef TP2_APPLICATION_H
#define TP2_APPLICATION_H


/**
 * Enumération des difficultés possibles.
 */
enum Difficulty{EASY, MEDIUM, HARD};

/**
 * La structure Application contient toutes les informations requises par la SDL.
 */
struct Application {
  /**
   * La fenêtre utilisée par le jeu.
   */
  SDL_Window* gWindow;
  /**
   * Le renderer utilisé pour dessiner le jeu.
   */
  SDL_Renderer* gRenderer;
  /**
   * L'image chargée sur la surface.
   */
  SDL_Surface* gImage;
  /**
   * Texture principale de l'application
   */
  SDL_Texture* texture;
  /**
   * Le sprite courrant
   */
  struct Sprite *currSprite;
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
  /**
   * The difficulty of the game.
   */
  enum Difficulty diff;

  bool isPause;

  bool isWon; 

  bool isLost; 
};

#endif
