/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_victoire.h"

struct Scene* tp2Victoire_getScene(struct Application *app) {
  struct Scene *scene = calloc(1, sizeof(struct Scene));

  scene->initScene = &tp2Victoire_initScene;
  scene->loadMedia = &tp2Victoire_loadMedia;
  scene->viewWillAppear = &tp2Victoire_viewWillAppear;
  scene->handleEvents = &tp2Victoire_handleEvents;
  scene->drawScene = &tp2Victoire_draw;
  scene->releaseMedia = &tp2Victoire_release;

  return scene;
}

void* tp2Victoire_initScene(struct Application *app) {
  struct Victoire* victoire = calloc(1, sizeof(struct Victoire));
  return victoire;
}

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Victoire_loadMedia(struct Application *app, void *state) {
  struct Victoire *victoire = (struct Victoire*) state;
  char *images[] = {victoire_RE, victoire_QU};
  int i;
  for (i = 0; i < 2; ++i) {
    SDL_Texture *image = tp2image_load(app, images[i]);
    if(image == NULL){
      printf("Unable to load image %s! SDL Error : %s\n", images[i], SDL_GetError());
      return false;
    }
    victoire->tabImages[i] = image;
  }

  tp2Sound_openChannel();
  victoire->choiceSound = tp2Sound_loadShort(SOUND_PICKAXE);

  return true;
}

void tp2Victoire_viewWillAppear(struct Application *app, void *state) {
  struct Victoire *victoire = (struct Victoire*) state;
}

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Victoire_handleEvents(struct Application *app, void *state, SDL_Event *event) {
  struct Victoire *victoire = (struct Victoire*) state;
  bool isConsumed = false;

  switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
        case SDLK_UP:
          if(victoire->state != DRESTART){
            victoire->state--;
            tp2Sound_playShort(victoire->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_DOWN:
          if(victoire->state != DQUIT){
            victoire->state++;
            tp2Sound_playShort(victoire->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_RETURN:
          if(victoire->state == DQUIT){
            app->isRunning = false;
          }
          else {
            app->isWon = false; 
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
void tp2Victoire_draw(struct Application *app, void *state) {
  struct Victoire *victoire = (struct Victoire*) state;
  int imageIndex = victoire->state;
  SDL_Texture *image = victoire->tabImages[imageIndex];
  SDL_Rect texr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(app->gRenderer, image, NULL, &texr);
}
/**
 *
 */
void tp2Victoire_release(struct Application *app, void *state) {
  struct Victoire *victoire = (struct Victoire*) state;
  int i;
  for (i = 0; i < 2; ++i) {
    SDL_DestroyTexture(victoire->tabImages[i]);
    victoire->tabImages[i] = NULL;
  }
  tp2Sound_freeShort(victoire->choiceSound);
  //tp2Sound_freeLong(victoire->backMusic);
  free(victoire);
}
