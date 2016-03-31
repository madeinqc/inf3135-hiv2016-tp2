#ifndef TP2_SCENE_H
#define TP2_SCENE_H

#include "sdl2.h"
#include "tp2_application.h"

struct Scene {
  void* (*initScene)(struct Application*);
  bool (*loadMedia)(struct Application*, void*);
  void (*viewWillAppear)(struct Application*, void*);
  bool (*handleEvents)(struct Application*, void*, SDL_Event*);
  void (*drawScene)(struct Application*, void*);
  void (*releaseMedia)(struct Application*, void*);
};

#endif