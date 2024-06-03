int xMouseMaze, yMouseMaze, sizeBlankMaze, sizeWallMaze, edgeMazeReal, edgeMazeVirtual, borMouseMaze, sizeMouseMaze;

// Matrix of wall maze
bool maze[3481], rowMaze[30][29], colMaze[30][29];

// Convert maze 1D to maze 2D
void saveMaze() {
  for (int y = 0; y < edgeMazeVirtual; ++y) {
    for (int x = 0; x < edgeMazeVirtual; ++x) {
      if (maze[y + edgeMazeVirtual * x]) {  
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = true;
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = true;
      } else {
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = false;
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = false;
      }
    }
  }
}

// Build maze
void carveMaze(int x, int y) {
  int x1Tmp, y1Tmp, x2Tmp, y2Tmp, dxTmp, dyTmp;
  int dirTmp = random(4), countTmp = 0;
  while (countTmp < 4) {
    dxTmp = dyTmp = 0;

    if (dirTmp == 0) dxTmp = 1;
    else if (dirTmp == 1) dyTmp = 1;
    else if (dirTmp == 2) dxTmp = -1;
    else dyTmp = -1;

    x1Tmp = x + dxTmp;
    y1Tmp = y + dyTmp;
    x2Tmp = x1Tmp + dxTmp;
    y2Tmp = y1Tmp + dyTmp;

    // Check maze is always soluted
    if (x2Tmp > 0 && x2Tmp < edgeMazeVirtual && y2Tmp > 0 && y2Tmp < edgeMazeVirtual && maze[y1Tmp * edgeMazeVirtual + x1Tmp] == 1 && maze[y2Tmp * edgeMazeVirtual + x2Tmp] == 1) {
      maze[y1Tmp * edgeMazeVirtual + x1Tmp] = maze[y2Tmp * edgeMazeVirtual + x2Tmp] = false;
      x = x2Tmp; 
      y = y2Tmp;
      dirTmp = random(4);
      countTmp = 0;
    } else {
      dirTmp = (dirTmp + 1) % 4;
      ++countTmp;
    }
  }
}

// Generate maze 1D
void generateMaze() {
  int edgeEdgeTmp = edgeMazeVirtual * edgeMazeVirtual;
  for (int x = 0; x < edgeEdgeTmp; ++x) maze[x] = true;
  maze[edgeMazeVirtual + 1] = false;
  for (int y = 1; y < edgeMazeVirtual; y += 2) {
    for (int x = 1; x < edgeMazeVirtual; x += 2) carveMaze(x, y);
  }
  maze[1] = maze[edgeEdgeTmp - 2] = false;
}

// Mouse moves top, right, bottom, left
bool moveMouseMaze() {
  if (!digitalRead(top) && yMouseMaze && !rowMaze[yMouseMaze][xMouseMaze]) {
    tft.fillRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, black);
    tft.fillRoundRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, --yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);
    return false;
  }  

  if (!digitalRead(right) && !colMaze[xMouseMaze + 1][yMouseMaze]) {
    tft.fillRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, black);
    if (xMouseMaze == edgeMazeReal - 2) return true;
    tft.fillRoundRect(++xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);
    return false;
  }

  if (!digitalRead(bottom) && yMouseMaze != edgeMazeReal - 1 && !rowMaze[yMouseMaze + 1][xMouseMaze]) {
    tft.fillRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, black);
    tft.fillRoundRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, ++yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);
    return false;
  }

  if (!digitalRead(left) && xMouseMaze && !colMaze[xMouseMaze][yMouseMaze]) {
    tft.fillRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, black);
    tft.fillRoundRect(--xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);
    return false;
  }

  return false;
}

void drawMaze() {
  int edge1Tmp = edgeMazeReal - 1;

  for (int i = 1; i < edge1Tmp; ++i) {
    for (int j = 0; j < edge1Tmp; ++j) {
      if (rowMaze[i][j]) tft.fillRect(j * sizeBlankMaze, i * sizeBlankMaze, sizeBlankMaze, sizeWallMaze, red);
    }
  }

  for (int i = 1; i < edge1Tmp; ++i) {
    for (int j = 0; j < edge1Tmp; ++j) {
      if (colMaze[i][j]) tft.fillRect(i * sizeBlankMaze, j * sizeBlankMaze, sizeWallMaze, sizeBlankMaze, red);
    }
  }
}

