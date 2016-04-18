/**
 * @file
 * Gestion d'une jauge générique. 
 *
*/

#include "tp2_jauge.h"

struct Jauge* tp2jauge_create(char *tabImages[8], int timespan, struct Application* app){
	struct Jauge *newJauge = (struct Jauge*)malloc(sizeof(struct Jauge)); 

	newJauge->state = 7; 
	int i;
	for (i = 0; i < 8; ++i) {
    SDL_Texture *image = tp2image_load(app, tabImages[i]);
    if(image == NULL){
      printf("Unable to load image %s! SDL Error : %s\n", tabImages[i], SDL_GetError());
      return false;
    }
	newJauge->tabImages[i] = image;
	newJauge->lastUpdate = SDL_GetTicks();  
	newJauge->timespan = timespan;
	}
	return newJauge; 
}

void tp2jauge_render(struct Jauge *jauge, struct Application* app){
	tp2jauge_update(jauge, app);
	int imageIndex = jauge->state;
	SDL_Texture *image = jauge->tabImages[imageIndex]; 
	SDL_Rect text = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(app->gRenderer, image, NULL, &text);  
}

void tp2jauge_update(struct Jauge *jauge, struct Application* app){
	int currentTime = SDL_GetTicks();
	if(app->isPause || app->isLost || app->isWon){
		jauge->lastUpdate = currentTime; 
	}
	if(currentTime > jauge->lastUpdate + jauge->timespan && jauge->state !=0){
		jauge->state -= 1; 
		jauge->lastUpdate = currentTime; 
	}
	if(jauge->state == 0){
		app->isLost = true;  
	}
}

void tp2jauge_refill(struct Jauge *jauge){
	jauge->state =7; 
	jauge->lastUpdate = SDL_GetTicks(); 
}

void tp2jauge_delete(struct Jauge *jauge, struct Application* app){
	free(jauge); 
}
