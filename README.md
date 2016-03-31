# Travail pratique 2

## Description

Ce projet est un jeu en vue isométrique où un personnage nommé Bob doit miner toutes les pierres dans une carte sans manquer d'eau, de nourriture ou de sommeil. Ce projet est un travail réaliser pour monsieur *Alexandre Blondin Massé* dans le cadre du cours *INF3135 - Construction et maintenance de logiciel*  réalisé à l'*Université du Québec à Montréal*.
Tout le code est réalisé en *C* à l'exception d'un validateur de carte qui sera réalisé en *Python*.

Ce projet utilise le système de branchage [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/). Les versions officielles sont toutes sur la branche **master** avec un **tag** et les versions en développement sont sur la branche **develop**.

## Auteur(s)

- Giulia Cantoni (CANG21529205)
- Samuel Pilon (PILS01059008)
- Marc-Antoine Sauvé (SAUM13119008)

## Dépendances

- SDL 2.0.4
- SDL2 Image 2.0.1
- SDL2 Mixer 2.0.1
- SDL2 ttf 2.0.13
- Doxygen 1.8.11
- TMX C Loader [476ac9b](https://github.com/baylej/tmx/commit/476ac9b6f84278af89dadb2ccc4131caaa855ffd)
- libxml2 2.9.3
- zlib 1.2.8

## Fonctionnement

Le projet se maintient grâce à un Makefile qui permet de compiler, générer la documentation et de nettoyer le projet.

**Compiler:**
```make```

**Exécuter:**
```./tp2```

**Générer la documentation:**
```make doc```

**Nettoyer le projet:**
```make clean```

## Plateformes supportées

- Mac OS X El Capitan V.10.11.3
- Arch Linux 4.4.1-2-ARCH
- Kali Linux 4.0.0-kalil-amd64
- Ubuntu 14.04.4 LTS

## Contenu du projet

- `config.doxygen` : Contient la configuration doxygen pour générer la documentation;
- `grille.rst` : Grille de correction;
- `Makefile` : Fichier Makefile pour compiler, tester, nettoyer et générer la documentation du projet;
- `README.md` : Ceci est ce fichier. Explique le projet et les informations associées;
- `sdl2.h` : Inclue les fichiers requis pour la librarie SDL2;
- `tp2_accueil.c/tp2_accueil.h` : Fichier pour la scène du menu d'accueil;
- `tp2_application.h` : Fichier définissant la struct Application utilisée pour conserver l'état global de l'application;
- `tp2.c` : Point d'entrée qui appelle les fonctions nécessaire à l'initialisation de l'application;
- `tp2_image.c/tp2_image.h` : Module d'aide pour la gestion des images;
- `tp2_scene.h` : Fichier définissant la struct Scene utilisé pour simuler un polymorphisme pour les scènes;
- `tp2_sound.c/tp2_sound.h` : Module d'aide pour la gestion des sons;
- `tp2_window.c/tp2_window.h` : Module contenant la création de la fenêtre et la gestion de la boucle de jeu;

## Division des tâches

- [X] (2) Créer le makefile (Marc-Antoine Sauvé)
- [X] (5) Créer le squelette de l'application (fenêtre vide) (Marc-Antoine Sauvé)
- [X] (3) Design du menu d'accueil (En groupe)
- [X] (5) Gestion des événements du menu d'accueil (Samuel Pilon)
- [ ] (5) Créer le menu de pause (Giulia Cantoni)
- [ ] (8) Créer des cartes de test (Samuel Pilon)
- [X] (5) Chargement aléatoire d'une carte / lecture TMX (Marc-Antoine Sauvé)
- [X] (8) Mise à jour des structures de cartes selon le chargement de la carte TMX (Marc-Antoine Sauvé)
- [ ] (3) Gestion des collisions et des cases marchable (Samuel Pilon)
- [ ] (5) Gestion des transitions entre cartes (Samuel Pilon)
- [ ] (8) Création de Drawables qui savent se dessiner/charger/libérer (Samuel Pilon)
- [X] (8) Création de Scenes pour gérer les Drawable et les Event SDL (Marc-Antoine Sauvé)
- [ ] (8) Gestion des animations et mouvement du personnage et animation d'escalier (Samuel Pilon)
- [ ] (5) Gestion de la condition de victoire et de défaite et message approprié (Giulia Cantoni)
- [ ] (8) Minage des pierres, boire de l'eau et dormir (animation/actions/vérification) (Giulia Cantoni)
- [ ] (5) Gestion des jauges (Giulia Cantoni)
- [ ] (5) Chargement des cartes en python (Giulia Cantoni)
- [ ] (8) Tests automatisés pour les cartes (Giulia Cantoni)

## Références

- Documentation Doxygen: https://www.stack.nl/~dimitri/doxygen/manual/index.html
- SDL Wiki: https://wiki.libsdl.org/FrontPage

## Statut

Projet en développement
Menu d'acceuil fonctionnel pour quitter
Compilable sans erreurs et sans warnings