void drawBorderMaze() {
  tft.fillRect(0, sizeBlankMaze, sizeWallMaze, (edgeMazeReal - 2) * sizeBlankMaze, red);
  tft.fillRect((edgeMazeReal - 1) * sizeBlankMaze, 0, sizeWallMaze, (edgeMazeReal - 1) * sizeBlankMaze - sizeMouseMaze, red);
  tft.fillRect(0, 0, (edgeMazeReal - 1) * sizeBlankMaze, sizeWallMaze, red);
  tft.fillRect(0, (edgeMazeReal - 1) * sizeBlankMaze, (edgeMazeReal - 1) * sizeBlankMaze, sizeWallMaze, red);
}

void gameOverMaze() {
  switch (sizeBlankMaze) {
    case 16:
      if (commonScore < bestMazeEasy || !bestMazeEasy) {
        bestMazeEasy = commonScore;
        EEPROM.write(currentPlayer + addressBestMazeEasy, commonScore);
        EEPROM.commit();
      }
      break;
    case 12:
      if (commonScore < bestMazeMedium || !bestMazeMedium) {
        bestMazeMedium = commonScore;
        EEPROM.write(currentPlayer + addressBestMazeMedium, commonScore);
        EEPROM.commit();
      }
      break;
    default:
      if (commonScore < bestMazeHard || !bestMazeHard) {
        bestMazeHard = commonScore;
        EEPROM.write(currentPlayer + addressBestMazeHard, commonScore);
        EEPROM.commit();
      }
  }
}

void drawSubScreenMaze(int score) {
  switch (sizeBlankMaze) {
    case 16:
      drawSubScreen(bestMazeEasy, score);
      break;
    case 12:
      drawSubScreen(bestMazeMedium, score);
      break;
    default:
      drawSubScreen(bestMazeHard, score);
  }
}

int newGameMaze() {
  memset(maze, false, sizeof(maze));
  memset(rowMaze, false, sizeof(rowMaze));
  memset(colMaze, false, sizeof(colMaze));

  // Select size and level of maze
  // Easy is 15x15. Medium is 20x20. Hard is 30x30
  switch (selectThree(false, "--EASY--", "-MEDIUM-", "---HARD---")) {
    case 0: 
      sizeBlankMaze = 16;
      sizeWallMaze = 4;
      borMouseMaze = 3;
      edgeMazeReal = 15;
      edgeMazeVirtual = 29;
      sizeMouseMaze = 12;
      break;
    case 1:
      sizeBlankMaze = 12;
      sizeWallMaze = 3;
      borMouseMaze = 2;
      edgeMazeReal = 20;
      edgeMazeVirtual = 39;
      sizeMouseMaze = 9;
      break; 
    default:
      sizeBlankMaze = 8;
      sizeWallMaze = 2;
      borMouseMaze = 1;
      edgeMazeReal = 30;
      edgeMazeVirtual = 59;
      sizeMouseMaze = 6;
  }
  
  generateMaze();
  saveMaze();

  drawSubScreenMaze(0);
  drawBorderMaze();
  drawMaze();

  xMouseMaze = 0;
  yMouseMaze = 0;
  tft.fillRoundRect(sizeWallMaze, sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);

  // Maze actives
  while (1) {
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(pau)) return 0;
      if (moveMouseMaze()) {
        gameOverMaze();
        return 1;
      }
      delay(100);
    }
    increaseScore();
    if (commonScore % 5 == 0) tone(buzzer, 349, 120);
  }
}

int continueMaze() {
  drawSubScreenMaze(commonScore);
  drawBorderMaze();
  drawMaze();

  tft.fillRoundRect(xMouseMaze * sizeBlankMaze + sizeWallMaze, yMouseMaze * sizeBlankMaze + sizeWallMaze, sizeMouseMaze, sizeMouseMaze, borMouseMaze, green);

  // Maze actives
  while (1) {
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(pau)) return 0;
      if (moveMouseMaze()) {
        gameOverMaze();
        return 1;
      }
      delay(100);
    }
    increaseScore();
    if (commonScore % 5 == 0) tone(buzzer, 349, 120);
  }
}