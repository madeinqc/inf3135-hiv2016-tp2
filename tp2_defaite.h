/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_DEFAITE_H
#define TP2_DEFAITE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"


/**
 * Image du menu de defaite
 */
#define defaite_RE "assets/fin_jeu/go_restart.png"
#define defaite_QU "assets/fin_jeu/go_quit.png"

 /**
 * Sons du menu de pause
 */
//#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"

enum defaiteState{DRESTART, DQUIT};

struct Defaite{
	enum defaiteState state;
	SDL_Texture *tabImages[2];
	Mix_Chunk* choiceSound;
};

struct Scene* tp2Defaite_getScene(struct Application *app);

void* tp2Defaite_initScene(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Defaite_loadMedia(struct Application *app, void *state);

void tp2Defaite_viewWillAppear(struct Application *app, void *state);

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Defaite_handleEvents(struct Application *app, void *state, SDL_Event *event);

/**
 *
 */
void tp2Defaite_draw(struct Application *app, void *state);

/**
 *
 */
void tp2Defaite_release(struct Application *app, void *state);

#endif
