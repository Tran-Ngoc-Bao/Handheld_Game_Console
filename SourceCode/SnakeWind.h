int directionSnakeWind;

std::vector<coordinates> snake;

coordinates food, bigFood;

void drawSnakeHead() {
  tft.fillRoundRect(snake[0].x * 8, snake[0].y * 8, 8, 8, 1, yellow);
  tft.fillRoundRect(snake[0].x * 8 + 3, snake[0].y * 8 + 2, 3, 3, 1, black);
}

void drawPartSnakeBody(int x, int y) {
  tft.fillRoundRect(x * 8, y * 8, 8, 8, 1, green);
}

void generateFood() {
  while (1) {
    int x = random(30), y = random(30);
    bool b = false;
    for (int i = 0; i < snake.size(); ++i) {
      if (snake[i].x == x && snake[i].y == y) {
        b = true;
        break;
      }
    }
    int xx = bigFood.x, yy = bigFood.y;
    if ((x == xx && y == yy) || (x == xx + 1 && y == yy) || (x == xx && y == yy + 1) || (x == xx + 1 && y == yy + 1)) b = true;
    if (b) continue;
    food.x = x;
    food.y = y;
    tft.fillRoundRect(x * 8, y * 8, 8, 8, 3, white);
    return;
  }
}

void generateBigFood() {
  while (1) {
    int x = random(29), y = random(29);
    bool b = false;
    for (int i = 0; i < snake.size(); ++i) {
      int xx = snake[i].x, yy = snake[i].y;
      if ((xx == x && yy == y) || (xx == x + 1 && yy == y) || (xx == x && yy == y + 1) || (xx == x + 1 && yy == y + 1)) {
        b = true;
        break;
      }
      xx = food.x, yy = food.y;
      if ((xx == x && yy == y) || (xx == x + 1 && yy == y) || (xx == x && yy == y + 1) || (xx == x + 1 && yy == y + 1)) {
        b = true;
        break;
      }
    }
    if (b) continue;
    bigFood.x = x;
    bigFood.y = y;
    tft.fillRoundRect(x * 8, y * 8, 16, 16, 5, red);
    return;
  }
}

void drawRunSnake(int x, int y) {
  coordinates tmp = snake[snake.size() - 1];
  int b = 0;
  if (x == food.x && y == food.y) {
    increaseScore();
    b = 1;
  } else if (bigFood.x != -1) {
    int xx = bigFood.x, yy = bigFood.y;
    if ((x == xx && y == yy) || (x == xx + 1 && y == yy) || (x == xx && y == yy + 1) || (x == xx + 1 && y == yy + 1)) {
      commonScore += 4;
      increaseScore();
      b = 2;
    }
  }
  for (int i = snake.size() - 1; i > 0; --i) snake[i] = snake[i - 1];
  snake[0].x = x;
  snake[0].y = y;
  if (b) {
    snake.push_back(tmp);
    if (b == 1) generateFood();
    else {
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black);
      bigFood.x = -1;
    }
  } else tft.fillRect(tmp.x * 8, tmp.y * 8, 8, 8, black);
  drawSnakeHead();
  drawPartSnakeBody(snake[1].x, snake[1].y);
}

bool checkGameOverSW() {
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
      if (commonScore > bestSnakeWind) {
        bestSnakeWind = commonScore;          
        EEPROM.write(3, commonScore);
        EEPROM.commit();
      }
      snake.clear();
      return true;
    }
  }
  return false;
}

void moveSnake() {
  if (!digitalRead(top) && directionSnakeWind != 2) {
    directionSnakeWind = 0;
    if (!snake[0].y) drawRunSnake(snake[0].x, 29);
    else drawRunSnake(snake[0].x, snake[0].y - 1);
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
  } else {
    if (directionSnakeWind == 0) {
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

int newGameSnakeWind() {
  drawSubScreen(bestSnakeWind, 0);

  snake.clear();
  snake.push_back({15, 15});
  snake.push_back({14, 15});

  drawSnakeHead();
  drawPartSnakeBody(snake[1].x, snake[1].y);
  generateFood();

  directionSnakeWind = 1;

  while (1) {
    for (int i = 0; i < 100; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(100);
    }
    generateBigFood();
    for (int i = 0; i < 40; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(100);
    }
    if (bigFood.x != -1) {
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black);
      bigFood.x = -1;
    }
  }
}

int continueSnakeWind() {
  drawSubScreen(bestSnakeWind, commonScore);

  drawSnakeHead();
  for (int i = 1; i < snake.size(); ++i) drawPartSnakeBody(snake[i].x, snake[i].y);
  tft.fillRoundRect(food.x * 8, food.y * 8, 8, 8, 3, white);
  
  while (1) {
    for (int i = 0; i < 60; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(150);
    }
    generateBigFood();
    for (int i = 0; i < 30; ++i) {
      if (!digitalRead(enterPause)) return 0;
      moveSnake();
      if (checkGameOverSW()) return 1;
      delay(150);
    }
    if (bigFood.x != -1) {
      tft.fillRect(bigFood.x * 8, bigFood.y * 8, 16, 16, black);
      bigFood.x = -1;
    }
  }
}
