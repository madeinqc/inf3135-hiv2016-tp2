/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>
#include "tp2_window.h"

/**
 * Image du menu principal
 */
#define IMAGE_PE "assets/imagesAccueil/PlayEasy.png"
#define IMAGE_PM "assets/imagesAccueil/PlayMedium.png"
#define IMAGE_PH "assets/imagesAccueil/PlayHard.png"
#define IMAGE_DE "assets/imagesAccueil/DiffEasy.png"
#define IMAGE_DM "assets/imagesAccueil/DiffMedium.png"
#define IMAGE_DH "assets/imagesAccueil/DiffHard.png"
#define IMAGE_QE "assets/imagesAccueil/QuitEasy.png"
#define IMAGE_QM "assets/imagesAccueil/QuitMedium.png"
#define IMAGE_QH "assets/imagesAccueil/QuitHard.png"

enum State{PLAY, DIFFICULTY, QUIT};
enum Difficulty{EASY, MEDIUM, HARD};

struct Menu{
	enum State stateMenu;
	enum Difficulty diffMenu;
};

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
 * 
 * @params application Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool loopMenu(struct Application *application);