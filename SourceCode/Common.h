#include "Adafruit_ILI9341.h"
#include "vector"

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
#define enterPause 26

Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

#define black tft.color565(0, 0, 0)
#define indigo tft.color565(255, 0, 0)
#define green tft.color565(0, 255, 0)
#define red tft.color565(0, 0, 255)
#define yellow tft.color565(0, 255, 255)
#define purple tft.color565(255, 0, 255)
#define blue tft.color565(255, 255, 0)
#define white tft.color565(255, 255, 255)

int currentGame = 0;
int commonScore;
bool flag = true;

void posContinue() {
  tft.fillRect(80, 24, 156, 40, red);
  tft.setCursor(88, 32);
  tft.println("CONTINUE");
}

void negContinue() {
  tft.fillRect(80, 24, 156, 40, indigo);
  tft.setCursor(88, 32);
  tft.println("CONTINUE");
}

void posNewGame() {
  tft.fillRect(80, 88, 156, 40, red);
  tft.setCursor(88, 96);
  tft.println("NEW GAME");
}

void negNewGame() {
  tft.fillRect(80, 88, 156, 40, indigo);
  tft.setCursor(88, 96);
  tft.println("NEW GAME");
}

void posOtherGame() {
  tft.fillRect(64, 152, 192, 40, red);
  tft.setCursor(72, 160);
  tft.println("OTHER GAME");
}

void negOtherGame() {
  tft.fillRect(64, 152, 192, 40, indigo);
  tft.setCursor(72, 160);
  tft.println("OTHER GAME");
}

void drawBest(int best) {
  tft.fillRect(266, 40, 48, 24, black);
  tft.setTextColor(purple);
  if (best < 10) tft.setCursor(278, 40);
  else if (best < 100) tft.setCursor(270, 40);
  else tft.setCursor(266, 40);
  tft.println(best);
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