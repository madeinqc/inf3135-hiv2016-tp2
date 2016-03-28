/**
 * @file
 * Description a venir...
 *
*/

#ifndef TP2_PAUSE_H
#define TP2_PAUSE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_image.h"

/**
 * Image du menu de pause
 */
#define CO "assets/imagesPause/Continue.png"
#define RE "assets/imagesPause/Restart.png"
#define QU "assets/imagesPause/Quit.png"

enum State{CONTINUE, RESTART, QUIT};

struct Pause{
	enum State state;
	SDL_Surface *tabImages[3];
};

struct Scene* tp2Pause_getScene(struct Application *app);

void* tp2Pause_initScene(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Pause_loadMedia(struct Application *app, void *state);

void tp2Pause_viewWillAppear(struct Application *app, void *state);

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Pause_handleEvents(struct Application *app, void *state, SDL_Event *event);

/**
 *
 */
void tp2Pause_draw(struct Application *app, void *state);

/**
 *
 */
void tp2Pause_release(struct Application *app, void *state);

#endif
