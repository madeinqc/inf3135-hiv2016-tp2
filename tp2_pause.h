/**
 * @file
 * Sous-scène de carte qui gère l'événement de pause. 
 *
*/

#ifndef TP2_PAUSE_H
#define TP2_PAUSE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"

/**
 * Image du menu de pause
 */
#define CO "assets/imagesPause/PauseContinue.png"
#define RE "assets/imagesPause/PauseRestart.png"
#define QU "assets/imagesPause/PauseQuit.png"

 /**
 * Sons du menu de pause
 */
#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"

/**
 * Énumération des options du menu disponibles. 
 */
enum pauseState{CONTINUE, RESTART, PQUIT};
/**
 * Structure de pause.
 */
struct Pause{
	enum pauseState state;
	SDL_Texture *tabImages[3];
	Mix_Chunk* choiceSound;
};
/**
 * Creation de la scene du menu de pause.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la scène créée.
 */
struct Scene* tp2Pause_getScene(struct Application *app);
/**
 * Initialise la structure du menu de pause.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la structure créée.
 */
void* tp2Pause_initScene(struct Application *app);
/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Pointeur vers la structure du menu.
 * @return True si le chargement a réussi.
 */
bool tp2Pause_loadMedia(struct Application *app, void *state);
/**
 * Méthode qui sert à démarrer certains processus avant l'affichage de la scène.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Pause_viewWillAppear(struct Application *app, void *state);
/**
 * Méthode qui gère les événements du menu de pause.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 * @param event Pointeur vers l'événement à gérer.
 * @return True si l'événement a été géré par la méthode.
 */
bool tp2Pause_handleEvents(struct Application *app, void *state, SDL_Event *event);
/**
 * Méthode qui gère l'affichage du menu de pause.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Pause_draw(struct Application *app, void *state);
/**
 * Méthode qui libère les ressources chargées par loadMedia().
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Pause_release(struct Application *app, void *state);

#endif
