#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Adafruit_ILI9341.h>
#include "images/timage.h"
#include "images/ui/sol.h"
#include "images/obstacles/obstacle1.h"
#include "images/obstacles/obstacle2.h"
#include "images/obstacles/obstacle3.h"
#include "images/ui/life.h"
#include "images/robot/robotframe-1.h"
#include "images/robot/robotframe-2.h"
#include "images/robot/robotframe-3.h"
#include "images/robot/robotframe-4.h"

extern Adafruit_ILI9341 tft;
extern int lives;

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define TILE_SIZE  36
#define GRID_COLS   8
#define GRID_ROWS   5

#define GRID_WIDTH  (GRID_COLS * TILE_SIZE)
#define GRID_HEIGHT (GRID_ROWS * TILE_SIZE)

#define GRID_OFFSET_X ((SCREEN_WIDTH - GRID_WIDTH) / 2)
#define GRID_OFFSET_Y 0

#define ROBOT_WIDTH  36
#define ROBOT_HEIGHT 36

#define ROBOT_OFFSET_X 0
#define ROBOT_OFFSET_Y 0

int direction = -1;

const tImage* robotFrames[4] = {
  &robotframe1, &robotframe2, &robotframe3, &robotframe4
};

void initGraphics(Adafruit_ILI9341* screen) {}

void drawTileOpaque(int x, int y, const tImage* img) {
  tft.drawRGBBitmap(x, y, img->data, img->width, img->height);
}

void drawTileTransparent(int x, int y, const tImage* img) {
  int w = img->width;
  int h = img->height;
  const uint16_t* pixels = img->data;
  for (int yy = 0; yy < h; yy++)
    for (int xx = 0; xx < w; xx++) {
      uint16_t c = pixels[yy * w + xx];
      if (c != 0x0000) tft.drawPixel(x + xx, y + yy, c);
    }
}

void drawTileBackgroundAt(int x, int y) {
  drawTileOpaque(x, y, &sol);
}

void drawRobot(int x, int y, int frame) {
  const tImage* img = robotFrames[frame];
  int w = img->width;
  int h = img->height;
  const uint16_t* pixels = img->data;

  for (int yy = 0; yy < h; yy++) {
    for (int xx = 0; xx < w; xx++) {
      int srcX = (direction == 1) ? xx : (w - 1 - xx);
      uint16_t c = pixels[yy * w + srcX];
      if (c != 0x0000) tft.drawPixel(x + xx, y + yy, c);
    }
  }
}

void eraseRobotSprite(int x, int y) {
  tft.drawRGBBitmap(x, y, sol.data, sol.width, sol.height);
}

void drawLevelBackground() {
  for (int row = 0; row < GRID_ROWS; row++)
    for (int col = 0; col < GRID_COLS; col++)
      drawTileOpaque(GRID_OFFSET_X + col * TILE_SIZE, GRID_OFFSET_Y + row * TILE_SIZE, &sol);
}

void drawLifeBar() {
  int baseX = GRID_OFFSET_X;
  int baseY = GRID_OFFSET_Y + GRID_HEIGHT + 4;
  tft.fillRect(baseX, baseY, 200, life.height, ILI9341_BLACK);
  for (int i = 0; i < lives; i++)
    drawTileTransparent(baseX + i * (life.width + 4), baseY, &life);
}

void drawObstacle(int x, int y, int type) {
  switch (type) {
    case 0: drawTileTransparent(x, y, &obstacle1); break;
    case 1: drawTileTransparent(x, y, &obstacle2); break;
    case 2: drawTileTransparent(x, y, &obstacle3); break;
  }
}

void flashRobotRed(int x, int y) {
  tft.fillRect(x, y, ROBOT_WIDTH, ROBOT_HEIGHT, ILI9341_RED);
}

#endif