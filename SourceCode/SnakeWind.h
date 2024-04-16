int bestSnakeWind = 0, directionSnakeWind;

std::vector<coordinates> snake;

coordinates foodSnakeWind;

void drawBorder() {
  tft.fillRect(0, 0, 240, 8, red);
  tft.fillRect(0, 232, 240, 8, red);
  tft.fillRect(0, 8, 8, 224, red);
  tft.fillRect(232, 8, 8, 224, red);
}

void drawSnakeHead() {
  tft.fillRoundRect(snake[0].x * 8, snake[0].y * 8, 8, 8, 1, yellow);
  tft.fillRoundRect(snake[0].x * 8 + 3, snake[0].y * 8 + 2, 3, 3, 1, black);
}

void drawPartSnakeBody(int x, int y) {
  tft.fillRoundRect(x * 8, y * 8, 8, 8, 1, green);
}

void generateFoodSW() {
  while (1) {
    int x = random(1, 29), y = random(1, 29);
    bool b = false;
    for (int i = 0; i < snake.size(); ++i) {
      if (snake[i].x == x && snake[i].y == y) {
        b = true;
        break;
      }
    }
    if (b) continue;
    foodSnakeWind.x = x;
    foodSnakeWind.y = y;
    tft.fillRoundRect(x * 8, y * 8, 8, 8, 3, white);
    return;
  }
}

void drawRunSnake(int x, int y) {
  coordinates tmp = snake[snake.size() - 1];
  bool b = false;
  if (x == foodSnakeWind.x && y == foodSnakeWind.y) {
    increaseScore();
    b = true;
  }
  for (int i = snake.size() - 1; i > 0; --i) snake[i] = snake[i - 1];
  snake[0].x = x;
  snake[0].y = y;
  drawSnakeHead();
  drawPartSnakeBody(snake[1].x, snake[1].y);
  if (b) {
    generateFoodSW();
    snake.push_back(tmp);
  } else tft.fillRect(tmp.x * 8, tmp.y * 8, 8, 8, black);
}

bool checkGameOverSW() {
  int x = snake[0].x, y = snake[0].y;
  if (x == 0 || x == 29) {
    if (commonScore > bestSnakeWind) bestSnakeWind = commonScore;
    snake.clear();
    return true;
  }
  if (y == 0 || y == 29) {
    if (commonScore > bestSnakeWind) bestSnakeWind = commonScore;
    snake.clear();
    return true;
  }
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[i].x == x && snake[i].y == y) {
      if (commonScore > bestSnakeWind) bestSnakeWind = commonScore;
      snake.clear();
      return true;
    }
  }
  return false;
}

void moveSnake() {
  if (!digitalRead(top) && directionSnakeWind != 2) {
    directionSnakeWind = 0;
    drawRunSnake(snake[0].x, snake[0].y - 1);
  } else if (!digitalRead(right) && directionSnakeWind != 3) {
    directionSnakeWind = 1;
    drawRunSnake(snake[0].x + 1, snake[0].y);
  } else if (!digitalRead(bottom) && directionSnakeWind != 0) {
    directionSnakeWind = 2;
    drawRunSnake(snake[0].x, snake[0].y + 1);
  } else if (!digitalRead(left) && directionSnakeWind != 1) {
    directionSnakeWind = 3;
    drawRunSnake(snake[0].x - 1, snake[0].y);
  } else {
    if (directionSnakeWind == 0) drawRunSnake(snake[0].x, snake[0].y - 1);
    else if (directionSnakeWind == 1) drawRunSnake(snake[0].x + 1, snake[0].y);
    else if (directionSnakeWind == 2) drawRunSnake(snake[0].x, snake[0].y + 1);
    else drawRunSnake(snake[0].x - 1, snake[0].y);
  }
}

int newGameSnakeWind() {
  drawSubScreen(bestSnakeWind, 0);
  drawBorder();

  snake.push_back({15, 15});
  snake.push_back({14, 15});

  drawSnakeHead();
  drawPartSnakeBody(snake[1].x, snake[1].y);
  generateFoodSW();

  directionSnakeWind = 1;

  while (1) {
    if (!digitalRead(enterPause)) return 0;
    moveSnake();
    if (checkGameOverSW()) return 1;
    delay(150);
  }
}

int continueSnakeWind() {
  drawSubScreen(bestSnakeWind, commonScore);
  drawBorder();

  drawSnakeHead();
  for (int i = 1; i < snake.size(); ++i) drawPartSnakeBody(snake[i].x, snake[i].y);
  tft.fillRoundRect(foodSnakeWind.x * 8, foodSnakeWind.y * 8, 8, 8, 3, white);
  
  while (1) {
    if (!digitalRead(enterPause)) return 0;
    moveSnake();
    if (checkGameOverSW()) return 1;
    delay(150);
  }
}