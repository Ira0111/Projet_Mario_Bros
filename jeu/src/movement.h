#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "graphics.h"
#include "portal.h"
#include "levels.h"
#include "enemies.h"
#include "config.h"
#include "audio.h"

int robotX    = GRID_OFFSET_X;
int robotY    = GRID_OFFSET_Y;
int displayX  = GRID_OFFSET_X;
int displayY  = GRID_OFFSET_Y;
int prevDisplayX = GRID_OFFSET_X;
int prevDisplayY = GRID_OFFSET_Y;

bool isMoving   = false;
bool robotDrawn = false;

#define MAX_STEPS 4
int stepIndex = 0;
int startX, startY, endX, endY;

int robotFrame = 0;
unsigned long lastFrameTime = 0;
const int FRAME_INTERVAL = 70;

void initMovement() {
  robotX   = GRID_OFFSET_X;
  robotY   = GRID_OFFSET_Y;
  displayX = robotX;
  displayY = robotY;
  isMoving   = false;
  robotDrawn = false;
}

void startMove(int dx, int dy) {
  if (isMoving) return;

  int tileX = (robotX - GRID_OFFSET_X) / TILE_SIZE;
  int tileY = (robotY - GRID_OFFSET_Y) / TILE_SIZE;
  int targetTileX = tileX + dx;
  int targetTileY = tileY + dy;

  if (targetTileX < 0 || targetTileX >= GRID_COLS) return;
  if (targetTileY < 0 || targetTileY >= GRID_ROWS) return;

  if (dx != 0) direction = (dx < 0) ? 1 : -1;

  Level& L = levels[selectedLevel - 1];
  int nextX = robotX + dx * TILE_SIZE;
  int nextY = robotY + dy * TILE_SIZE;

  for (int i = 0; i < L.obstacleCount; i++) {
    if (nextX == L.obstacleX[i] && nextY == L.obstacleY[i]) {
      lives--;
      playDamageSound();
      drawLifeBar();
      eraseRobotSprite(displayX, displayY);
      drawRobot(displayX, displayY, 0);
      robotDrawn = true;
      return;
    }
  }

  for (int i = 0; i < enemyCount; i++) {
    if (abs(nextX - enemies[i].x) < TILE_SIZE &&
        abs(nextY - enemies[i].y) < TILE_SIZE) {
      lives--;
      playDamageSound();
      drawLifeBar();
      eraseRobotSprite(displayX, displayY);
      drawRobot(displayX, displayY, 0);
      robotDrawn = true;
      return;
    }
  }

  startX = robotX;
  startY = robotY;
  endX   = robotX + dx * TILE_SIZE;
  endY   = robotY + dy * TILE_SIZE;

  stepIndex     = 0;
  isMoving      = true;
  robotDrawn    = false;
  robotFrame    = 0;
  lastFrameTime = millis();
}

void updateMovement() {
  if (!isMoving) {
    if (!robotDrawn) {
      drawRobot(displayX, displayY, 0);
      robotDrawn = true;
    }
    return;
  }

  prevDisplayX = displayX;
  prevDisplayY = displayY;

  float t  = (float)stepIndex / (float)MAX_STEPS;
  displayX = startX + (int)((endX - startX) * t);
  displayY = startY + (int)((endY - startY) * t);

  unsigned long now = millis();
  if (now - lastFrameTime >= FRAME_INTERVAL) {
    lastFrameTime = now;
    robotFrame = (robotFrame + 1) % 4;
  }

  if (robotDrawn) eraseRobotSprite(prevDisplayX, prevDisplayY);

  drawRobot(displayX, displayY, robotFrame);
  robotDrawn = true;

  stepIndex++;

  if (stepIndex > MAX_STEPS) {
    robotX   = endX;
    robotY   = endY;
    displayX = robotX;
    displayY = robotY;
    isMoving   = false;
    robotFrame = 0;
    robotDrawn = false;
  }
}

#endif