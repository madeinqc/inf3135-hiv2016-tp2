Grille de correction
====================

Partie 1
--------

(Date de remise : au plus tard le **11 mars 2016**)

+-------------------------+-----------+-----------+
| Critère                 | Résultat  | Sur       |
+=========================+===========+===========+
| Exécutable minimal      | 10        | 10        |
+-------------------------+-----------+-----------+
| Makefile                | 10        | 10        |
+-------------------------+-----------+-----------+
| Division des tâches     | 20        | 20        |
+-------------------------+-----------+-----------+
| **Total**               | **40**    | **40**    |
+-------------------------+-----------+-----------+

Commentaires
------------

Impeccable. Cependant, j'ai dû modifier les inclusions des bibliothèques SDL
(aucune pénalité, car c'est ma faute) : elles sont exactement les mêmes que
pour Linux. Par conséquent, votre fichier ``sdl2.h`` devrait être simplement::

    #ifndef SDL2_h
    #define SDL2_h
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_mixer.h>
    #endif

Partie 2
--------

(Date de remise : au plus tard le **1er avril 2016**)

+-------------------------+----------------------------+-----------+-----------+
| Critère                 | Sous-critère               | Résultat  | Sur       |
+=========================+============================+===========+===========+
|                         | Lecture du format TMX      |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Affichage graphique        |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Gestion des jauges         |           | 10        |
|                         +----------------------------+-----------+-----------+
| Fonctionnabilité        | Déplacement du personnage  |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Gestion des collisions     |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Gestion des événements     |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Accueil, menu, quitter,    |           | 10        |
|                         | niveau de difficulté, etc. |           |           |
+-------------------------+----------------------------+-----------+-----------+
|                         | Modularité                 |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Style de programmation     |           | 10        |
| Qualité du code         +----------------------------+-----------+-----------+
|                         | Documentation (en-tête du  |           | 10        |
|                         | fichier et des fonctions)  |           |           |
+-------------------------+----------------------------+-----------+-----------+
|                         | Compilation et nettoyage   |           | 10        |
| Makefile                +----------------------------+-----------+-----------+
|                         | Documentation et tests     |           | 5         |
+-------------------------+----------------------------+-----------+-----------+
|                         | Commits significatifs      |           | 10        |
| Utilisation de Git      +----------------------------+-----------+-----------+
|                         | Qualité des messages de    |           | 5         |
|                         | commits                    |           |           |
+-------------------------+----------------------------+-----------+-----------+
|                         | Équité du travail          |           | 10        |
|                         +----------------------------+-----------+-----------+
| Travail individuel      | Tâches complétées          |           | 10        |
|                         +----------------------------+-----------+-----------+
|                         | Qualité du code            |           | 10        |
+-------------------------+----------------------------+-----------+-----------+
| **Total**                                            |           | **160**   |
+-------------------------+----------------------------+-----------+-----------+
