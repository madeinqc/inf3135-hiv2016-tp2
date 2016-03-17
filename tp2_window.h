/**
 * @file
 * Description a venir...
 *
 */

#ifndef TP2_WINDOW_H
#define TP2_WINDOW_H

#include "sdl2.h"
#include <stdbool.h>
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_accueil.h"

/**
 * Title de la fenêtre principale.
 */
#define WINDOW_TITLE "Bob le mineur"
/**
 * Largeur de la fenêtre principale.
 */
#define SCREEN_WIDTH 640
/**
 * Hauteur de la fenêtre principale.
 */
#define SCREEN_HEIGHT 480

/**
 * Initialise la SDL et remplis {@link #Application application}.
 * @param application Un pointeur vers la structure Application à remplir.
 * @return True si l'initialisation a réussi.
 */
bool initialize(struct Application *application);

/**
 * Initialise la scène d'accueil.
 */
void initMainScene(struct Application *app);

/**
 * Effectue la boucle de jeu en traitant les messages reçu par la SDL.
 * La boucle de jeu s'effectue environ 60 fois par seconde pour un rendu de 60 fps.
 * @param application Un pointeur vers la structure Application à utiliser.
 */
void gameLoop(struct Application *application);

/**
 * Ferme la SDL correctement en libérant les ressources nécessaires.
 * @param application Un pointeur vers la structure Application à libérer.
 * @return True si la libération des ressources a réussi.
 */
void shutDown(struct Application *application);

#endif
