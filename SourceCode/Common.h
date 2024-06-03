#include "Adafruit_ILI9341.h"
#include "vector"
#include "EEPROM.h"

// Pins of screen
#define _cs 15
#define _dc 2 
#define _mosi 23
#define _sclk 18 
#define _rst 4   
#define _miso     

// Pins of buttons
#define top 27
#define bottom 14
#define left 13
#define right 25
#define enter 26
#define pau 33
#define buzzer 32

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

// Colors
#define black tft.color565(0, 0, 0)
#define indigo tft.color565(255, 0, 0)
#define green tft.color565(0, 255, 0)
#define red tft.color565(0, 0, 255)
#define yellow tft.color565(0, 255, 255)
#define purple tft.color565(255, 0, 255)
#define blue tft.color565(255, 255, 0)
#define white tft.color565(255, 255, 255)

// Abstract addresses data about best score
#define addressBestFlappyBird 8

#define addressBestMazeEasy 9
#define addressBestMazeMedium 10
#define addressBestMazeHard 11

#define addressBestPonkEasy 12
#define addressBestPonkMedium 13
#define addressBestPonkHard 14

#define addressBestSnakeWindFreeEasy 15
#define addressBestSnakeWindFreeMedium 16
#define addressBestSnakeWindFreeHard 17
#define addressBestSnakeWindHomeEasy 18
#define addressBestSnakeWindHomeMedium 19
#define addressBestSnakeWindHomeHard 20
#define addressBestSnakeWindParkEasy 21
#define addressBestSnakeWindParkMedium 22
#define addressBestSnakeWindParkHard 23

#define addressBestTankWar 24

int currentGame = 0, commonScore;

int bestFlappyBird;
int bestPonkEasy, bestPonkMedium, bestPonkHard;
int bestMazeEasy, bestMazeMedium, bestMazeHard;
int bestSnakeWindFreeEasy, bestSnakeWindFreeMedium, bestSnakeWindFreeHard, bestSnakeWindHomeEasy, bestSnakeWindHomeMedium, bestSnakeWindHomeHard
                          , bestSnakeWindParkEasy, bestSnakeWindParkMedium, bestSnakeWindParkHard;
int bestTankWar;

int countPlayer, currentPlayer;

bool flag = true; // True is new game. False is continue

// Buzzer sound function
void playTone(int t, int duration) {
  tone(buzzer, t, duration);
  delay(duration * 1.3);
  noTone(buzzer);
}

// "Mario Theme"
void music() {
  playTone(660, 120);
  playTone(660, 120);
  delay(120);
  playTone(660, 120);
  delay(120);
  playTone(510, 120);
  playTone(660, 120);
  delay(120);
  playTone(1397, 120);
  delay(300);
  playTone(380, 120);
  delay(300);
  playTone(510, 120);
  delay(120);
  playTone(380, 120);
  delay(300);
}

// drawOne, drawTwo, drawThree support for selectTwo, selectThree
void drawOne(bool b, String s) {
  if (b) tft.fillRect(80, 24, 156, 40, red);
  else tft.fillRect(80, 24, 156, 40, indigo);
  tft.setCursor(88, 32);
  tft.println(s);
}

void drawTwo(bool b, String s) {
  if (b) tft.fillRect(80, 88, 156, 40, red);
  else tft.fillRect(80, 88, 156, 40, indigo);
  tft.setCursor(88, 96);
  tft.println(s);
}


void drawThree(bool b, String s) {
  if (b) tft.fillRect(64, 152, 192, 40, red);
  else tft.fillRect(64, 152, 192, 40, indigo);
  tft.setCursor(72, 160);
  tft.println(s);
}

void drawPause(bool b) {
  tft.setTextSize(2);

  if (b) tft.fillRect(252, 184, 66, 32, red);
  else tft.fillRect(252, 184, 66, 32, indigo);

  tft.setCursor(256, 192);
  tft.setTextColor(white);
  tft.println("PAUSE");
}

int selectThree(bool b, String one, String two, String three) {
  if (b) drawPause(true);

  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  bool oneTmp = true;
  bool twoTmp = false;

  drawOne(true, one);
  drawTwo(false, two);
  drawThree(false, three);

  // Up and down action for drawOne, drawTwo, drawThree
  while (1) {
    if (oneTmp) {
      if (!digitalRead(enter)) return 0;
      if (!digitalRead(top)) {
        drawOne(false, one);
        drawThree(true, three);
        oneTmp = false;
      } else if (!digitalRead(bottom)) {
        drawOne(false, one);
        drawTwo(true, two);
        oneTmp = false;
        twoTmp = true;
      } 
    } else if (twoTmp) {
      if (!digitalRead(enter)) return 1;
      if (!digitalRead(top)) {
        drawTwo(false, two);
        drawOne(true, one);
        twoTmp = false;
        oneTmp = true;
      } else if (!digitalRead(bottom)) {
        drawTwo(false, two);
        drawThree(true, three);
        twoTmp = false;
      } 
    } else {
      if (!digitalRead(enter)) return 2;
      if (!digitalRead(top)) {
        drawThree(false, three);
        drawTwo(true, two);
        twoTmp = true;
      } else if (!digitalRead(bottom)) {
        drawThree(false, three);
        drawOne(true, one);
        oneTmp = true;
      } 
    }
  }
}

