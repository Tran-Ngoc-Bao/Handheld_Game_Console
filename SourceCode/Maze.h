int bestMaze = 0, xMouse, yMouse;

char maze[841];

bool rowMaze[15][14], colMaze[15][14];

void saveMaze() {
  for (int y = 0; y < 29; ++y) {
    for (int x = 0; x < 29; ++x) {
      if (maze[y + 29 * x]) {  
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = true;
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = true;
      } else {
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = false;
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = false;
      }
    }
  }
}

void carveMaze(int x, int y) {
  int x1, y1, x2, y2, dx, dy;
  int dir = random(4), count = 0;
  while (count < 4) {
    dx = dy = 0;
    if (dir == 0) dx = 1;
    else if (dir == 1) dy = 1;
    else if (dir == 2) dx = -1;
    else dy = -1;
    x1 = x + dx;
    y1 = y + dy;
    x2 = x1 + dx;
    y2 = y1 + dy;
    if (x2 > 0 && x2 < 29 && y2 > 0 && y2 < 29 && maze[y1 * 29 + x1] == 1 && maze[y2 * 29 + x2] == 1) {
      maze[y1 * 29 + x1] = maze[y2 * 29 + x2] = 0;
      x = x2; 
      y = y2;
      dir = random(4);
      count = 0;
    } else {
      dir = (dir + 1) % 4;
      ++count;
    }
  }
}

void generateMaze() {
  for (int x = 0; x < 841; ++x) maze[x] = 1;
  maze[30] = 0;
  for (int y = 1; y < 29; y += 2) {
    for (int x = 1; x < 29; x += 2) carveMaze(x, y);
  }
  maze[1] = maze[839] = 0;
}

bool moveMouse() {
  if (!digitalRead(top) && yMouse && !rowMaze[yMouse][xMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    tft.fillRoundRect(xMouse * 16 + 10, --yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }  
  if (!digitalRead(right) && !colMaze[xMouse + 1][yMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    if (xMouse == 13) return true;
    tft.fillRoundRect(++xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }
  if (!digitalRead(bottom) && yMouse != 14 && !rowMaze[yMouse + 1][xMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    tft.fillRoundRect(xMouse * 16 + 10, ++yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }
  if (!digitalRead(left) && xMouse && !colMaze[xMouse][yMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    tft.fillRoundRect(--xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }
  return false;
}

int newGameMaze() {
  drawSubScreen(bestMaze, 0);

  tft.fillRect(6, 22, 4, 208, red);
  tft.fillRect(230, 6, 4, 212, red);
  tft.fillRect(6, 6, 224, 4, red);
  tft.fillRect(6, 230, 228, 4, red);

  generateMaze();
  saveMaze();

  for (int i = 1; i < 14; ++i) {
    int y = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (rowMaze[i][j]) tft.fillRect(j * 16 + 6, y + 6, 16, 4, red);
    }
  }

  for (int i = 1; i < 14; ++i) {
    int x = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (colMaze[i][j]) tft.fillRect(x + 6, j * 16 + 6, 4, 16, red);
    }
  }

  xMouse = 0;
  yMouse = 0;
  tft.fillRoundRect(10, 10, 12, 12, 3, green);

  while (1) {
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(enterPause)) return 0;
      if (moveMouse()) {
        if (commonScore < bestMaze || !bestMaze) bestMaze = commonScore;
        return 1;
      }
      delay(100);
    }
    increaseScore();
  }
}

int continueMaze() {
  drawSubScreen(bestMaze, 0);

  tft.fillRect(6, 22, 4, 208, red);
  tft.fillRect(230, 6, 4, 212, red);
  tft.fillRect(6, 6, 224, 4, red);
  tft.fillRect(6, 230, 228, 4, red);

  for (int i = 1; i < 14; ++i) {
    int y = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (rowMaze[i][j]) tft.fillRect(j * 16 + 6, y + 6, 16, 4, red);
    }
  }

  for (int i = 1; i < 14; ++i) {
    int x = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (colMaze[i][j]) tft.fillRect(x + 6, j * 16 + 6, 4, 16, red);
    }
  }

  tft.fillRoundRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);

  while (1) {
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(enterPause)) return 0;
      if (moveMouse()) {
        if (commonScore < bestMaze || !bestMaze) bestMaze = commonScore;
        return 1;
      }
      delay(100);
    }
    increaseScore();
  }
}