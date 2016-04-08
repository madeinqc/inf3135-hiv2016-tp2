/**
 * @file
 * Fichier permettant de gerer les sprites animes
 *
*/

#ifndef TP2_ANIMSPRITE_H
#define TP2_ANIMSPRITE_H

#include <stdbool.h>
#include "sdl2.h"
#include "tp2_image.h"
#include "tp2_window.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_sound.h"



/**
 * Image du personnage principal
 */
#define IMG_PERSO "assets/walking.png"
/**
 * Enumeration des directions
 */
enum Direction{EAST,SOUTH,WEST,NORTH};
/**
* Structure de la sprite
*/
struct Sprite{
	// Image informations
	int nbColumns;
	int nbRows;
	int nbFrames;
	int spriteWidth;
	int spriteHeight;
	int xOffset;
	int yOffset;
	// Frames
	int currentFrame;
	int delayBetweenFrame;
	// Position
	int posX;
	int posY;
	int lastDirection;
	int currentLayer;
	// Speed
	int speed;
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
bool createSprite(const char* filename, int numRows, int numColumns, int numFrames, 
					 int initialFrame, int delayBetweenFrame, int speed, struct Application* app);
/**
 * Libere les ressources du sprite
 * @params *app L'application
 */
void deleteSprite(struct Sprite *sprite, struct Application* app);
/**
 * Prepare le sprite pour le renderer
 * @params *app L'application
 */
void renderSprite(struct Sprite *sprite, SDL_Renderer *ren);
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
void layerToString(int layer, char* string);

void handleEventsSprite(struct Sprite *sprite, SDL_Event *event, struct Application *app);
#endif