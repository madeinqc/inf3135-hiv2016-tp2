#include "tp2_jauge.h"

struct Jauge* createJauge(char *tabImages[8], int timespan, struct Application* app){
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

void deleteJauge(struct Jauge *jauge, struct Application* app){
	free(jauge); 
}

void renderJauge(struct Jauge *jauge, struct Application* app){
	updateJauge(jauge, app); 
	int imageIndex = jauge->state; 
	SDL_Texture *image = jauge->tabImages[imageIndex]; 
	SDL_Rect text = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_RenderCopy(app->gRenderer, image, NULL, &text);  
}

void updateJauge(struct Jauge *jauge, struct Application* app){
	int currentTime = SDL_GetTicks();
	if(jauge->state ==0){
		app->isLost = true;  
	}
	if(currentTime > jauge->lastUpdate + jauge->timespan && jauge->state !=0){
		jauge->state -= 1; 
		jauge->lastUpdate = currentTime; 
	}
}

void refillJauge(struct Jauge *jauge, struct Application* app){
	jauge->state = 7; 
}