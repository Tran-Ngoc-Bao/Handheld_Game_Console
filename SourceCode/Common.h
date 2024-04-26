#include "Adafruit_ILI9341.h"  // Đưa vào thư viện để điều khiển màn hình LCD TFT
#include "vector"               // Đưa vào thư viện vector để sử dụng
#include "EEPROM.h"             // Đưa vào thư viện EEPROM để lưu trữ dữ liệu vào bộ nhớ EEPROM

// Định nghĩa các chân giao tiếp với màn hình LCD TFT
#define _cs 15
#define _dc 2 
#define _mosi 23
#define _sclk 18 
#define _rst 4   
#define _miso     

// Định nghĩa các chân cảm biến và nút nhấn
#define top 27
#define bottom 14
#define left 13
#define right 25
#define enterPause 26

// Khởi tạo màn hình LCD TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(_cs, _dc, _mosi, _sclk, _rst);

// Định nghĩa các màu sắc sử dụng trong chương trình
#define black tft.color565(0, 0, 0)
#define indigo tft.color565(255, 0, 0)
#define green tft.color565(0, 255, 0)
#define red tft.color565(0, 0, 255)
#define yellow tft.color565(0, 255, 255)
#define purple tft.color565(255, 0, 255)
#define blue tft.color565(255, 255, 0)
#define white tft.color565(255, 255, 255)

// Khai báo biến và cờ
int currentGame = 0, commonScore;
int bestFlappyBird, bestMaze, bestPonk, bestSnakeWind, bestTankWar;
bool flag = true;

// Khai báo các hàm sử dụng trong chương trình
// Vẽ nút "CONTINUE" khi được chọn
void posContinue() {
  tft.fillRect(80, 24, 156, 40, red);
  tft.setCursor(88, 32);
  tft.println("CONTINUE");
}

// Vẽ nút "CONTINUE" khi không được chọn
void negContinue() {
  tft.fillRect(80, 24, 156, 40, indigo);
  tft.setCursor(88, 32);
  tft.println("CONTINUE");
}

// Vẽ nút "NEW GAME" khi được chọn
void posNewGame() {
  tft.fillRect(80, 88, 156, 40, red);
  tft.setCursor(88, 96);
  tft.println("NEW GAME");
}

// Vẽ nút "NEW GAME" khi không được chọn
void negNewGame() {
  tft.fillRect(80, 88, 156, 40, indigo);
  tft.setCursor(88, 96);
  tft.println("NEW GAME");
}

// Vẽ nút "OTHER GAME" khi được chọn
void posOtherGame() {
  tft.fillRect(64, 152, 192, 40, red);
  tft.setCursor(72, 160);
  tft.println("OTHER GAME");
}

// Vẽ nút "OTHER GAME" khi không được chọn
void negOtherGame() {
  tft.fillRect(64, 152, 192, 40, indigo);
  tft.setCursor(72, 160);
  tft.println("OTHER GAME");
}

// Vẽ điểm số tốt nhất
void drawBest(int best) {
  tft.fillRect(266, 40, 48, 24, black);
  tft.setTextColor(purple);
  if (best < 10) tft.setCursor(278, 40);
  else if (best < 100) tft.setCursor(270, 40);
  else tft.setCursor(266, 40);
  tft.println(best);
}

// Vẽ điểm số hiện tại
void drawScore() {
  tft.fillRect(266, 104, 48, 24, black);
  tft.setTextColor(purple);
  if (commonScore < 10) tft.setCursor(278, 104);
  else if (commonScore < 100) tft.setCursor(270, 104);
  else tft.setCursor(264, 104);
  tft.println(commonScore);
}

// Vẽ màn hình con bao gồm điểm số hiện tại và điểm số tốt nhất
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

// Tăng điểm số hiện tại
void increaseScore() {
  ++commonScore;
  drawScore();
}

void selectGame();          // Chọn trò chơi mới

// Khai báo cấu trúc dữ liệu coordinates để lưu tọa độ
struct coordinates {
  int x, y;
};