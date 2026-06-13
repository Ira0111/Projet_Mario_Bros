#ifndef GAME_H
#define GAME_H

#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "movement.h"
#include "portal.h"
#include "enemies.h"
#include "levels.h"
#include "audio.h"
extern Adafruit_ILI9341 tft;

int  lives       = 3;
bool playerWon   = false;
int  selectedLevel = 1;

void initGame() {
  lives     = 3;
  playerWon = false;
}

void resetGame() {
  initMovement();
  playerWon = false;
  lives     = 3;
}

void loadLevel(int id) {
  Level& L = levels[id - 1];

  robotX   = L.startX;
  robotY   = L.startY;
  displayX = robotX;
  displayY = robotY;

  portalX = L.portalX;
  portalY = L.portalY;
  initPortal();

  enemyCount = L.enemyCount;
  for (int i = 0; i < enemyCount; i++) {
    enemies[i] = { L.enemyX[i], L.enemyY[i], L.enemyType[i], 0, 0, false };
  }
}

void checkCollisions() {
  if (abs(robotX - portalX) < TILE_SIZE && abs(robotY - portalY) < TILE_SIZE) {
    playPortalTouchSound();
    playerWon = true;
  }
}

void drawWinScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setCursor(80, 100);
  tft.print("VICTOIRE !");
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(40, 180);
  tft.print("Appuyez sur droite");
}

void drawGameOverScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.setCursor(70, 100);
  tft.print("GAME OVER");
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(40, 180);
  tft.print("Appuyez sur droite");
}

void updateGame() {
  if (!musicPlaying) playLevelMusic();
  updateMovement();
  updatePortalAnimation();
  updateEnemies();
  checkCollisions();
}

#endif