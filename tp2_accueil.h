/**
 * @file
 * Contient toutes les méthodes relatives au menu d'acceuil
 *
*/

#ifndef TP2_ACCUEIL_H
#define TP2_ACCUEIL_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_application.h"
#include "tp2_animSprite.h"
#include "tp2_scene.h"
#include "tp2_window.h"
#include "tp2_sound.h"
#include "tp2_image.h"
#include "tp2_pause.h"
#include "tp2_carte.h"

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
#define SOUND_ACCEUIL "assets/sounds/acceuilSong2.wav"
/**
 * Énumération des options du menu disponibles. 
 */
enum State{PLAY, DIFFICULTY, QUIT};
/**
 * Structure de medu d'acceuil. 
 */
struct Menu{
	enum State state;
	SDL_Texture *tabImages[9];
  Mix_Chunk* choiceSound;
  Mix_Music* backMusic;
};
/**
 * Creation de la scene du menu d'acceuil.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la scène créée.
 */
struct Scene* tp2Accueil_getScene(struct Application *app);
/**
 * Initialise la structure du menu d'acceuil.
 * @param app Pointeur vers l'application.
 * @return void* Pointeur vers la structure créée.
 */
void* tp2Accueil_initScene(struct Application *app);
/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Accueil_loadMedia(struct Application *app, void *state);
/**
 * Méthode qui sert à démarrer certains processus avant l'affichage de la scène.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Accueil_viewWillAppear(struct Application *app, void *state);
/**
 * Méthode qui gère les événements du menu d'acceuil
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 * @param event Pointeur vers l'événement à gérer.
 * @return True si l'événement a été géré par la méthode.
 */
bool tp2Accueil_handleEvents(struct Application *app, void *state, SDL_Event *event);
/**
 * Méthode qui gère l'affichage du menu d'acceuil.
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Accueil_draw(struct Application *app, void *state);
/**
 * Méthode qui libère les ressources chargées par loadMedia()
 * @param app Pointeur vers l'application.
 * @param state Pointeur vers la structure du menu.
 */
void tp2Accueil_release(struct Application *app, void *state);

#endif
