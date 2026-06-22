# Mario Bytes — Console de jeu embarquée

### Jeu développé sur ESP32 + écran ILI9341

---

## Présentation

Mario Bytes est un jeu embarqué développé sur **ESP32**, affiché sur un écran **TFT ILI9341**, avec :

- un personnage animé
- des obstacles
- des ennemis animés
- un portail de fin
- un système de vies
- un menu interactif
- des sons et musiques via buzzer

Le projet est entièrement codé en C++ (Arduino) et organisé en modules indépendants pour une meilleure lisibilité.

---

## Architecture du code

Le dossier `src/` contient tous les modules du jeu :

src/
├── audio.h        → Gestion du buzzer, musiques, sons
├── config.h       → Définition des boutons
├── enemies.h      → Gestion et animation des ennemis
├── game.h         → Logique du jeu (vies, collisions, états)
├── graphics.h     → Affichage (robot, obstacles, fond, vie)
├── levels.h       → Données des 3 niveaux
├── menu.h         → Menu principal (choix du niveau)
├── movement.h     → Déplacements + animations du robot
├── portal.h       → Portail animé
└── images/...     → Sprites convertis en RGB565

Chaque fichier gère une partie précise du jeu, ce qui rend le code clair, modulaire et facile à maintenir.

---

## Description des modules

### `audio.h` — Sons & musiques

- Gère le buzzer (GPIO 25)
- Musique du menu
- Musiques des niveaux
- Sons : validation, dégâts, portail, victoire, game over
- Fonctionnement basé sur `tone()` + timing interne

Fonctions clés :  
`playMenuMusic()`, `playLevelMusic()`, `playDamageSound()`, `playWinMusic()`, `updateAudio()`

---

### `game.h` — Logique du jeu

- Gestion des vies
- Détection de victoire / game over
- Chargement des niveaux
- Mise à jour globale du jeu

Fonctions clés :  
`initGame()`, `resetGame()`, `loadLevel()`, `updateGame()`, `checkCollisions()`

---

### `movement.h` — Déplacements du robot

- Déplacement par tuiles
- Animation du robot (4 frames)
- Interpolation fluide (4 steps)
- Gestion des collisions

Fonctions clés :  
`startMove(dx, dy)`, `updateMovement()`

---

### `portal.h` — Portail animé

- Animation sur 8 frames
- Détection de contact
- Affichage pixel par pixel

Fonctions clés :  
`initPortal()`, `updatePortalAnimation()`

---

### `enemies.h` — Ennemis animés

- Deux types d’ennemis : drone et tank
- Animation sur 3 frames
- Affichage pixel par pixel
- Gestion du tableau d’ennemis

Fonction clé :  
`updateEnemies()`

---

### `graphics.h` — Affichage général

- Dessin du robot
- Dessin des obstacles
- Fond du niveau
- Barre de vie
- Sprites RGB565

Fonctions clés :  
`drawRobot()`, `drawObstacle()`, `drawLevelBackground()`, `drawLifeBar()`

---

### `levels.h` — Données des niveaux

Contient les données des 3 niveaux :

- position de départ
- position du portail
- ennemis (type + position)
- obstacles (type + position)

---

### `menu.h` — Menu principal

- Affichage du titre
- Sélection du niveau
- Navigation avec boutons
- Validation avec bouton droite

Fonctions clés :  
`drawMenuStatic()`, `drawLevelNumber()`, `updateMenu()`, `getMenuLevel()`

---

## Programme principal (`.ino`)

Le fichier principal gère :

### L’initialisation

- écran ILI9341
- boutons
- audio
- modules du jeu

### La machine à états

STATE_MENU
STATE_PLAYING
STATE_WIN
STATE_GAMEOVER

### La boucle principale

- Menu → choix du niveau
- Jeu → déplacements, collisions, animations
- Victoire → écran + musique
- Game Over → écran + musique

---

## Matériel utilisé

- ESP32 Dev Module
- Écran ILI9341 (SPI)
- Buzzer
- Boutons GPIO
- Boîtier 3D imprimé

---

## Compilation & Upload (Arduino IDE)

1. Installer les bibliothèques :
   - **Adafruit_GFX**
   - **Adafruit_ILI9341**

2. Sélectionner la carte :
   ESP32 Dev Module

3. Sélectionner le port COM

4. Compiler & téléverser

---

## Personnalisation

Vous pouvez modifier :

- les musiques → `audio.h`
- les niveaux → `levels.h`
- les sprites → `images/`
- la vitesse d’animation
- la difficulté (ennemis, obstacles)
- les couleurs de l’écran

---

## Licence

Projet étudiant — utilisation libre pour apprentissage.
