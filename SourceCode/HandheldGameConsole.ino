#include "Common.h"       // Đưa vào các thư viện và tập tin phụ trợ
#include "FlappyBird.h"
#include "Maze.h"
#include "Ponk.h"
#include "SnakeWind.h"
#include "TankWar.h"
#include "Pause.h"
#include "GameOver.h"
#include "SelectGame.h"

void setup() {
  // Khởi tạo các chân cảm biến và cổng Serial để giao tiếp với nút nhấn và màn hình
  pinMode(top, INPUT);
  pinMode(bottom, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(enterPause, INPUT);

  Serial.begin(9600);  // Khởi động giao tiếp Serial với tốc độ baud là 9600

  // Khởi tạo màn hình TFT và đặt chế độ xoay
  tft.begin();
  tft.setRotation(2);

  // Khởi tạo EEPROM để lưu trữ điểm số tốt nhất của các trò chơi
  EEPROM.begin(5);
  bestFlappyBird = EEPROM.read(0);
  bestMaze = EEPROM.read(1);
  bestPonk = EEPROM.read(2);
  bestSnakeWind = EEPROM.read(3);
  bestTankWar = EEPROM.read(4);

  // Chọn trò chơi khi lần đầu chạy chương trình
  selectGame();
}

void loop() {
  int resCommon; // Biến để lưu kết quả trả về từ hàm switchNewGame hoặc switchContinue

  // Nếu flag là true, có nghĩa là chúng ta đang chơi một trò chơi mới
  // Ngược lại, chúng ta đang tiếp tục trò chơi đã chọn trước đó
  if (flag) 
    resCommon = switchNewGame();
  else 
    resCommon = switchContinue();

  // Nếu trò chơi kết thúc và chúng ta chọn trò chơi mới, quay lại màn hình chọn trò chơi
  if (resCommon) {

    //1 sẽ là gameover,0 là pause
    flag = true; // Thiết lập lại flag để cho biết chúng ta đang chơi trò chơi mới
    if (gameOver(commonScore) == 2) 
      selectGame();
  } else {
    // Hiển thị màn hình tạm dừng và xử lý nút nhấn tạm dừng
    int resPause = pause();
    if (resPause == 0) 
      flag = false; // Nếu như nhấn nút tiếp tục, tiếp tục trò chơi
    else {
      flag = true;  // Nếu chọn trò chơi mới từ màn hình tạm dừng, quay lại màn hình chọn trò chơi
      if (resPause == 2) 
        selectGame();
    }
  }
}