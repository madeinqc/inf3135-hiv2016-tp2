/**
 * @file
 * Le module TP2 est le module par défaut.
 * C'est lui qui s'occupe du chargement, de la boucle de jeu et de la fermeture.
 */

#include <stdbool.h>
#include "sdl2.h"

/**
 * Title de la fenêtre principale.
 */
#define WINDOW_TITLE "Bob le mineur"
/**
 * Largeur de la fenêtre principale.
 */
#define SCREEN_WIDTH 640
/**
 * Hauteur de la fenêtre principale.
 */
#define SCREEN_HEIGHT 480

/**
 * Image du menu principal
 */
#define IMAGE_MENU "assets/imagesAccueil/PlayEasy.png"

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


/**
 * Point d'entré du programme.
 * Cette fonction s'assure de l'initialisation et de la libération des ressources avant d'appeller la boucle de jeu.
 * @return 0 si tout c'est bien passé, sinon un code d'erreur négatif.
 */
int main();

/**
 * Initialise la SDL et remplis {@link #Application application}.
 * @param application Un pointeur vers la structure Application à remplir.
 * @return True si l'initialisation a réussi.
 */
bool initialize(struct Application *application);

/**
 * Charge les ressources graphiques en mémoire.
 * @param application Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool loadMedia(struct Application *application);

/**
 * Charge une image dans un SDL_Surface.
 * @params application Un pointeur vers la structure Application à utiliser.
 * @return SDL_Surface contenant l'image ou NULL.
 */
SDL_Surface* loadImage(struct Application *application);

/**
 * Effectue la boucle de jeu en traitant les messages reçu par la SDL.
 * La boucle de jeu s'effectue environ 60 fois par seconde pour un rendu de 60 fps.
 * @param application Un pointeur vers la structure Application à utiliser.
 */
void gameLoop(struct Application *application);

/**
 * Ferme la SDL correctement en libérant les ressources nécessaires.
 * @param application Un pointeur vers la structure Application à libérer.
 * @return True si la libération des ressources a réussi.
 */
void shutDown(struct Application *application);
