/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_defaite.h"

struct Scene* tp2Defaite_getScene(struct Application *app) {
  struct Scene *scene = calloc(1, sizeof(struct Scene));

  scene->initScene = &tp2Defaite_initScene;
  scene->loadMedia = &tp2Defaite_loadMedia;
  scene->viewWillAppear = &tp2Defaite_viewWillAppear;
  scene->handleEvents = &tp2Defaite_handleEvents;
  scene->drawScene = &tp2Defaite_draw;
  scene->releaseMedia = &tp2Defaite_release;

  return scene;
}

void* tp2Defaite_initScene(struct Application *app) {
  struct Defaite* defaite = calloc(1, sizeof(struct Defaite));
  return defaite;
}

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Defaite_loadMedia(struct Application *app, void *state) {
  struct Defaite *defaite = (struct Defaite*) state;
  char *images[] = {defaite_RE, defaite_QU};
  int i;
  for (i = 0; i < 2; ++i) {
    SDL_Texture *image = tp2image_load(app, images[i]);
    if(image == NULL){
      printf("Unable to load image %s! SDL Error : %s\n", images[i], SDL_GetError());
      return false;
    }
    defaite->tabImages[i] = image;
  }

  tp2Sound_openChannel();
  defaite->choiceSound = tp2Sound_loadShort(SOUND_PICKAXE);

  return true;
}

void tp2Defaite_viewWillAppear(struct Application *app, void *state) {
  struct Defaite *defaite = (struct Defaite*) state;
}

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Defaite_handleEvents(struct Application *app, void *state, SDL_Event *event) {
  struct Defaite *defaite = (struct Defaite*) state;
  bool isConsumed = false;

  switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
        case SDLK_UP:
          if(defaite->state != DRESTART){
            defaite->state--;
            tp2Sound_playShort(defaite->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_DOWN:
          if(defaite->state != DQUIT){
            defaite->state++;
            tp2Sound_playShort(defaite->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_RETURN:
          if(defaite->state == DQUIT){
            app->isRunning = false;
          }
          else {
            app->isLost = false; 
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
void tp2Defaite_draw(struct Application *app, void *state) {
  struct Defaite *defaite = (struct Defaite*) state;
  int imageIndex = defaite->state;
  SDL_Texture *image = defaite->tabImages[imageIndex];
  SDL_Rect texr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(app->gRenderer, image, NULL, &texr);
}
/**
 *
 */
void tp2Defaite_release(struct Application *app, void *state) {
  struct Defaite *defaite = (struct Defaite*) state;
  int i;
  for (i = 0; i < 2; ++i) {
    SDL_DestroyTexture(defaite->tabImages[i]);
    defaite->tabImages[i] = NULL;
  }
  tp2Sound_freeShort(defaite->choiceSound);
  //tp2Sound_freeLong(defaite->backMusic);
  free(defaite);
}
