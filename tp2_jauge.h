	/**
 * @file
 * Fichier permettant de gerer les trois jauges 
 *
*/

#ifndef TP2_JAUGE_H
#define TP2_JAUGE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_image.h"
#include "tp2_window.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_sound.h"

/**
 * Images des des etats de la jauge Nourriture
 */
#define FOOD_0 "assets/jauge_food/jauge-food_empty.png"
#define FOOD_1 "assets/jauge_food/jauge-food_red.png"
#define FOOD_2 "assets/jauge_food/jauge-food_yellowHalf.png"
#define FOOD_3 "assets/jauge_food/jauge-food_yellowFull.png"
#define FOOD_4 "assets/jauge_food/jauge-food_orangeHalf.png"
#define FOOD_5 "assets/jauge_food/jauge-food_orangeFull.png"
#define FOOD_6 "assets/jauge_food/jauge-food_greenHalf.png"
#define FOOD_7 "assets/jauge_food/jauge-food_greenFull.png"
/**
 * Images des des etats de la jauge Eau
 */
#define WATER_0 "assets/jauge_water/jauge-water_empty.png"
#define WATER_1 "assets/jauge_water/jauge-water_red.png"
#define WATER_1 "assets/jauge_water/jauge-water_red.png"
#define WATER_2 "assets/jauge_water/jauge-water_yellowHalf.png"
#define WATER_3 "assets/jauge_water/jauge-water_yellowFull.png"
#define WATER_4 "assets/jauge_water/jauge-water_orangeHalf.png"
#define WATER_5 "assets/jauge_water/jauge-water_orangeFull.png"
#define WATER_6 "assets/jauge_water/jauge-water_greenHalf.png"
#define WATER_7 "assets/jauge_water/jauge-water_greenFull.png"
/**
 * Images des des etats de la jauge nourriture
 */
#define SLEEP_0 "assets/jauge_sleep/jauge-sleep_empty.png"
#define SLEEP_1 "assets/jauge_sleep/jauge-sleep_red.png"
#define SLEEP_2 "assets/jauge_sleep/jauge-sleep_yellowHalf.png"
#define SLEEP_3 "assets/jauge_sleep/jauge-sleep_yellowFull.png"
#define SLEEP_4 "assets/jauge_sleep/jauge-sleep_orangeHalf.png"
#define SLEEP_5 "assets/jauge_sleep/jauge-sleep_orangeFull.png"
#define SLEEP_6 "assets/jauge_sleep/jauge-sleep_greenHalf.png"
#define SLEEP_7 "assets/jauge_sleep/jauge-sleep_greenFull.png"

/*
* Structure d'une jauge
*/
struct Jauge{
	int state; 
	SDL_Texture *tabImages[8]; 
};

/**
 * Creer une jauge
 */
struct Jauge* createJauge(char *tabImages[8], struct Application* app);
/**
 * Libere les ressources de la jauge
 * @params *app L'application
 */
void deleteJauge(struct Jauge *jauge, struct Application* app);
/**
 * Prepare le jauge pour le renderer
 * @params *app L'application
 */
void renderJauge(struct Jauge *jauge, struct Application* app);
/**
 * Bouge le jauge dans une direction
 * @params direction La direction dans laquelle bouger le jauge
 */
void moveJauge(struct Jauge *jauge, int direction);
/**
 * Gestion des evenements lies au jauge
 * @params *event L'evenement a gerer
 * @params *app L'application
 */
void handleEventsJauge(struct Jauge *jauge, SDL_Event *event, struct Application *app);
#endif