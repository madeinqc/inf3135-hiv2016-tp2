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
#define IMG_FOOD_0 "assets/jauges-food_empty.png"
#define IMG_FOOD_1 "assets/jauges-food_red.png"
#define IMG_FOOD_2 "assets/jauges-food_yellowHalf.png"
#define IMG_FOOD_3 "assets/jauges-food_yellowFull.png"
#define IMG_FOOD_4 "assets/jauges-food_orangeHalf.png"
#define IMG_FOOD_5 "assets/jauges-food_orangeFull.png"
#define IMG_FOOD_6 "assets/jauges-food_greenHalf.png"
#define IMG_FOOD_7 "assets/jauges-food_greenFull.png"
/**
 * Images des des etats de la jauge Eau
 */
#define IMG_WATER_0 "assets/jauges-water_empty.png"
#define IMG_WATER_1 "assets/jauges-water_red.png"
#define IMG_WATER_2 "assets/jauges-water_yellowHalf.png"
#define IMG_WATER_3 "assets/jauges-water_yellowFull.png"
#define IMG_WATER_4 "assets/jauges-water_orangeHalf.png"
#define IMG_WATER_5 "assets/jauges-water_orangeFull.png"
#define IMG_WATER_6 "assets/jauges-water_greenHalf.png"
#define IMG_WATER_7 "assets/jauges-water_greenFull.png"
/**
 * Images des des etats de la jauge nourriture
 */
#define IMG_SLEEP_0 "assets/jauges-sleep_empty.png"
#define IMG_SLEEP_1 "assets/jauges-sleep_red.png"
#define IMG_SLEEP_2 "assets/jauges-sleep_yellowHalf.png"
#define IMG_SLEEP_3 "assets/jauges-sleep_yellowFull.png"
#define IMG_SLEEP_4 "assets/jauges-sleep_orangeHalf.png"
#define IMG_SLEEP_5 "assets/jauges-sleep_orangeFull.png"
#define IMG_SLEEP_6 "assets/jauges-sleep_greenHalf.png"
#define IMG_SLEEP_7 "assets/jauges-sleep_greenFull.png"

/*
* Structure d'une jauge
*/
struct Jauge{
	int etat; 
	char *images[]; 
	// Rendering
	SDL_Texture *texture;
};

/**
 * Creer un spritesheet
 * @params *filename Chemin vers le fichier du sprite
 * @params numRows Le nombre de ligne du fichier sprite
 * @params numColumns Le nombre de colonne du fichier sprite
 * @params numFrames Le nombre de frames par direction du sprite
 * @params initialFrame La frame initiale
 * @params delayBetweenFrame Le delai entre les frames
 * @params speed La vitesse pour bouger le sprite
 * @params *app L'application
 * @return False si la creation echoue
 */
bool CreateSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, int speed, struct Application* app);
/**
 * Libere les ressources du sprite
 * @params *app L'application
 */
void DeleteSprite(struct Sprite *sprite, struct Application* app);
/**
 * Prepare le sprite pour le renderer
 * @params *app L'application
 */
void RenderSprite(struct Sprite *sprite, struct Application* app);
/**
 * Bouge le sprite dans une direction
 * @params direction La direction dans laquelle bouger le sprite
 */
void moveSprite(struct Sprite *sprite, int direction);
/**
 * Gestion des evenements lies au sprite
 * @params *event L'evenement a gerer
 * @params *app L'application
 */
void handleEventsSprite(struct Sprite *sprite, SDL_Event *event, struct Application *app);
#endif