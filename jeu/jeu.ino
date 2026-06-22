#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>

#include "src/graphics.h"
#include "src/movement.h"
#include "src/portal.h"
#include "src/enemies.h"
#include "src/levels.h"
#include "src/audio.h"
#include "src/menu.h"
#include "src/game.h"

#define TFT_CS 5
#define TFT_DC 22
#define TFT_RST 21
#define TFT_MOSI 23
#define TFT_CLK 18
#define TFT_MISO 19

#define BTN_LEFT 15
#define BTN_RIGHT 4
#define BTN_UP 17
#define BTN_DOWN 5

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

enum GameState { STATE_MENU,
                 STATE_PLAYING,
                 STATE_WIN,
                 STATE_GAMEOVER };
GameState currentState = STATE_MENU;

bool winScreenShown = false;
bool gameOverScreenShown = false;
bool menuShown = false;

void slideTransitionUp() {
  for (int y = 0; y <= 240; y += 10) {
    tft.fillRect(0, 240 - y, 320, 10, ILI9341_BLACK);
    delay(5);
  }
}

void setup() {
  pinMode(BTN_LEFT, INPUT);
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_UP, INPUT);
  pinMode(BTN_DOWN, INPUT);

  tft.begin(20000000);
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  initGraphics(&tft);
  initGame();
  initPortal();
  initAudio();
}

void loop() {
  switch (currentState) {

    case STATE_MENU:
      if (!menuShown) {
        tft.fillScreen(ILI9341_WHITE);
        drawMenuStatic();
        drawLevelNumber();
        playMenuMusic();
        menuShown = true;
      }

      updateMenu();
      updateAudio();

      if (!digitalRead(BTN_RIGHT)) {
        while (!digitalRead(BTN_RIGHT))
          ;
        playValidateSound();
        slideTransitionUp();

        selectedLevel = getMenuLevel();
        stopMusic();
        resetGame();
        initMovement();
        initPortal();

        tft.fillScreen(ILI9341_BLACK);
        drawLevelBackground();
        loadLevel(selectedLevel);

        Level& L = levels[selectedLevel - 1];
        for (int i = 0; i < L.obstacleCount; i++) {
          drawObstacle(L.obstacleX[i], L.obstacleY[i], L.obstacleType[i]);
        }

        drawLifeBar();
        menuShown = false;
        currentState = STATE_PLAYING;
        delay(200);
      }
      break;

    case STATE_PLAYING:
      updateGame();
      updateAudio();

      if (!digitalRead(BTN_LEFT)) startMove(-1, 0);
      if (!digitalRead(BTN_RIGHT)) startMove(1, 0);
      if (!digitalRead(BTN_UP)) startMove(0, 1);
      if (!digitalRead(BTN_DOWN)) startMove(0, -1);

      if (playerWon) {
        currentState = STATE_WIN;
        delay(300);
      }
      if (lives <= 0) {
        currentState = STATE_GAMEOVER;
        delay(300);
      }
      break;

    case STATE_WIN:
      if (!winScreenShown) {
        drawWinScreen();
        stopMusic();
        playWinMusic();
        winScreenShown = true;
      }
      if (!digitalRead(BTN_RIGHT)) {
        while (!digitalRead(BTN_RIGHT))
          ;
        playerWon = false;
        menuShown = false;
        winScreenShown = false;
        currentState = STATE_MENU;
        delay(200);
      }
      break;

    case STATE_GAMEOVER:
      if (!gameOverScreenShown) {
        drawGameOverScreen();
        stopMusic();
        playGameOverMusic();
        gameOverScreenShown = true;
      }
      if (!digitalRead(BTN_RIGHT)) {
        while (!digitalRead(BTN_RIGHT))
          ;
        lives = 3;
        playerWon = false;
        menuShown = false;
        gameOverScreenShown = false;
        currentState = STATE_MENU;
        delay(200);
      }
      break;
  }
}
