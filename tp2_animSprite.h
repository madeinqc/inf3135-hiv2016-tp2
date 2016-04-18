/**
 * @file
 * Fichier permettant de gérer le personnage principal.
*/
#ifndef TP2_ANIMSPRITE_H
#define TP2_ANIMSPRITE_H

#include <stdbool.h>
#include "tp2_structCarte.h"
#include "sdl2.h"
#include "tp2_image.h"
#include "tp2_window.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_sound.h"
#include "tp2_tmx.h"

/**
 * Image du personnage principal.
 */
#define IMG_PERSO "assets/walking.png"
/**
 * Enumeration des directions.
 */
enum Direction{EAST,SOUTH,WEST,NORTH};

/**
 * Structure d'une position
 */
struct Position{
	// Varie entre 0 et 15
	int tileX;
	int tileY;

	int tileNumber;

	// GID pour layer -1 et layer courant
	int tileGID;
	int tileGIDly;

	// ID pour layer -1 et layer courant
	int idTile;
	int idTilely;
};
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
	struct Position currTile;
	struct Position futureTile;
	int lastDirection;
	int currentLayer;
	// Speed
	int speed;
	// Nombre de roche minees
	int nbRoches;
	// Rendering
	SDL_Texture *texture;
	// Render ou non le sprite
	int nextTimeShow;
	bool show;
	bool isAnimating;
};

/**
 * Creer un spritesheet animé.
 * @param filename Chemin vers le fichier du sprite.
 * @param numRows Le nombre de ligne du fichier sprite.
 * @param numColumns Le nombre de colonne du fichier sprite.
 * @param numFrames Le nombre de frames par direction du sprite.
 * @param initialFrame La frame initiale.
 * @param delayBetweenFrame Le delai entre les frames.
 * @param speed La vitesse pour bouger le sprite.
 * @param app L'application.
 * @return True si la création réussi.
 */
bool tp2animSprite_create(const char *filename, int numRows, int numColumns, int numFrames,
													int initialFrame, int delayBetweenFrame, int speed, struct Application *app);
/**
 * Libere les ressources du sprite.
 * @param sprite Le sprite à supprimer.
 * @param app L'application.
 */
void tp2animSprite_delete(struct Sprite *sprite, struct Application *app);
/**
 * Prépare le sprite pour le renderer.
 * @param carte La carte où render.
 * @param sprite Le sprite à render.
 * @param app L'application
 */
void tp2animSprite_render(struct Carte *carte, struct Sprite *sprite, SDL_Renderer *ren);
/**
 * Bouge le sprite dans une direction.
 * @param sprite Le sprite à bouger.
 * @param direction La direction dans laquelle bouger le sprite.
 * @param carte La carte sur laquelle le sprite bouge.
 */
void tp2animSprite_move(struct Sprite *sprite, int direction, struct Carte *carte);

void tp2animSprite_layerToString(int layer, char *string);

/**
 * Gestion des evenements lies au sprite.
 * @param sprite Le sprite.
 * @param event L'événement à gérer.
 * @param app L'application.
 * @param carte La carte sur laquelle l'événement est appelé.
 * @return True si l'événement est géré par la méthode.
 */
bool tp2animSprite_handleEvents(struct Sprite *sprite, SDL_Event *event, struct Application *app, struct Carte *carte);

/**
 * Ajuste les offsets du sprite pour s'ajusté à l'animation.
 * @param carte La carte contenant le sprite.
 * @param sprite Le sprite à ajuster.
 */
void tp2animSprite_updateOffsets(struct Carte *carte, struct Sprite *sprite);
#endif