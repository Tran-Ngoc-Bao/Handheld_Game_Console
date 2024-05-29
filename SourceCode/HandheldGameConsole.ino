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
#include "Player.h"
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

  EEPROM.begin(201);

  tft.begin();
  tft.setRotation(2);

  countPlayer = EEPROM.read(200);

  if (selectTwo(false, "WELCOME!", "OLD PLAYER") == 1) {
    enterPlayer();
    currentPlayer = (countPlayer - 1) * 25;
  } else if (countPlayer) currentPlayer = selectEight();
  else {
    enterPlayer();
    currentPlayer = (countPlayer - 1) * 25;
  }

  bestFlappyBird = EEPROM.read(currentPlayer + addressBestFlappyBird);

  bestMazeEasy = EEPROM.read(currentPlayer + addressBestMazeEasy);
  bestMazeMedium = EEPROM.read(currentPlayer + addressBestMazeMedium);
  bestMazeHard = EEPROM.read(currentPlayer + addressBestMazeHard);

  bestPonkEasy = EEPROM.read(currentPlayer + addressBestPonkEasy);
  bestPonkMedium = EEPROM.read(currentPlayer + addressBestPonkMedium);
  bestPonkHard = EEPROM.read(currentPlayer + addressBestPonkHard);

  bestSnakeWindFreeEasy = EEPROM.read(currentPlayer + addressBestSnakeWindFreeEasy);
  bestSnakeWindFreeMedium = EEPROM.read(currentPlayer + addressBestSnakeWindFreeMedium);
  bestSnakeWindFreeHard = EEPROM.read(currentPlayer + addressBestSnakeWindFreeHard);
  bestSnakeWindHomeEasy = EEPROM.read(currentPlayer + addressBestSnakeWindHomeEasy);
  bestSnakeWindHomeMedium = EEPROM.read(currentPlayer + addressBestSnakeWindHomeMedium);
  bestSnakeWindHomeHard = EEPROM.read(currentPlayer + addressBestSnakeWindHomeHard);
  bestSnakeWindParkEasy = EEPROM.read(currentPlayer + addressBestSnakeWindParkEasy);
  bestSnakeWindParkMedium = EEPROM.read(currentPlayer + addressBestSnakeWindParkMedium);
  bestSnakeWindParkHard = EEPROM.read(currentPlayer + addressBestSnakeWindParkHard);

  bestTankWar = EEPROM.read(currentPlayer + addressBestTankWar);

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
    int resultPauseTmp = selectThree(true, "CONTINUE", "NEW GAME", "OTHER GAME");
    if (resultPauseTmp == 0) flag = false;
    else {
      flag = true;
      if (resultPauseTmp == 2) selectGame();
    }
  }
}