int directionSnakeWind;

std::vector<coordinates> snake;

coordinates food, bigFood;

void drawSnakeHead() { // vẽ đầu rắn
  tft.fillRoundRect(snake[0].x * 8, snake[0].y * 8, 8, 8, 1, yellow);
  tft.fillRoundRect(snake[0].x * 8 + 3, snake[0].y * 8 + 2, 3, 3, 1, black);
}

void drawPartSnakeBody(int x, int y) { // vẽ thân rắn
  tft.fillRoundRect(x * 8, y * 8, 8, 8, 1, green);
}

void generateFood() {
  while (1) { // tạo thức ăn mới khi hết thức ăn cũ
    int x = random(30), y = random(30); // random tọa độ thức ăn mới
    bool b = false; // kiểm tra xem tọa độ có trùng với vị trí rắn không
    for (int i = 0; i < snake.size(); ++i) {
      if (snake[i].x == x && snake[i].y == y) {
        b = true; // trùng tọa độ với rắn
        break;
      }
    }
    int xx = bigFood.x, yy = bigFood.y; // tiếp tục kiểm tra có trùng tọa độ với thức ăn to không
    if ((x == xx && y == yy) || (x == xx + 1 && y == yy) || (x == xx && y == yy + 1) || (x == xx + 1 && y == yy + 1)) b = true; 
    if (b) continue; // nếu vẫn trùng gán tọa độ mới
    food.x = x;
    food.y = y;
    tft.fillRoundRect(x * 8, y * 8, 8, 8, 3, white); // vẽ thức ăn ra màn hình
    return;
  }
}

void generateBigFood() {
  while (1) {
    int x = random(29), y = random(29); // random tọa độ 
    bool b = false; // đặt biến kiểm tra có trùng tọa độ rắn không
    for (int i = 0; i < snake.size(); ++i) {
      int xx = snake[i].x, yy = snake[i].y;
      if ((xx == x && yy == y) || (xx == x + 1 && yy == y) || (xx == x && yy == y + 1) || (xx == x + 1 && yy == y + 1)) {
        b = true; // trùng tọa độ với rắn
        break;
      }
      xx = food.x, yy = food.y;
      if ((xx == x && yy == y) || (xx == x + 1 && yy == y) || (xx == x && yy == y + 1) || (xx == x + 1 && yy == y + 1)) {
        b = true; // trùng tọa độ với thức ăn thường
        break;
      }
    }
    if (b) continue; // nếu vẫn trùng gán tọa độ mới
    bigFood.x = x;
    bigFood.y = y;
    tft.fillRoundRect(x * 8, y * 8, 16, 16, 5, red); // vẽ thức ăn to ra màn hình
    return;
  }
}

void drawRunSnake(int x, int y) {
  coordinates [tmp = snakesnake.size() - 1];  // Lưu lại tọa độ ô cuối cùng
  int b = 0;
  if (x == food.x && y == food.y) { // Ăn đc thức ăn thường
    increaseScore(); // Tăng điểm
    b = 1; // Đánh dấu đã ăn thức ăn
  } else if (bigFood.x != -1) {  //Ăn đc thức ăn to
    int xx = bigFood.x, yy = bigFood.y;
    if ((x == xx && y == yy) || (x == xx + 1 && y == yy) || (x == xx && y == yy + 1) || (x == xx + 1 && y == yy + 1)) {
      commonScore += 4; // tăng 4 điểm
      increaseScore(); // 5 điểm
      b = 2; // Đánh dấu đã ăn thức ăn to
    }
  }
  for (int i = snake.size() - 1; i > 0; --i) snake[i] = snake[i - 1]; // Dịch chuyển vị trí các phần thân
  snake[0].x = x; // Đặt vị trí mới cho đầu rắn
  snake[0].y = y;
  if (b) { //Nếu có ăn thức ăn
    snake.push_back(tmp); //Thêm phần thân cuối cùng vào
    if (b == 1) generateFood(); // Tạo thức ăn mới
    else {
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black); // Xóa thức ăn to
      bigFood.x = -1;
    }
  } else tft.fillRect(tmp.x * 8, tmp.y * 8, 8, 8, black); // xóa ô cuối cùng
  drawSnakeHead();
  drawPartSnakeBody(snake[1].x, snake[1].y);
}

