# Travail pratique 2

## Description

Ce projet est un jeu en vue isométrique où un personnage nommé Bob doit miner toutes les pierres dans une carte sans manquer d'eau, de nourriture ou de sommeil. Ce projet est un travail réaliser pour monsieur *Alexandre Blondin Massé* dans le cadre du cours *INF3135 - Construction et maintenance de logiciel*  réalisé à l'*Université du Québec à Montréal*.
Tout le code est réalisé en *C* à l'exception d'un validateur de carte qui sera réalisé en *Python*.

Ce projet utilise le systême de branchage [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/). Les versions officielles sont toutes sur la branche **master** avec un **tag** et les versions en développement sont sur la branche **develop**.

## Auteur(s)

- Giulia Cantoni (CANG21529205)
- Samuel Pilon (PILS01059008)
- Marc-Antoine Sauvé (SAUM13119008)

## Dépendances

- SDL 2.0.4
- SDL2 Image 2.0.1
- Doxygen 1.8.11

## Fonctionnement

Expliquez comment faire fonctionner votre projet :

- Comment le compiler;
- Comment l'exécuter;
- Comment le tester;
- Comment générer la documentation,
- etc.

## Plateformes supportées

- Mac OS X El Capitan V.10.11.3
- Arch Linux 4.4.1-2-ARCH
- Kali Linux 4.0.0-kalil-amd64

## Contenu du projet

Décrivez brièvement chacun des répertoires et modules contenus dans le
projet. Utilisez le format suivant :

- `nom du fichier1` : décrire le contenu du fichier1;
- `nom du fichier2` : décrire le contenu du fichier2;
- etc.

## Division des tâches

- [X] (2) Créer le makefile (Marc-Antoine Sauvé)
- [X] (5) Créer le squelette de l'application (fenêtre vide) (Marc-Antoine Sauvé)
- [ ] (3) Design du menu d'accueil (En groupe)
- [ ] (5) Gestion des événements du menu d'accueil (Samuel Pilon)
- [ ] (5) Créer le menu de pause (Giulia Cantoni)
- [ ] (8) Créer des cartes de test (Samuel Pilon)
- [ ] (5) Chargement aléatoire d'une carte / lecture TMX (Marc-Antoine Sauvé)
- [ ] (8) Mise à jour des structures de cartes selon le chargement de la carte TMX (Marc-Antoine Sauvé)
- [ ] (3) Gestion des collisions et des cases marchable (Samuel Pilon)
- [ ] (5) Gestion des transitions entre cartes (Samuel Pilon)
- [ ] (8) Création de Drawables qui savent se dessiner/charger/libérer (Samuel Pilon)
- [ ] (8) Création de Scenes pour gérer les Drawable et les Event SDL (Marc-Antoine Sauvé)
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
Compilable sans erreurs
