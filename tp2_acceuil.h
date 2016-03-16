/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>
#include "tp2_application.h"

/**
 * Image du menu principal
 */
#define IMAGE_MENU "assets/imagesAccueil/PlayEasy.png"

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
 * Initialise la SDL et remplis {@link #Application application}.
 * @param application Un pointeur vers la structure Application à remplir.
 * @return True si l'initialisation a réussi.
 */
bool initialize(struct Application *application);

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