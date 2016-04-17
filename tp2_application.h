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
   * Texture principale de l'application.
   */
  SDL_Texture* texture;
  /**
   * Le sprite courrant.
   */
  struct Sprite *currSprite;
  /**
   * Est-ce que l'application doit toujours fonctionner.
   */
  bool isRunning;
  /**
   * La scène courrante.
   */
  struct Scene *scene;
  /**
   * La nouvelle scène à charger.
   */
  struct Scene *nextScene;
  /**
   * La difficulté du jeu.
   */
  enum Difficulty diff;
  /**
   * Est-ce que le jeu est sur pause.
   */
  bool isPause;
  /**
   * Est-ce que le jeu a été gagné.
   */
  bool isWon; 
  /**
   * Est-ce que le jeu a été perdu.
   */
  bool isLost; 
};

#endif
