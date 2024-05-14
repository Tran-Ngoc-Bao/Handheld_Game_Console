#include "Common.h"
#include "FlappyBird.h"
#include "Maze.h"
#include "Ponk.h"
#include "SnakeWind.h"
#include "TankWar.h"
#include "Pause.h"
#include "GameOver.h"
#include "SelectGame.h"

void setup() {
  pinMode(top, INPUT);
  pinMode(bottom, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(enter, INPUT);
  pinMode(pau, INPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  tft.begin();
  tft.setRotation(2);

  EEPROM.begin(5);
  bestFlappyBird = EEPROM.read(0);
  bestMaze = EEPROM.read(1);
  bestPonk = EEPROM.read(2);
  bestSnakeWind = EEPROM.read(3);
  bestTankWar = EEPROM.read(4);

  selectGame();
}

void loop() {
  int resCommon;
  if (flag) resCommon = switchNewGame();
  else resCommon = switchContinue();

  if (resCommon) {
    flag = true;
    if (gameOver(commonScore) == 2) selectGame();
  } else {
    int resPause = pause();
    if (resPause == 0) flag = false;
    else {
      flag = true;
      if (resPause == 2) selectGame();
    }
  }
}