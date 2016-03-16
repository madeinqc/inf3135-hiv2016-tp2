/**
 * @file
 * Le module TP2 est le module par défaut.
 * C'est lui qui s'occupe du chargement, de la boucle de jeu et de la fermeture.
 */

#include "tp2_acceuil.h"

int main() {
  struct Application app;
  if (initialize(&app)) {
    loadMedia(&app);
    gameLoop(&app);
    shutDown(&app);
  } else {
    printf("Could not initialize SDL");
  }
}
