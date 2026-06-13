#ifndef MENU_H
#define MENU_H

#include <Adafruit_ILI9341.h>

extern Adafruit_ILI9341 tft;
extern int selectedLevel;

#define BTN_LEFT 15
#define BTN_RIGHT 4
#define BTN_UP 17
#define BTN_DOWN 5

int menuLevel = 1;
const int minLevel = 1;
const int maxLevel = 3;
unsigned long lastInput = 0;
const int inputDelay = 150;
bool menuDrawn = false;

void drawMenuStatic() {
  tft.fillScreen(ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(60, 20);
  tft.print("MARIO BYTES");
  tft.setTextSize(2);
  tft.setCursor(70, 80);
  tft.print("Choisir niveau :");
  tft.setTextSize(2);
  tft.setCursor(40, 200);
  tft.print("Haut/Bas = changer");
  tft.setCursor(40, 220);
  tft.print("Droite = valider");
}

void drawLevelNumber() {
  tft.fillRect(110, 120, 120, 40, ILI9341_WHITE);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(3);
  tft.setCursor(130, 130);
  tft.print("^ ");
  tft.print(menuLevel);
  tft.print(" v");
}

void updateMenu() {

  unsigned long now = millis();
  if (now - lastInput < inputDelay) return;

  if (!digitalRead(BTN_UP)) {
    if (menuLevel < maxLevel) menuLevel++;
    drawLevelNumber();
    lastInput = now;
  }
  if (!digitalRead(BTN_DOWN)) {
    if (menuLevel > minLevel) menuLevel--;
    drawLevelNumber();
    lastInput = now;
  }
}

int getMenuLevel() {
  return menuLevel;
}

#endif