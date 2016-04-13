/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_CARTE_H
#define TP2_CARTE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"
#include "tp2_accueil.h"
#include "tp2_tmx.h"
#include "tp2_jauge.h"
#include "tp2_animSprite.h"
#include "tp2_defaite.h"
#include "tp2_victoire.h"
#include "tp2_pause.h"

/**
 * Sons du jeu
 */
#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"
#define IMG_BACK "assets/background_game.png"

struct Scene* tp2Carte_getScene(struct Application *app);

void* tp2Carte_initScene(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Carte_loadMedia(struct Application *app, void *state);

void tp2Carte_viewWillAppear(struct Application *app, void *state);

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Carte_handleEvents(struct Application *app, void *state, SDL_Event *event);

/**
 *
 */
void tp2Carte_draw(struct Application *app, void *state);

/**
 *
 */
void tp2Carte_release(struct Application *app, void *state);

#endif