bool checkGameOverSW() {
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) { // Tọa độ thân trùng với đầu
      if (commonScore > bestSnakeWind) { 
        bestSnakeWind = commonScore;       // Nếu điểm hiện tại cao hơn kỷ lục thì ghi lại kỷ lục    
        EEPROM.write(3, commonScore); // lưu điểm
        EEPROM.commit(); 
      }
      snake.clear(); // Xóa toàn bộ rắn 
      return true;
    }
  }
  return false;
}

void moveSnake() {
  if (!digitalRead(top) && directionSnakeWind != 2) { // Nếu ấn nút lên và hướng chưa phải hướng xuống
    directionSnakeWind = 0; // đổi hướng lên
    if (!snake[0].y) drawRunSnake(snake[0].x, 29); // nếu đầu ở trên cùng thì xuống dưới cùng
    else drawRunSnake(snake[0].x, snake[0].y - 1);  // di chuyển lên 1 ô
  } else if (!digitalRead(right) && directionSnakeWind != 3) {
    directionSnakeWind = 1;
    if (snake[0].x == 29) drawRunSnake(0, snake[0].y);
    else drawRunSnake(snake[0].x + 1, snake[0].y);
  } else if (!digitalRead(bottom) && directionSnakeWind != 0) {
    directionSnakeWind = 2;
    if (snake[0].y == 29) drawRunSnake(snake[0].x, 0);
    else drawRunSnake(snake[0].x, snake[0].y + 1);
  } else if (!digitalRead(left) && directionSnakeWind != 1) {
    directionSnakeWind = 3;
    if (!snake[0].x) drawRunSnake(29, snake[0].y);
    else drawRunSnake(snake[0].x - 1, snake[0].y);
  } else {  // Nếu không ấn phím
    if (directionSnakeWind == 0) { // kiểm tra hướng hiện tại và di chuyển theo hướng đó
      if (!snake[0].y) drawRunSnake(snake[0].x, 29);
      else drawRunSnake(snake[0].x, snake[0].y - 1);
    } else if (directionSnakeWind == 1) {
      if (snake[0].x == 29) drawRunSnake(0, snake[0].y);
      else drawRunSnake(snake[0].x + 1, snake[0].y);
    } else if (directionSnakeWind == 2) {
      if (snake[0].y == 29) drawRunSnake(snake[0].x, 0);
      else drawRunSnake(snake[0].x, snake[0].y + 1);
    } else {
      if (!snake[0].x) drawRunSnake(29, snake[0].y);
      else drawRunSnake(snake[0].x - 1, snake[0].y);
    }
  }
}

int newGameSnakeWind() { // chơi lại
  drawSubScreen(bestSnakeWind, 0); // In ra màn hình kết quả tốt nhất

  snake.clear(); // tạo lại con rắn
  snake.push_back({15, 15});
  snake.push_back({14, 15});

  drawSnakeHead(); // vẽ đầu và thân rắn
  drawPartSnakeBody(snake[1].x, snake[1].y);
  generateFood(); // tạo thức ăn

  directionSnakeWind = 1; // hướng di chuyển mặc định

  while (1) {
    for (int i = 0; i < 100; ++i) {
      if (!digitalRead(enterPause)) return 0; // kiểm tra có nhấn pause không
      moveSnake();
      if (checkGameOverSW()) return 1; // kiểm tra gameover
      delay(100);
    }
    generateBigFood(); // tạo thức ăn to
    for (int i = 0; i < 40; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(100);
    }
    if (bigFood.x != -1) { // nếu ăn thức ăn to thì xóa thức ăn to
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black);
      bigFood.x = -1;
    }
  }
}

int continueSnakeWind() { // tiếp tục chơi
  drawSubScreen(bestSnakeWind, commonScore); // in ra màn hình kết quả hiện tại

  drawSnakeHead(); // vẽ lại rắn
  for (int i = 1; i < snake.size(); ++i) drawPartSnakeBody(snake[i].x, snake[i].y);
  tft.fillRoundRect(food.x * 8, food.y * 8, 8, 8, 3, white);
  
  while (1) {
    for (int i = 0; i < 100; ++i) {
      if (!digitalRead(enterPause)) return 0; // kiểm tra có nhấn pause không
      moveSnake();
      if (checkGameOverSW()) return 1; // kiểm tra gameover
      delay(100);
    }
    generateBigFood(); // tạo thức ăn to
    for (int i = 0; i < 40; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(100);
    }
    if (bigFood.x != -1) { // nếu ăn thức ăn to thì xóa thức ăn to
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black);
      bigFood.x = -1;
    }
  }
}
