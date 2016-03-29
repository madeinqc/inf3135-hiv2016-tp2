/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_pause.h"

struct Scene* tp2Pause_getScene(struct Application *app) {
  struct Scene *scene = calloc(1, sizeof(struct Scene));

  scene->initScene = &tp2Pause_initScene;
  scene->loadMedia = &tp2Pause_loadMedia;
  scene->viewWillAppear = &tp2Pause_viewWillAppear;
  scene->handleEvents = &tp2Pause_handleEvents;
  scene->drawScene = &tp2Pause_draw;
  scene->releaseMedia = &tp2Pause_release;

  return scene;
}

void* tp2Pause_initScene(struct Application *app) {
  struct Pause* pause = calloc(1, sizeof(struct Pause));
  return pause;
}

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Pause_loadMedia(struct Application *app, void *state) {
  struct Pause *pause = (struct Pause*) state;
  char *images[] = {CO, RE, QU};
  int i;
  for (i = 0; i < 3; ++i) {
    SDL_Surface *image = tp2image_load(app, images[i]);
    if(image == NULL){
      printf("Unable to load image %s! SDL Error : %s\n", images[i], SDL_GetError());
      return false;
    }
    pause->tabImages[i] = image;
  }

  tp2Sound_openChannel();
  pause->choiceSound = tp2Sound_loadShort(SOUND_PICKAXE);

  return true;
}

void tp2Pause_viewWillAppear(struct Application *app, void *state) {
  // NULL
}

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Pause_handleEvents(struct Application *app, void *state, SDL_Event *event) {
  struct Pause *pause = (struct Pause*) state;
  bool isConsumed = false;

  switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
        case SDLK_UP:
          if(pause->state != CONTINUE){
            pause->state--;
            tp2Sound_playShort(pause->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_DOWN:
          if(pause->state != PQUIT){
            pause->state++;
            tp2Sound_playShort(pause->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_RETURN:
          if(pause->state == PQUIT){
            app->isRunning = false;
          }
          else if(pause->state == RESTART){
            app->nextScene = tp2Accueil_getScene(app);
          }
          isConsumed = true;
          break;
        default: break;
      }
      break;
    default: break;
  }

  return isConsumed;
}

/**
 *
 */
void tp2Pause_draw(struct Application *app, void *state) {
  struct Pause *pause = (struct Pause*) state;
  SDL_Surface *image = pause->tabImages[pause->state];
  SDL_BlitSurface(image, NULL, app->gScreenSurface, NULL);
  SDL_UpdateWindowSurface(app->gWindow);
}

/**
 *
 */
void tp2Pause_release(struct Application *app, void *state) {
  struct Pause *pause = (struct Pause*) state;
  int i;
  for (i = 0; i < 3; ++i) {
    SDL_FreeSurface(pause->tabImages[i]);
    pause->tabImages[i] = NULL;
  }
  /*tp2Sound_freeShort(pause->choiceSound);
  tp2Sound_freeLong(pause->backMusic);*/
  free(pause);
}
