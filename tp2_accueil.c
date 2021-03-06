/**
 * @file
 * Contient toutes les méthodes relatives au menu d'acceuil
 *
*/
#include "tp2_accueil.h"

struct Scene* tp2Accueil_getScene(struct Application *app) {
  struct Scene *scene = calloc(1, sizeof(struct Scene));

  scene->initScene = &tp2Accueil_initScene;
  scene->loadMedia = &tp2Accueil_loadMedia;
  scene->viewWillAppear = &tp2Accueil_viewWillAppear;
  scene->handleEvents = &tp2Accueil_handleEvents;
  scene->drawScene = &tp2Accueil_draw;
  scene->releaseMedia = &tp2Accueil_release; 

  return scene;
}

void* tp2Accueil_initScene(struct Application *app) {
  struct Menu* menu = calloc(1, sizeof(struct Menu));
  return menu;
}

bool tp2Accueil_loadMedia(struct Application *app, void *state) {
  struct Menu *menu = (struct Menu*) state;
  char *images[] = {PE, PM, PH, DE, DM, DH, QE, QM, QH};
  int i;
  for (i = 0; i < 9; ++i) {
    SDL_Texture *image = tp2image_load(app, images[i]);
    if(image == NULL){
      printf("Unable to load image %s! SDL Error : %s\n", images[i], SDL_GetError());
      return false;
    }
    menu->tabImages[i] = image;
  }

	tp2Sound_openChannel();
	menu->choiceSound = tp2Sound_loadShort(SOUND_PICKAXE);
	menu->backMusic = tp2Sound_loadLong(SOUND_ACCEUIL);
  
  return true;
}

void tp2Accueil_viewWillAppear(struct Application *app, void *state) {
  struct Menu *menu = (struct Menu*) state;
  tp2Sound_playLong(menu->backMusic);
}

bool tp2Accueil_handleEvents(struct Application *app, void *state, SDL_Event *event) {
  struct Menu *menu = (struct Menu*) state;
  bool isConsumed = false;

  switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
        case SDLK_UP:
          if(menu->state != PLAY){
            menu->state--;
            tp2Sound_playShort(menu->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_DOWN:
          if(menu->state != QUIT){
            menu->state++;
            tp2Sound_playShort(menu->choiceSound);
          }
          isConsumed = true;
          break;
        case SDLK_RIGHT:
          if(menu->state == DIFFICULTY){
            if(app->diff != HARD){
              app->diff++;
              tp2Sound_playShort(menu->choiceSound);
            }
          }
          isConsumed = true;
          break;
        case SDLK_LEFT:
          if(menu->state == DIFFICULTY){
            if(app->diff != EASY){
              app->diff--;
              tp2Sound_playShort(menu->choiceSound);
            }
          }
          isConsumed = true;
          break;
        case SDLK_RETURN:
          if(menu->state == QUIT){
            app->isRunning = false;
          } else if (menu->state == PLAY) {
            app->nextScene = tp2Carte_getScene(app);
          }
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
void tp2Accueil_draw(struct Application *app, void *state) {
  struct Menu *menu = (struct Menu*) state;
  int imageIndex = (menu->state * 3) + app->diff;
  SDL_Texture *image = menu->tabImages[imageIndex];
  SDL_Rect texr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_RenderCopy(app->gRenderer, image, NULL, &texr);
}

/**
 *
 */
void tp2Accueil_release(struct Application *app, void *state) {
  struct Menu *menu = (struct Menu*) state;
  int i;
  for (i = 0; i < 9; ++i) {
    SDL_DestroyTexture(menu->tabImages[i]);
    menu->tabImages[i] = NULL;
  }
  tp2Sound_freeShort(menu->choiceSound);
  tp2Sound_freeLong(menu->backMusic);
  free(menu);
}
