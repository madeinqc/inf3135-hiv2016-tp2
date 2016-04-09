#include "tp2_jauge.h"

struct Jauge* createJauge(char *tabImages[8], struct Application* app){
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
	}
	return newJauge; 
}

void deleteJauge(struct Jauge *jauge, struct Application* app){
	free(jauge); 
}

void renderJauge(struct Jauge *jauge, struct Application* app){

}

void moveJauge(struct Jauge *jauge, int direction){

}

void handleEventsJauge(struct Jauge *jauge, SDL_Event *event, struct Application *app){
	
}