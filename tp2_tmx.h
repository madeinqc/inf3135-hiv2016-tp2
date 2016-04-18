/**
 * @file
 * Gestion de tout ce qui touche au rendering du jeu.
 */

#ifndef TP2_TMX_H
#define TP2_TMX_H

#include <dirent.h>
#include <time.h>
#include "tp2_animSprite.h"
#include "tp2_structCarte.h"

#define INITIAL_CAPACITY 8
#define ASSETS_PATH "./assets/"

/**
 * Structure 
 */
struct mapsName {
  char** names;
  long count;
  long capacity;
};
/**
 * 
 * @param
 * @return 
 */
void* sdl_img_loader(const char *path);
/**
 * 
 * @param
 * @param
 * @return 
 */
void tp2tmx_loadRandomMap(SDL_Renderer *renderer, struct Carte *carte);
/**
 * 
 * @param
 * @return 
 */
void tp2tmx_initMapValues(struct Carte *carte);
/**
 * 
 * @param
 * @return 
 */
void tp2tmx_mapFree(tmx_map *map);
/**
 * 
 * @param
 * @return 
 */
long tp2tmx_pseudoRandom(long max);
/**
 * 
 * @param
 * @return 
 */
void tp2tmx_getAllMapsName(struct mapsName *mapsName);
/**
 * 
 * @param
 * @return 
 */
void tp2tmx_freeAllMapsName(struct mapsName *mapsName);
/**
 * 
 * @param
 * @param
 * @param
 * @return 
 */
void tp2tmx_drawLayer(SDL_Renderer *ren, struct Carte *carte, tmx_layer *layer);
/**
 * 
 * @param
 * @param
 * @return 
 */
SDL_Texture* tp2tmx_renderMap(SDL_Renderer *ren, struct Carte *carte);
/**
 * Trouve la sous-section qui contient la maison pour initialiser le jeu sur cette sous-carte.
 * @param carte La carte courante.
 * @return True si une sous-section a été trouvée.
 */
bool tp2tmx_findSectionHouse(struct Carte *carte);
/**
 * Trouve le nombre de roches à miner dans la carte.
 * @param carte La carte courante.
 */
void tp2tmx_findNbRocks(struct Carte *carte);
/**
 * Vérifie si la future case est accessible par le personnage.
 * @param carte La carte courante.
 * @return True si elle est accessible.
 */
bool tp2tmx_isTileOK(struct Carte *carte);
/**
 * Trouve toutes les informations de la future case à partir de son x et son y.
 * @param carte La carte courante.
 * @param layer Le layer sur lequel la case se trouve.
 * @return True si la case cherchée existe et est une case valide.
 */
bool tp2tmx_setTileInformations(struct Carte *carte, tmx_layer *layer);
/**
 * Transforme la position dans la grille de la sous-carte du personnage en coordonnées pour le renderer.
 * @param carte La carte courante.
 * @param layer Le layer sur lequel le personnage se trouve.
 * @return True si l'opération réussi.
 */
bool tp2tmx_fromPositionToCoordinates(struct Carte *carte, tmx_layer *layer);
/**
 * Remet la future position à la position courante.
 * @param sprite Le sprite courant.
 */
void tp2tmx_restartFutureTile(struct Sprite *sprite);
/**
 * Met à jour la position courante à partir de la future position.
 * @param sprite Le sprite courant.
 * @return 
 */
void tp2tmx_updateCurrentTile(struct Sprite *sprite);
/**
 * Change la sous-carte affichée si nécessaire.
 * @param carte La carte courante.
 * @return True si la sous-carte a été changée.
 */
bool tp2tmx_changeSousMap(struct Carte *carte);
/**
 * Vérifie et mine une roche si possible.
 * @param carte La carte courante.
 * @return True si une roche a été minée.
 */
bool tp2tmx_minerRoche(struct Carte *carte);
/**
 * Vérifie et boit de l'eau si possible.
 * @param carte La carte courante.
 * @return True si l'eau a été bu.
 */
bool tp2tmx_boireEau(struct Carte *carte);
/**
 * Vérifie et dort/mange si c'est possible.
 * @param carte La carte courante.
 * @return True si le personnage s'est reposé/a mangé.
 */
bool tp2tmx_reposManger(struct Carte *carte);
/**
 * Vérifie les informations de la tuile devant le personnage.
 * @param carte La carte courante.
 * @param layer Le layer sur lequel est le personnage.
 */
void tp2tmx_setIdEnFace(struct Carte *carte, tmx_layer *layer);
/**
 * Verifie et monte un escalier si c'est possible.
 * @param id Le id de la case devant le sprite.
 * @param carte La carte courante.
 * @param layer Le layer sur lequel se trouve le personnage.
 * @return True si un escalier a été monté.
 */
bool tp2tmx_gestionEscaliersUp(int id, struct Carte *carte, tmx_layer *layer);
/**
 * Verifie et descend un escalier si c'est possible.
 * @param idTile Le id de la case devant (et dessous) le sprite.
 * @param carte La carte courante.
 * @param layer Le layer sur leuquel se trouve le sprite.
 * @return True si un escalier a été descendu.
 */
bool tp2tmx_gestionEscaliersDown(int idTile, struct Carte *carte, tmx_layer *layer);
/**
 * Détruit une tuile (change son gid pour 0)
 * @param layer Le layer sur lequel se trouve la tuile.
 * @param tileNumber Le numéro de la tuile à supprimer.
 */
void tp2tmx_destroyElement(tmx_layer *layer, int tileNumber);
/**
 * Gère les différentes actions possibles du personnage.
 * @param carte La carte courante.
 * @return True si une action a été effectuée par le personnage.
 */
bool tp2tmx_actions(struct Carte *carte);
#endif
