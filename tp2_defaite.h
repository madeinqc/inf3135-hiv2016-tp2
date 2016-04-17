/**
 * @file
 * Sous-scène de carte qui gère l'événement de défaite. 
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
 * Images du menu de défaite.
 */
#define defaite_RE "assets/fin_jeu/go_restart.png"
#define defaite_QU "assets/fin_jeu/go_quit.png"

/**
 * Énumération des options du menu disponibles. 
 */
enum defaiteState{DRESTART, DQUIT};
/**
 * Structure de défaite.
 */
struct Defaite{
	enum defaiteState state;
	SDL_Texture *tabImages[2];
	Mix_Chunk* choiceSound;
};
/**
 * Creation de la scene du menu de défaite.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la scène créée.
 */
struct Scene* tp2Defaite_getScene(struct Application *app);
/**
 * Initialise la structure du menu de défaite.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la structure créée.
 */
void* tp2Defaite_initScene(struct Application *app);
/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Pointeur vers la structure du menu.
 * @return True si le chargement a réussi.
 */
bool tp2Defaite_loadMedia(struct Application *app, void *state);
/**
 * Méthode qui sert à démarrer certains processus avant l'affichage de la scène.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Defaite_viewWillAppear(struct Application *app, void *state);
/**
 * Méthode qui gère les événements du menu de défaite.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 * @param event Pointeur vers l'événement à gérer.
 * @return True si l'événement a été géré par la méthode.
 */
bool tp2Defaite_handleEvents(struct Application *app, void *state, SDL_Event *event);
/**
 * Méthode qui gère l'affichage du menu de défaite.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Defaite_draw(struct Application *app, void *state);
/**
 * Méthode qui libère les ressources chargées par loadMedia().
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Defaite_release(struct Application *app, void *state);

#endif
