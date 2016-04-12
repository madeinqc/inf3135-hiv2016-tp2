/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_VICTOIRE_H
#define TP2_VICTOIRE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"


/**
 * Image du menu de victoire
 */
#define victoire_RE "assets/fin_jeu/win_restart.png"
#define victoire_QU "assets/fin_jeu/win_quit.png"

 /**
 * Sons du menu de victoire
 */
//#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"

enum victoireState{VRESTART, VQUIT};

struct Victoire{
	enum victoireState state;
	SDL_Texture *tabImages[2];
	Mix_Chunk* choiceSound;
};

struct Scene* tp2Victoire_getScene(struct Application *app);

void* tp2Victoire_initScene(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Victoire_loadMedia(struct Application *app, void *state);

void tp2Victoire_viewWillAppear(struct Application *app, void *state);

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Victoire_handleEvents(struct Application *app, void *state, SDL_Event *event);

/**
 *
 */
void tp2Victoire_draw(struct Application *app, void *state);

/**
 *
 */
void tp2Victoire_release(struct Application *app, void *state);

#endif
