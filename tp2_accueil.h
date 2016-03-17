/**
 * @file
 * Description a venir...
 *
*/
#include "sdl2.h"
#include <stdbool.h>
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"

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
#define SOUND_ACCEUIL "assets/sounds/acceuilSong.wav"

enum State{PLAY, DIFFICULTY, QUIT};
enum Difficulty{EASY, MEDIUM, HARD};

struct Menu{
	enum State state;
	enum Difficulty diff;
	SDL_Surface *tabImages[9];
  Mix_Chunk* choiceSound;
  Mix_Music* backMusic;
};

struct Menu* tp2Accueil_init(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Accueil_loadMedia(struct Application *app, struct Menu *menu);

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Accueil_handleEvents(struct Application *app, struct Menu *menu, SDL_Event *event);

/**
 *
 */
void tp2Accueil_draw(struct Application *app, struct Menu *menu);

/**
 *
 */
void tp2Accueil_release(struct Application *app, struct Menu *menu);
