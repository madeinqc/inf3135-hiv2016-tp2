/**
 * @file
 * Structure scène.
 */
#ifndef TP2_SCENE_H
#define TP2_SCENE_H

#include "sdl2.h"
#include "tp2_application.h"

/**
 * Structure contenant des pointeurs vers les méthodes de la scène.
 * Le pointeur void en paramètre de quelques méthodes représente la structure derrière la scène.
 */
struct Scene {
  /**
   * Pointeur vers une méthode qui initialise la scène.
   */
  void *(*initScene)(struct Application *);

  /**
	 * Pointeur vers une méthode qui charge les médias de la scène.
	 */
  bool (*loadMedia)(struct Application *, void *);

  /**
	 * Pointeur vers une méthode qui précharge certains éléments avant l'affichage de la scène.
	 */
  void (*viewWillAppear)(struct Application *, void *);

  /**
	 * Pointeur vers une méthode qui gère les événements de la scène.
	 */
  bool (*handleEvents)(struct Application *, void *, SDL_Event *);

  /**
	 * Pointeur vers une méthode qui affiche la scène.
	 */
  void (*drawScene)(struct Application *, void *);

  /**
	 * Pointeur vers une méthode qui libère les médias de la scène.
	 */
  void (*releaseMedia)(struct Application *, void *);
};

#endif
