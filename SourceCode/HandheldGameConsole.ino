/*
NOTE: VARIABLE NAME, FUNCTION NAME
    Belong to game: main target + game name + sub target
      Ex: bestMazeEasy
    Var in function: variable name + Tmp
      Ex: resultTmp
    Use common: normal
      Ex: tft
*/

#include "Common.h"
#include "FlappyBird.h"
#include "Maze.h"
#include "Ponk.h"
#include "SnakeWind.h"
#include "TankWar.h"
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

  bestFlappyBird = EEPROM.read(addressBestFlappyBird);

  bestMazeEasy = EEPROM.read(addressBestMazeEasy);
  bestMazeMedium = EEPROM.read(addressBestMazeMedium);
  bestMazeHard = EEPROM.read(addressBestMazeHard);

  bestPonkEasy = EEPROM.read(addressBestPonkEasy);
  bestPonkMedium = EEPROM.read(addressBestPonkMedium);
  bestPonkHard = EEPROM.read(addressBestPonkHard);

  bestSnakeWindFreeEasy = EEPROM.read(addressBestSnakeWindFreeEasy);
  bestSnakeWindFreeMedium = EEPROM.read(addressBestSnakeWindFreeMedium);
  bestSnakeWindFreeHard = EEPROM.read(addressBestSnakeWindFreeHard);
  bestSnakeWindHomeEasy = EEPROM.read(addressBestSnakeWindHomeEasy);
  bestSnakeWindHomeMedium = EEPROM.read(addressBestSnakeWindHomeMedium);
  bestSnakeWindHomeHard = EEPROM.read(addressBestSnakeWindHomeHard);
  bestSnakeWindParkEasy = EEPROM.read(addressBestSnakeWindParkEasy);
  bestSnakeWindParkMedium = EEPROM.read(addressBestSnakeWindParkMedium);
  bestSnakeWindParkHard = EEPROM.read(addressBestSnakeWindParkHard);

  bestTankWar = EEPROM.read(addressBestTankWar);

  selectGame();
}

// Handheld game console actives
void loop() {
  int resultCommonTmp;
  if (flag) resultCommonTmp = switchNewGame();
  else resultCommonTmp = switchContinue();

  if (resultCommonTmp) {
    flag = true;
    if (selectTwo(true, "NEW GAME", "OTHER GAME") == 2) selectGame();
  } else {
    int resultPauseTmp = selectThree("CONTINUE", "NEW GAME", "OTHER GAME");
    if (resultPauseTmp == 0) flag = false;
    else {
      flag = true;
      if (resultPauseTmp == 2) selectGame();
    }
  }
}