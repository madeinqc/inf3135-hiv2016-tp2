/**
 * @file
 * Description a venir...
 *
*/
#include "tp2_sound.h"

Mix_Chunk* loadShortSound(const char *pathToSound){
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(10);
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

void freeShortSound(Mix_Chunk* toFree){
	Mix_FreeChunk(toFree);
	Mix_Quit();
}