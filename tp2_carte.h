/**
 * @file
 * Gestion de la scène carte.
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
 * Sons du jeu.
 */
#define SOUND_PICKAXE "assets/sounds/pickaxe.wav"
#define SOUND_SNORING "assets/sounds/snoring.wav"
#define SOUND_DRINK "assets/sounds/drink.wav"
#define MUSIC_GAME "assets/sounds/gameSong.wav"

/**
 * Image du fond.
 */
#define IMG_BACK "assets/background_game.png"

/**
 * Création de la scène carte.
 * @param app L'application courante.
 * @return La scène créée.
 */
struct Scene* tp2Carte_getScene(struct Application *app);
/**
 * Initialise la structure de la carte.
 * @param app L'application courante.
 * @return Un pointeur vers la structure de la carte.
 */
void* tp2Carte_initScene(struct Application *app);

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Un pointeur vers la structure de la carte.
 * @return True si le chargement a réussi.
 */
bool tp2Carte_loadMedia(struct Application *app, void *state);
/**
 * Démarrage de certains processus avant l'affichage de la scène.
 * @param app L'application courante.
 * @param state Un pointeur vers la structure de la carte.
 */
void tp2Carte_viewWillAppear(struct Application *app, void *state);

/**
 * Méthode qui gère les événements de la scène carte.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Un pointeur vers la structure de la carte.
 * @param event L'événement à gérer.
 * @return True si l'événement a été géré par la méthode.
 */
bool tp2Carte_handleEvents(struct Application *app, void *state, SDL_Event *event);

/**
 * Méthode qui render la scène carte.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Un pointeur vers la structure de la carte.
 */
void tp2Carte_draw(struct Application *app, void *state);

/**
 * Méthode qui décharge les médias chargés par la scène carte.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @param state Un pointeur vers la structure de la carte.
 */
void tp2Carte_release(struct Application *app, void *state);

#endif