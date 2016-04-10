/**
 * @file
 * Description a venir... 
 *
*/

#include "tp2_carte.h"

struct Scene* tp2Carte_getScene(struct Application *app) {
  struct Scene *scene = calloc(1, sizeof(struct Scene));

  scene->initScene = &tp2Carte_initScene;
  scene->loadMedia = &tp2Carte_loadMedia;
  scene->viewWillAppear = &tp2Carte_viewWillAppear;
  scene->handleEvents = &tp2Carte_handleEvents;
  scene->drawScene = &tp2Carte_draw;
  scene->releaseMedia = &tp2Carte_release;

  return scene;
}

void* tp2Carte_initScene(struct Application *app) {
  struct Carte* carte = calloc(1, sizeof(struct Carte));
  return carte;
}

/**
 * Charge les ressources graphiques en mémoire.
 * @param app Un pointeur vers la structure Application à utiliser.
 * @return True si le chargement a réussi.
 */
bool tp2Carte_loadMedia(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;

  tp2Sound_openChannel();
  carte->pickaxeSound = tp2Sound_loadShort(SOUND_PICKAXE);

  tp2tmx_loadRandomMap(app->gRenderer, carte);

  carte->xSection = 0;
  carte->ySection = 0;

  carte->maxXSection = (carte->map->height + 1)/ 15;
  carte->maxYSection = (carte->map->width + 1)/ 15;

  carte->pause = tp2Pause_getScene(app); 
  carte->sPause = carte->pause->initScene(app);
  carte->pause->loadMedia(app, carte->sPause);

  char *imagesFood[] = {FOOD_0, FOOD_1, FOOD_2, FOOD_3, FOOD_4, FOOD_5, FOOD_6, FOOD_7};
  char *imagesWater[] = {WATER_0, WATER_1, WATER_2, WATER_3, WATER_4, WATER_5, WATER_6, WATER_7};
  char *imagesSleep[] = {SLEEP_0, SLEEP_1, SLEEP_2, SLEEP_3, SLEEP_4, SLEEP_5, SLEEP_6, SLEEP_7};
  int timespanFood;
  int timespanWater;
  int timespanSleep;
  switch(app->diff){ // sets timespan accoring to the difficutly of the game chosen
    case 0: 
      timespanFood = 15000; // 15sec
      timespanWater = 10000; // 10sec
      timespanSleep = 20000; // 20sec
      break;
    case 1: 
      timespanFood = 10000;
      timespanWater = 10000; 
      timespanSleep = 10000; 
      break;
    case 2: 
      timespanFood = 10000; // 10sec 
      timespanWater = 5000; // 5sec
      timespanSleep = 10000; // 10sec
      break;
  } 
  carte->foodJauge = createJauge(imagesFood, timespanFood, app); 
  carte->waterJauge = createJauge(imagesWater, timespanWater, app); 
  carte->sleepJauge = createJauge(imagesSleep, timespanSleep, app); 

  if(!createSprite(IMG_PERSO, 4, 20, 20, 20, 0, 2, app)){
  	printf("Probleme lors de l'initialisation du personnage!");
  	return false;
  }
  carte->isSpriteInitialized = false;
  carte->sprite = app->currSprite;

  carte->background = tp2image_load(app, IMG_BACK);

  findSectionHouse(carte);

  return true;
}

void tp2Carte_viewWillAppear(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;
}

/**
 * 
 * @params app Un pointeur vers la structure Application à utiliser.
 * @return True si on commence le jeu, False si on quitte.
 */
bool tp2Carte_handleEvents(struct Application *app, void *state, SDL_Event *event) {
  struct Carte *carte = (struct Carte*) state;
  bool isConsumed = false;
  if(app->isPause){
  	return carte->pause->handleEvents(app, carte->sPause, event);
  }else{
  	isConsumed = handleEventsSprite(carte->sprite, event, app);
  }
  if(isConsumed) return true;
  switch(event->type){
    case SDL_KEYDOWN:
      switch(event->key.keysym.sym){
        case SDLK_q:
          carte->ySection -= carte->ySection == 0 ? 0 : 1;
          isConsumed = true;
          break;
        case SDLK_s:
          carte->ySection += carte->ySection == carte->maxYSection - 1 ? 0 : 1;
          isConsumed = true;
          break;
        case SDLK_a:
          carte->xSection += carte->xSection == carte->maxXSection - 1 ? 0 : 1;
          isConsumed = true;
          break;
        case SDLK_w:
          carte->xSection -= carte->xSection == 0 ? 0 : 1;
          isConsumed = true;
          break;
        // FOR TEST ONLY TO BE REMOVED
        case SDLK_f:
          refillJauge(carte->waterJauge, app); 
          break; 
        // **********************************
        case SDLK_ESCAPE:
          app->isPause = true; 
          break;
        case SDLK_RETURN:
          tp2Sound_playShort(carte->pickaxeSound);
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
void tp2Carte_draw(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;
  SDL_Rect texr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_Texture *texture = tp2tmx_renderMap(app->gRenderer, carte);
  SDL_RenderCopy(app->gRenderer, texture, NULL, &texr);
  renderJauge(carte->foodJauge, app); 
  renderJauge(carte->waterJauge, app); 
  renderJauge(carte->sleepJauge, app); 
  if(app->isPause){
  	carte->pause->drawScene(app, carte->sPause);
  }
  SDL_DestroyTexture(texture);
}

/**
 *
 */
void tp2Carte_release(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;
  tp2Sound_freeShort(carte->pickaxeSound);
  tp2tmx_mapFree(carte->map);
  carte->pause->releaseMedia(app, carte->sPause);
  carte->foodJauge = NULL; 
  carte->waterJauge = NULL; 
  carte->sleepJauge = NULL; 
  free(carte);
  deleteSprite(app->currSprite, app);
}
