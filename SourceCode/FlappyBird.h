int yBird;

int heightArray[31][2];

void drawLeftSewer(int x, int h) { // vẽ ống cống trái
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawMidSewer(int x, int h) { // vẽ ống cống giữa
  tft.fillRect(x * 8, 0, 8, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 8, (19 - h) * 8, green);
}

void drawRightSewer(int x, int h) { // vẽ ống cống phải
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, black);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, black);
  tft.fillRect(x * 8, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawSewer(int x, int h) { // vẽ ống cống
  tft.fillRect(x * 8 + 4, 0, 16, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 24, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 24, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 16, (19 - h) * 8, green);
}

void drawRunSewer() { // vẽ ống cống mới
  for (int i = 0; i < 30; ++i) {
    if (heightArray[i][0]) {
      switch (heightArray[i][1]) {
        case 0: // ống cống hiện tại là trái 
          heightArray[i][1] = 1; 
          drawMidSewer(i, heightArray[i][0]); // vẽ ống cống giữa
          break;
        case 1: // ống cống hiện tại là giữa
          heightArray[i][1] = 2; 
          drawRightSewer(i, heightArray[i][0]); // vẽ ống cống phải
          break;
        default: // ống cống hiện tải là phải
          tft.fillRect(i * 8, 0, 8, heightArray[i][0] * 8, black);
          tft.fillRect(i * 8, (heightArray[i][0] + 9) * 8, 8, (21 - heightArray[i][0]) * 8, black);
          heightArray[i][0] = 0; // xóa ống cống hiện tại
      }
    } else if (heightArray[i + 1][0]) { // không có ống cống thì kiểm tra vị trí tiếp theo
      heightArray[i][0] = heightArray[i + 1][0]; // sao chép chiều cao ống tiếp theo về ống hiện tại
      heightArray[i][1] = 0;
      drawLeftSewer(i, heightArray[i][0]); // vẽ ống cống trái
    }
  }
}

void drawBird() { // vẽ chim
  tft.fillRoundRect(36, yBird * 8, 16, 16, 5, yellow);
  tft.fillRoundRect(44, yBird * 8, 8, 8, 5, white);
  tft.fillRoundRect(30, yBird * 8 + 4, 10, 8, 5, white);
  tft.fillRoundRect(46, yBird * 8 + 2, 3, 3, 1, black);
  tft.fillRoundRect(48, yBird * 8 + 10, 8, 4, 3, red);
}

bool checkGameOverFB() {
  if (heightArray[4][0]) { 
    if (heightArray[4][0] >= yBird || yBird >= heightArray[4][0] + 7) { // nếu đụng phải ống cống gameover
      if (commonScore > bestFlappyBird) {
        bestFlappyBird = commonScore;
        EEPROM.write(0, commonScore);
        EEPROM.commit(); // lưu điểm kỷ lục
      }
      return true;
    } 
  }
  if (heightArray[6][0]) {
    if (heightArray[6][0] >= yBird || yBird >= heightArray[6][0] + 7) { // nếu đụng phải ống cống gameover
      if (commonScore > bestFlappyBird) {
        bestFlappyBird = commonScore;
        EEPROM.write(0, commonScore);
        EEPROM.commit(); // lưu điểm kỷ lục
      }
      return true;
    }
  }
  return false;
}

void birdFly() { 
  if (!digitalRead(top)) { // chim bay lên khi nhấn nút trên
    tft.fillRect(36, yBird * 8, 16, 16, black);
    tft.fillRect(30, yBird * 8 + 4, 6, 12, black);
    tft.fillRect(52, yBird * 8 + 10, 4, 4, black);
    --yBird; 
    tft.fillRoundRect(36, yBird * 8, 16, 16, 5, yellow);
    tft.fillRoundRect(44, yBird * 8, 8, 8, 5, white);
    tft.fillRoundRect(30, yBird * 8 + 8, 10, 8, 5, white);
    tft.fillRoundRect(46, yBird * 8 + 2, 3, 3, 1, black);
    tft.fillRoundRect(48, yBird * 8 + 10, 8, 4, 3, red);
    delay(100);
    tft.fillRect(30, yBird * 8 + 8, 8, 8, black);
    tft.fillRoundRect(36, yBird * 8 + 10, 6, 6, 5, yellow);
    tft.fillRoundRect(30, yBird * 8 + 4, 10, 8, 5, white);
  }
}

void birdFall() {
  tft.fillRect(36, yBird * 8, 16, 16, black);
  tft.fillRect(30, yBird * 8 + 4, 6, 12, black);
  tft.fillRect(52, yBird * 8 + 10, 4, 4, black);
  ++yBird; 
  drawBird(); 
}


int generateSewer(int rd, int status) {
  heightArray[30][0] = rd;
  heightArray[30][1] = status;
  for (int i = 0; i < 5; ++i) {
    if (!digitalRead(pau)) return 0;
    birdFly();
    if (checkGameOverFB()) return 1;
    delay(50);
  }
  birdFall();
  if (checkGameOverFB()) return 1;
  drawRunSewer();
  if (heightArray[3][0] && !heightArray[4][0]) increaseScore(); // bay qua ống cống tăng điểm
  return 2;
}

int generateBlack() {
  heightArray[30][0] = 0; // vẽ khoảng trống
  for (int i = 0; i < 5; ++i) {
    if (!digitalRead(pau)) return 0;
    birdFly();
    if (checkGameOverFB()) return 1;
    delay(50);
  }
  birdFall();
  if (checkGameOverFB()) return 1;
  drawRunSewer();
  if (heightArray[3][0] && !heightArray[4][0]) increaseScore(); // bay qua ống cống tăng điểm
  return 2;
}

int newGameFlappyBird() { // chơi lại
  drawSubScreen(bestFlappyBird, 0); // hiển thị điểm cao nhất

  memset(heightArray, 0, sizeof(heightArray)); 

  for (int i = 12; i < 30; i += 6) { // vẽ ống cách nhau 6 vị trí
    int rd = random(7, 15); // random chiều cao ống
    heightArray[i][0] = heightArray[i + 1][0] = heightArray[i + 2][0] = rd;
    heightArray[i][1] = 0;
    heightArray[i + 1][1] = 1;
    heightArray[i + 2][1] = 2; // 3 ống lần lượt trái, giữa , phải
    drawSewer(i, rd); // vẽ 3 ống
  }

  yBird = 15;
  drawBird();

  // trò chơi vận hành
  while (1) {
    int rd = random(7, 15);

    int result = generateSewer(rd, 0);
    if (result != 2) return result;
    result = generateSewer(rd, 1);
    if (result != 2) return result;
    result = generateSewer(rd, 2);
    if (result != 2) return result;
    
    result = generateBlack();
    if (result != 2) return result;
    result = generateBlack();
    if (result != 2) return result;
    result = generateBlack();
    if (result != 2) return result;
  }
}

int continueFlappyBird() {
  drawSubScreen(bestFlappyBird, commonScore);

  // vẽ lại trạng thái cũ
  for (int i = 0; i < 30; ++i) {
    if (heightArray[i][0]) {
      switch (heightArray[i][1]) {
        case 0:
          drawLeftSewer(i, heightArray[i][0]);
          break;
        case 1:
          drawMidSewer(i, heightArray[i][0]);
          break;
        default:
          drawRightSewer(i, heightArray[i][0]);
      }
    }
  }

  drawBird();

  int result;

  // đưa trò chơi trở lại vào guồng vận hành
  if (heightArray[29][0]) {
    switch (heightArray[29][1]) {
      case 0:
        result = generateSewer(heightArray[29][0], 1);
        if (result != 2) return result;
        result = generateSewer(heightArray[29][0], 2);
        if (result != 2) return result;
        
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
        break;
      case 1:
        result = generateSewer(heightArray[29][0], 2);
        if (result != 2) return result;
        
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
        break;
      default:
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
        result = generateBlack();
        if (result != 2) return result;
    }
  } else {
    if (heightArray[28][0]) {
      result = generateBlack();
      if (result != 2) return result;
      result = generateBlack();
      if (result != 2) return result;
    } else if (heightArray[27][0]) {
      result = generateBlack();
      if (result != 2) return result;
    }
  }

  // trò chơi vận hành
  while (1) {
    int rd = random(7, 15);

    result = generateSewer(rd, 0);
    if (result != 2) return result;
    result = generateSewer(rd, 1);
    if (result != 2) return result;
    result = generateSewer(rd, 2);
    if (result != 2) return result;
    
    result = generateBlack();
    if (result != 2) return result;
    result = generateBlack();
    if (result != 2) return result;
    result = generateBlack();
    if (result != 2) return result;
  }
}