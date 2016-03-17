/**
 * @file
 * Description a venir...
 *
*/
#include "tp2_sound.h"

Mix_Chunk* loadShortSound(const char *pathToSound){
	Mix_Chunk* shortSound = Mix_LoadWAV(pathToSound);
	if(shortSound == NULL){
		printf("Sound could not be loaded! SDL_Error: %s\n", Mix_GetError());
		return NULL;
	}
	return shortSound;
}

void playShortSound(Mix_Chunk* toPlay){
	if(Mix_PlayChannel(-1, toPlay, 0)){
		printf("Sound could not be played! SDL_Error: %s\n", Mix_GetError());
	}
}