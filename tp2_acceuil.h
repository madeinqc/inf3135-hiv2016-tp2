/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>
#include "tp2_window.h"
#include "tp2_sound.h"

/**
 * Image du menu principal
 */
#define PE "assets/imagesAccueil/PlayEasy.png"
#define PM "assets/imagesAccueil/PlayMedium.png"
#define PH "assets/imagesAccueil/PlayHard.png"
#define DE "assets/imagesAccueil/DiffEasy.png"
#define DM "assets/imagesAccueil/DiffMedium.png"
#define DH "assets/imagesAccueil/DiffHard.png"
#define QE "assets/imagesAccueil/QuitEasy.png"
#define QM "assets/imagesAccueil/QuitMedium.png"
#define QH "assets/imagesAccueil/QuitHard.png"
/**
 * Sons du menu principal
 */
#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"

enum State{PLAY, DIFFICULTY, QUIT};
enum Difficulty{EASY, MEDIUM, HARD};

struct Menu{
	enum State state;
	enum Difficulty diff;
	char *tabImages[9];
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
SDL_Surface* loadImage(struct Application *application, char *imagePath);

/**
 * 
 * @params application Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool loopMenu(struct Application *application);