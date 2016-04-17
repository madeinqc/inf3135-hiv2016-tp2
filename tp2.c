/**
 * @file
 * Le module TP2 est le module par défaut.
 * C'est lui qui s'occupe du chargement, de la boucle de jeu et de la fermeture.
 */

#include "tp2_window.h"

int main() {

  char c[] = "c";
  char s[] = "lawl string";
  char *ss[] = {c, s};

  struct Application app = {NULL, NULL, NULL, NULL, NULL, true, NULL, NULL, false, false, false};
  if (initialize(&app)) {
    initMainScene(&app);
    gameLoop(&app);
    shutDown(&app);
  } else {
    printf("Could not initialize SDL");
  }
}
