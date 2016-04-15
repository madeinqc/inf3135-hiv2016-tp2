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
  carte->snoringSound = tp2Sound_loadShort(SOUND_SNORING);
  carte->drinkSound = tp2Sound_loadShort(SOUND_DRINK);
  carte->gameMusic = tp2Sound_loadLong(MUSIC_GAME);

  tp2tmx_loadRandomMap(app->gRenderer, carte);

  carte->xSection = 0;
  carte->ySection = 0;

  carte->maxXSection = (carte->map->height + 1)/ 15;
  carte->maxYSection = (carte->map->width + 1)/ 15;

  carte->pause = tp2Pause_getScene(app); 
  carte->sPause = carte->pause->initScene(app);
  carte->pause->loadMedia(app, carte->sPause);

  carte->defaite = tp2Defaite_getScene(app); 
  carte->sDefaite = carte->defaite->initScene(app);
  carte->defaite->loadMedia(app, carte->sDefaite);
  app->isLost = false; 

  carte->victoire = tp2Victoire_getScene(app); 
  carte->sVictoire = carte->victoire->initScene(app);
  carte->victoire->loadMedia(app, carte->sVictoire);
  carte->allMined = false; 
  app->isWon = false; 

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

  // Detruire le personnage dans la map
  destroyElement(carte->map->ly_head->next, 127);

  findNbRocks(carte);

  return true;
}

void tp2Carte_viewWillAppear(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;
  Mix_VolumeMusic(5);
  tp2Sound_playLong(carte->gameMusic);
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
  }
  else if(app->isLost){
    return carte->defaite->handleEvents(app, carte->sDefaite, event);
  }
  else if(carte->allMined || app->isWon){
    app->isWon = true; 
    return carte->victoire->handleEvents(app, carte->sVictoire, event);
  }
  else{
  	isConsumed = handleEventsSprite(carte->sprite, event, app, carte);
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
        case SDLK_SPACE:
        	actions(carte);
          break;
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
  else if(app->isLost){
    carte->defaite->drawScene(app, carte->sDefaite);
  }
  else if(app->isWon){
    carte->victoire->drawScene(app, carte->sVictoire);
  }
  SDL_DestroyTexture(texture);
}

/**
 *
 */
void tp2Carte_release(struct Application *app, void *state) {
  struct Carte *carte = (struct Carte*) state;
  tp2Sound_freeShort(carte->pickaxeSound);
  tp2Sound_freeShort(carte->snoringSound);
  tp2Sound_freeShort(carte->drinkSound);
  tp2Sound_freeLong(carte->gameMusic);
  tp2tmx_mapFree(carte->map);
  carte->pause->releaseMedia(app, carte->sPause);
  carte->defaite->releaseMedia(app, carte->sDefaite);
  carte->victoire->releaseMedia(app, carte->sVictoire);
  carte->foodJauge = NULL; 
  carte->waterJauge = NULL; 
  carte->sleepJauge = NULL; 
  free(carte);
  deleteSprite(app->currSprite, app);
}
