#ifndef ENEMIES_H
#define ENEMIES_H

#include <Adafruit_ILI9341.h>
#include "graphics.h"
#include "levels.h"
extern Adafruit_ILI9341 tft;
extern int selectedLevel;

#include "images/drone/drone-1.h"
#include "images/drone/drone-2.h"
#include "images/drone/drone-3.h"
#include "images/tank/tank-1.h"
#include "images/tank/tank-2.h"
#include "images/tank/tank-3.h"

static const tImage* droneFrames[3] = { &drone1, &drone2, &drone3 };
static const tImage* tankFrames[3]  = { &tank1,  &tank2,  &tank3  };

struct Enemy {
  int x, y, type, frame;
  unsigned long lastFrame;
  bool drawn;
};

static const int MAX_ENEMIES = 5;
static int   enemyCount = 0;
static Enemy enemies[MAX_ENEMIES];

static void drawEnemyFrame(Enemy& e) {
  const tImage* img = (e.type == 0) ? droneFrames[e.frame] : tankFrames[e.frame];
  int w = img->width;
  int h = img->height;
  const uint16_t* pixels = img->data;
  for (int yy = 0; yy < h; yy++)
    for (int xx = 0; xx < w; xx++) {
      uint16_t c = pixels[yy * w + xx];
      if (c != 0x0000) tft.drawPixel(e.x + xx, e.y + yy, c);
    }
}

void updateEnemies() {
  unsigned long now = millis();
  for (int i = 0; i < enemyCount; i++) {
    Enemy& e = enemies[i];
    if (!e.drawn) {
      drawEnemyFrame(e);
      e.drawn = true;
      continue;
    }
    if (now - e.lastFrame >= 120) {
      e.lastFrame = now;
      e.frame = (e.frame + 1) % 3;
      drawEnemyFrame(e);
    }
  }
}

#endif