// Read player name from EEPROM address
String readNamePlayer(bool b, int n) {
  if (n / 25 >= countPlayer) return "";
  String namePlayerTmp = "";
  if (b) for (int i = 0; i < 8; ++i) {
    if (EEPROM.read(n + i) == 111) break;
    namePlayerTmp += (char) (65 + EEPROM.read(n + i));
  } else for (int i = 0; i < 4; ++i) {
    if (EEPROM.read(n + i) == 111) break;
    namePlayerTmp += (char) (65 + EEPROM.read(n + i));
  } 
  return namePlayerTmp;
}

void drawOldPlayer(bool b, int x, int y, String s) {
  if (b) tft.fillRoundRect(x, y, 128, 24, 5, red);
  else tft.fillRoundRect(x, y, 128, 24, 5, indigo);
  tft.setCursor(x + 16, y + 4);
  tft.println(s);
}

// Show list of old player (max: 8)
int selectEight() {
  tft.fillScreen(black);
  tft.setTextSize(2);
  tft.setTextColor(white);

  drawOldPlayer(true, 16, 48, readNamePlayer(true, 0));

  drawOldPlayer(false, 16, 88, readNamePlayer(true, 25));
  drawOldPlayer(false, 16, 128, readNamePlayer(true, 50));
  drawOldPlayer(false, 16, 168, readNamePlayer(true, 75));

  drawOldPlayer(false, 176, 48, readNamePlayer(true, 100));
  drawOldPlayer(false, 176, 88, readNamePlayer(true, 125));
  drawOldPlayer(false, 176, 128, readNamePlayer(true, 150));
  drawOldPlayer(false, 176, 168, readNamePlayer(true, 175));
  
  // Select player action (move top, right, bottom, left)
  /* Illustration:
    1     5
    2     6
    3     7
    4     8
  */
  int targetTmp = 1;
  while (1) {
    switch (targetTmp) {
      case 1:
        if (!digitalRead(right)) {
          targetTmp = 5;
          drawOldPlayer(false, 16, 48, readNamePlayer(true, 0));
          drawOldPlayer(true, 176, 48, readNamePlayer(true, 100));
        } else if (!digitalRead(bottom)) {
          targetTmp = 2;
          drawOldPlayer(false, 16, 48, readNamePlayer(true, 0));
          drawOldPlayer(true, 16, 88, readNamePlayer(true, 25));
        } else if (!digitalRead(enter)) return 0;
        break;
      case 2:
        if (!digitalRead(top)) {
          targetTmp = 1;
          drawOldPlayer(false, 16, 88, readNamePlayer(true, 25));
          drawOldPlayer(true, 16, 48, readNamePlayer(true, 0));
        } else if (!digitalRead(right)) {
          targetTmp = 6;
          drawOldPlayer(false, 16, 88, readNamePlayer(true, 25));
          drawOldPlayer(true, 176, 88, readNamePlayer(true, 125));
        } else if (!digitalRead(bottom)) {
          targetTmp = 3;
          drawOldPlayer(false, 16, 88, readNamePlayer(true, 25));
          drawOldPlayer(true, 16, 128, readNamePlayer(true, 50));
        } else if (!digitalRead(enter) && countPlayer > 1) return 25;
        break;
      case 3:
        if (!digitalRead(top)) {
          targetTmp = 2;
          drawOldPlayer(false, 16, 128, readNamePlayer(true, 50));
          drawOldPlayer(true, 16, 88, readNamePlayer(true, 25));
        } else if (!digitalRead(right)) {
          targetTmp = 7;
          drawOldPlayer(false, 16, 128, readNamePlayer(true, 50));
          drawOldPlayer(true, 176, 128, readNamePlayer(true, 150));
        } else if (!digitalRead(bottom)) {
          targetTmp = 4;
          drawOldPlayer(false, 16, 128, readNamePlayer(true, 50));
          drawOldPlayer(true, 16, 168, readNamePlayer(true, 75));
        } else if (!digitalRead(enter) && countPlayer > 2) return 50;
        break;
      case 4:
        if (!digitalRead(top)) {
          targetTmp = 3;
          drawOldPlayer(false, 16, 168, readNamePlayer(true, 75));
          drawOldPlayer(true, 16, 128, readNamePlayer(true, 50));
        } else if (!digitalRead(right)) {
          targetTmp = 8;
          drawOldPlayer(false, 16, 168, readNamePlayer(true, 75));
          drawOldPlayer(true, 176, 168, readNamePlayer(true, 175));
        } else if (!digitalRead(enter) && countPlayer > 3) return 75;
        break;
      case 5:
        if (!digitalRead(left)) {
          targetTmp = 1;
          drawOldPlayer(false, 176, 48, readNamePlayer(true, 100));
          drawOldPlayer(true, 16, 48, readNamePlayer(true, 0));
        } else if (!digitalRead(bottom)) {
          targetTmp = 6;
          drawOldPlayer(false, 176, 48, readNamePlayer(true, 100));
          drawOldPlayer(true, 176, 88, readNamePlayer(true, 125));
        } else if (!digitalRead(enter) && countPlayer > 4) return 100;
        break;
      case 6:
        if (!digitalRead(top)) {
          targetTmp = 5;
          drawOldPlayer(false, 176, 88, readNamePlayer(true, 125));
          drawOldPlayer(true, 176, 48, readNamePlayer(true, 100));
        } else if (!digitalRead(left)) {
          targetTmp = 2;
          drawOldPlayer(false, 176, 88, readNamePlayer(true, 125));
          drawOldPlayer(true, 16, 88, readNamePlayer(true, 25));
        } else if (!digitalRead(bottom)) {
          targetTmp = 7;
          drawOldPlayer(false, 176, 88, readNamePlayer(true, 125));
          drawOldPlayer(true, 176, 128, readNamePlayer(true, 150));
        } else if (!digitalRead(enter) && countPlayer > 5) return 125;
        break;
      case 7:
        if (!digitalRead(top)) {
          targetTmp = 6;
          drawOldPlayer(false, 176, 128, readNamePlayer(true, 150));
          drawOldPlayer(true, 176, 88, readNamePlayer(true, 125));
        } else if (!digitalRead(left)) {
          targetTmp = 3;
          drawOldPlayer(false, 176, 128, readNamePlayer(true, 150));
          drawOldPlayer(true, 16, 128, readNamePlayer(true, 50));
        } else if (!digitalRead(bottom)) {
          targetTmp = 8;
          drawOldPlayer(false, 176, 128, readNamePlayer(true, 150));
          drawOldPlayer(true, 176, 168, readNamePlayer(true, 175));
        } else if (!digitalRead(enter) && countPlayer > 6) return 150;
        break;
      default:
        if (!digitalRead(top)) {
          targetTmp = 7;
          drawOldPlayer(false, 176, 168, readNamePlayer(true, 175));
          drawOldPlayer(true, 176, 128, readNamePlayer(true, 150));
        } else if (!digitalRead(left)) {
          targetTmp = 4;
          drawOldPlayer(false, 176, 168, readNamePlayer(true, 175));
          drawOldPlayer(true, 16, 168, readNamePlayer(true, 75));
        } else if (!digitalRead(enter) && countPlayer > 7) return 175;
    }
    delay(100);
  }
}

