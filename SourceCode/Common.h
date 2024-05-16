#include "Adafruit_ILI9341.h"
#include "vector"
#include "EEPROM.h"

#define _cs 15
#define _dc 2 
#define _mosi 23
#define _sclk 18 
#define _rst 4   
#define _miso     

#define top 27
#define bottom 14
#define left 13
#define right 25
#define enter 26
#define pau 33
#define buzzer 32

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

#define black tft.color565(0, 0, 0)
#define indigo tft.color565(255, 0, 0)
#define green tft.color565(0, 255, 0)
#define red tft.color565(0, 0, 255)
#define yellow tft.color565(0, 255, 255)
#define purple tft.color565(255, 0, 255)
#define blue tft.color565(255, 255, 0)
#define white tft.color565(255, 255, 255)

#define addressBestFlappyBird 0

#define addressBestMazeEasy 1
#define addressBestMazeMedium 2
#define addressBestMazeHard 3

#define addressBestPonkEasy 4
#define addressBestPonkMedium 5
#define addressBestPonkHard 6

#define addressBestSnakeWindFreeEasy 7
#define addressBestSnakeWindFreeMedium 8
#define addressBestSnakeWindFreeHard 9
#define addressBestSnakeWindHomeEasy 10
#define addressBestSnakeWindHomeMedium 11
#define addressBestSnakeWindHomeHard 12
#define addressBestSnakeWindParkEasy 13
#define addressBestSnakeWindParkMedium 14
#define addressBestSnakeWindParkHard 15

#define addressBestTankWar 16

int currentGame = 0, commonScore;

int bestFlappyBird;
int bestPonkEasy, bestPonkMedium, bestPonkHard;
int bestMazeEasy, bestMazeMedium, bestMazeHard;
int bestSnakeWindFreeEasy, bestSnakeWindFreeMedium, bestSnakeWindFreeHard, bestSnakeWindHomeEasy, bestSnakeWindHomeMedium, bestSnakeWindHomeHard
                          , bestSnakeWindParkEasy, bestSnakeWindParkMedium, bestSnakeWindParkHard;
int bestTankWar;

bool flag = true;

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

void posOne(String s) {
  tft.fillRect(80, 24, 156, 40, red);
  tft.setCursor(88, 32);
  tft.println(s);
}

void negOne(String s) {
  tft.fillRect(80, 24, 156, 40, indigo);
  tft.setCursor(88, 32);
  tft.println(s);
}

void posTwo(String s) {
  tft.fillRect(80, 88, 156, 40, red);
  tft.setCursor(88, 96);
  tft.println(s);
}

void negTwo(String s) {
  tft.fillRect(80, 88, 156, 40, indigo);
  tft.setCursor(88, 96);
  tft.println(s);
}

void posThree(String s) {
  tft.fillRect(64, 152, 192, 40, red);
  tft.setCursor(72, 160);
  tft.println(s);
}

void negThree(String s) {
  tft.fillRect(64, 152, 192, 40, indigo);
  tft.setCursor(72, 160);
  tft.println(s);
}

void drawBest(int best) {
  tft.fillRect(266, 40, 48, 24, black);
  tft.setTextColor(purple);

  if (best < 10) tft.setCursor(278, 40);
  else if (best < 100) tft.setCursor(270, 40);
  else tft.setCursor(266, 40);

  tft.println(best);
}

int selectThree(String one, String two, String three) {
  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  bool oneTmp = true;
  bool twoTmp = false;

  posOne(one);
  negTwo(two);
  negThree(three);

  while (1) {
    if (oneTmp) {
      if (!digitalRead(enter)) return 0;
      if (!digitalRead(top)) {
        negOne(one);
        posThree(three);
        oneTmp = false;
      } else if (!digitalRead(bottom)) {
        negOne(one);
        posTwo(two);
        oneTmp = false;
        twoTmp = true;
      } 
    } else if (twoTmp) {
      if (!digitalRead(enter)) return 1;
      if (!digitalRead(top)) {
        negTwo(two);
        posOne(one);
        twoTmp = false;
        oneTmp = true;
      } else if (!digitalRead(bottom)) {
        negTwo(two);
        posThree(three);
        twoTmp = false;
      } 
    } else {
      if (!digitalRead(enter)) return 2;
      if (!digitalRead(top)) {
        negThree(three);
        posTwo(two);
        twoTmp = true;
      } else if (!digitalRead(bottom)) {
        negThree(three);
        posOne(one);
        oneTmp = true;
      } 
    }
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

  posTwo(two);
  negThree(three);

  while (1) {
    if (twoTmp) {
      if (!digitalRead(enter)) return 1;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negTwo(two);
        posThree(three);
        twoTmp = false;
      } 
    } else {
      if (!digitalRead(enter)) return 2;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negThree(three);
        posTwo(two);
        twoTmp = true;
      } 
    }
  }
}

void drawScore() {
  tft.fillRect(266, 104, 48, 24, black);
  tft.setTextColor(purple);

  if (commonScore < 10) tft.setCursor(278, 104);
  else if (commonScore < 100) tft.setCursor(270, 104);
  else tft.setCursor(264, 104);
  
  tft.println(commonScore);
}

void drawSubScreen(int best, int score) {
  commonScore = score;

  tft.fillScreen(black);
  tft.fillRect(240, 0, 4, 240, blue);

  tft.setTextSize(2);

  tft.setCursor(260, 16);
  tft.setTextColor(white);
  tft.println("BEST");

  drawBest(best);

  tft.setCursor(252, 80);
  tft.setTextColor(white);
  tft.println("SCORE");

  drawScore();

  tft.fillRect(252, 168, 66, 32, indigo);
  tft.setCursor(256, 176);
  tft.setTextColor(white);
  tft.println("PAUSE");
}

void increaseScore() {
  ++commonScore;
  drawScore();
}

void selectGame();

struct coordinates {
  int x, y;
};