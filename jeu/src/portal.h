#ifndef PORTAL_H
#define PORTAL_H

#include <Adafruit_ILI9341.h>
#include "graphics.h"
extern Adafruit_ILI9341 tft;

#include "images/portal/FendaN4-1.h"
#include "images/portal/FendaN4-2.h"
#include "images/portal/FendaN4-3.h"
#include "images/portal/FendaN4-4.h"
#include "images/portal/FendaN4-5.h"
#include "images/portal/FendaN4-6.h"
#include "images/portal/FendaN4-7.h"
#include "images/portal/FendaN4-8.h"

const tImage* portalFrames[8] = {
  &FendaN41, &FendaN42, &FendaN43, &FendaN44,
  &FendaN45, &FendaN46, &FendaN47, &FendaN48
};

int           portalFrame    = 0;
unsigned long lastPortalTime = 0;
const int     PORTAL_INTERVAL = 125;
bool          portalDrawn    = false;

int portalX = GRID_OFFSET_X + 6 * TILE_SIZE;
int portalY = GRID_OFFSET_Y + 2 * TILE_SIZE;

void initPortal() {
  portalFrame    = 0;
  lastPortalTime = millis();
  portalDrawn    = false;
}

static void drawPortalFrame() {

  const tImage*   img    = portalFrames[portalFrame];
  int             w      = img->width;
  int             h      = img->height;
  const uint16_t* pixels = img->data;

  for (int yy = 0; yy < h; yy++)
    for (int xx = 0; xx < w; xx++) {
      uint16_t c = pixels[yy * w + xx];
      if (c != 0x0000) tft.drawPixel(portalX + xx, portalY + yy, c);
    }
}

void updatePortalAnimation() {
  if (!portalDrawn) {
    drawPortalFrame();
    portalDrawn = true;
    return;
  }

  unsigned long now = millis();
  if (now - lastPortalTime >= PORTAL_INTERVAL) {
    lastPortalTime = now;
    portalFrame = (portalFrame + 1) % 8;
    drawPortalFrame();
  }
}

#endif