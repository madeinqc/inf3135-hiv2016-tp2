/**
 * @file
 * Fichier permettant de gerer les sprites animes
 *
*/

#ifndef TP2_ANIMSPRITE_H
#define TP2_ANIMSPRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tp2_structCarte.h"
#include "sdl2.h"
#include "tp2_image.h"
#include "tp2_window.h"
#include "tp2_application.h"
#include "tp2_scene.h"
#include "tp2_sound.h"
#include "tp2_tmx.h"

/**
 * Image du personnage principal
 */
#define IMG_PERSO "assets/walking.png"

/**
* Structure de la sprite
*/
struct Sprite {
  // Image informations
  int nbColumns;
  int nbRows;
  int spriteWidth;
  int spriteHeight;
  // Drawing offset
  int xOffset;
  int yOffset;
  // Frames
  int currentFrame;
  int delayBetweenFrame;
  int lastFrameTime;
  // Position
  unsigned int posX;
  unsigned int posY;
  int currentLayer;
  enum Direction orientation;
  enum Direction nextDirection;
  // Animation
  enum Direction walkingToward;
  // Nombre de roche minees
  int nbRoches;
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
bool tp2animSprite_create(const char *filename, int numRows, int numColumns,
                          int initialFrame, int delayBetweenFrame, struct Application *app);

/**
 * Libere les ressources du sprite
 * @params *app L'application
 */
void tp2animSprite_delete(struct Sprite *sprite, struct Application *app);

/**
 * Prepare le sprite pour le renderer
 * @params *app L'application
 */
void tp2animSprite_render(struct Carte *carte, struct Sprite *sprite, SDL_Renderer *ren);

/**
 * Bouge le sprite dans une direction si possible
 */
void tp2animSprite_move(struct Sprite *sprite, struct Carte *carte);

/**
 * Gestion des evenements lies au sprite
 * @params *event L'evenement a gerer
 * @params *app L'application
 */
void tp2animSprite_layerToString(int layer, char *string);

bool tp2animSprite_handleEvents(struct Sprite *sprite, SDL_Event *event, struct Application *app, struct Carte *carte);

void tp2animSprite_updateOffsets(struct Sprite *sprite, struct Carte *carte);

#endif