/**
 * @file
 * Sous-scène de carte qui gère l'événement de victoire. 
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
 * Images du menu de victoire.
 */
enum victoireState{VRESTART, VQUIT};
/**
 * Structure de victoire.
 */
struct Victoire{
	enum victoireState state;
	SDL_Texture *tabImages[2];
	Mix_Chunk* choiceSound;
};
/**
 * Creation de la scene du menu de victoire.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la scène créée.
 */
struct Scene* tp2Victoire_getScene(struct Application *app);
/**
 * Initialise la structure du menu de victoire.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la structure créée.
 */
void* tp2Victoire_initScene(struct Application *app);
/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Pointeur vers la structure du menu.
 * @return True si le chargement a réussi.
 */
bool tp2Victoire_loadMedia(struct Application *app, void *state);
/**
 * Méthode qui sert à démarrer certains processus avant l'affichage de la scène.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Victoire_viewWillAppear(struct Application *app, void *state);
/**
 * Méthode qui gère les événements du menu de victoire.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 * @param event Pointeur vers l'événement à gérer.
 * @return True si l'événement a été géré par la méthode.
 */
bool tp2Victoire_handleEvents(struct Application *app, void *state, SDL_Event *event);
/**
 * Méthode qui gère l'affichage du menu de victoire.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Victoire_draw(struct Application *app, void *state);
/**
 * Méthode qui libère les ressources chargées par loadMedia()
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Victoire_release(struct Application *app, void *state);

#endif
