/**
 * @file
 * Fichier contenant les méthodes nécessaires au chargement des sons.
*/
#ifndef TP2_SOUND_H
#define TP2_SOUND_H

#include "tp2_sound.h"

void tp2Sound_openChannel() {
  Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
  Mix_AllocateChannels(10);
}

void tp2Sound_closeChannel() {
  Mix_Quit();
}

Mix_Chunk *tp2Sound_loadShort(const char *pathToSound) {
  Mix_Chunk *shortSound = Mix_LoadWAV(pathToSound);
  if (shortSound == NULL) {
    printf("Sound could not be loaded! SDL_Error: %s\n", Mix_GetError());
    return NULL;
  }
  return shortSound;
}

Mix_Music *tp2Sound_loadLong(const char *pathToSound) {
  Mix_Music *longSound = Mix_LoadMUS(pathToSound);
  if (longSound == NULL) {
    printf("Sound could not be loaded! SDL_Error: %s\n", Mix_GetError());
    return NULL;
  }
  Mix_VolumeMusic(30);
  return longSound;
}

void tp2Sound_playShort(Mix_Chunk *toPlay) {
  if (Mix_PlayChannel(-1, toPlay, 0)) {
    printf("Sound could not be played! SDL_Error: %s\n", Mix_GetError());
  }
}

void tp2Sound_playLong(Mix_Music *toPlay) {
  if (Mix_PlayMusic(toPlay, -1)) {
    printf("Sound could not be played! SDL_Error: %s\n", Mix_GetError());
  }
}

void tp2Sound_freeShort(Mix_Chunk *toFree) {
  Mix_FreeChunk(toFree);
}

void tp2Sound_freeLong(Mix_Music *toFree) {
  Mix_FreeMusic(toFree);
}

#endif