int selectTwo(bool gameOver, String two, String three) {
  if (gameOver) music();

  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  if (gameOver) {
    if (commonScore < 10) tft.setCursor(152, 32);
    else if (commonScore < 100) tft.setCursor(136, 32);
    else tft.setCursor(128, 32);
    tft.println(commonScore);
  }

  bool twoTmp = true;

  drawTwo(true, two);
  drawThree(false, three);

  // Up and down action for drawTwo, drawThree
  while (1) {
    if (twoTmp) {
      if (!digitalRead(enter)) return 1;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        drawTwo(false, two);
        drawThree(true, three);
        twoTmp = false;
      } 
    } else {
      if (!digitalRead(enter)) return 2;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        drawThree(false, three);
        drawTwo(true, two);
        twoTmp = true;
      } 
    }
  }
}

void drawScore() {
  tft.fillRect(266, 152, 48, 24, black);
  tft.setTextSize(2);
  tft.setTextColor(purple);

  if (commonScore < 10) tft.setCursor(278, 152);
  else if (commonScore < 100) tft.setCursor(270, 152);
  else tft.setCursor(264, 152);

  tft.println(commonScore);
}

// Draw player name, current game's best score, current score, pause button
void drawSubScreen(int best, int score) {
  commonScore = score;

  tft.fillScreen(black);
  tft.fillRect(240, 0, 4, 240, blue);

  tft.setTextSize(2);
  tft.setTextColor(white);

  tft.setCursor(246, 16);
  tft.println("PLAYER");

  tft.setCursor(260, 72);
  tft.println("BEST");

  tft.setCursor(252, 128);
  tft.println("SCORE");

  tft.fillRect(266, 96, 48, 24, black);
  tft.setTextColor(purple);

  if (best < 10) tft.setCursor(278, 96);
  else if (best < 100) tft.setCursor(270, 96);
  else tft.setCursor(266, 96);

  tft.println(best);

  drawScore();

  drawPause(false);

  tft.setTextSize(2);
  tft.setTextColor(purple);
  tft.setCursor(260, 40);
  tft.println(readNamePlayer(false, currentPlayer));
}

void increaseScore() {
  ++commonScore;
  drawScore();
}

void selectGame();

struct coordinates {
  int x, y;
};