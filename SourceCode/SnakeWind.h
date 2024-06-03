int directionSnakeWind, speedSnakeWind, mapSnakeWind;
bool wallSnakeWind[30][30];

std::vector<coordinates> snakeWind;

coordinates foodSnakeWind, bigFoodSnakeWind;

void drawHeadSnakeWind() {
  tft.fillRoundRect(snakeWind[0].x * 8, snakeWind[0].y * 8, 8, 8, 1, yellow);
  tft.fillRoundRect(snakeWind[0].x * 8 + 3, snakeWind[0].y * 8 + 2, 3, 3, 1, black);
}

void generateFoodSnakeWind() {
  while (1) {
    int x = random(30), y = random(30);
    if (wallSnakeWind[x][y]) continue; // Food is not in wall
    bool b = false;
    for (int i = 0; i < snakeWind.size(); ++i) {
      // Food is not in snake
      if (snakeWind[i].x == x && snakeWind[i].y == y) {
        b = true;
        break;
      }
    }

    // Food is not in big food
    if ((x == bigFoodSnakeWind.x && y == bigFoodSnakeWind.y) || (x == bigFoodSnakeWind.x + 1 && y == bigFoodSnakeWind.y) || (x == bigFoodSnakeWind.x && y == bigFoodSnakeWind.y + 1) 
                                                              || (x == bigFoodSnakeWind.x + 1 && y == bigFoodSnakeWind.y + 1)) b = true;
    if (b) continue;
    foodSnakeWind.x = x;
    foodSnakeWind.y = y;
    tft.fillRoundRect(x * 8, y * 8, 8, 8, 3, white);
    return;
  }
}

void generateBigFoodSnakeWind() {
  while (1) {
    int x = random(29), y = random(29);

    // Big food is not in wall
    if (wallSnakeWind[x][y] || wallSnakeWind[x + 1][y] || wallSnakeWind[x][y + 1] || wallSnakeWind[x + 1][y + 1]) continue;
    bool b = false;
    for (int i = 0; i < snakeWind.size(); ++i) {
      // Big food is not in snake
      if ((snakeWind[i].x == x && snakeWind[i].y == y) || (snakeWind[i].x == x + 1 && snakeWind[i].y == y) || (snakeWind[i].x == x && snakeWind[i].y == y + 1) 
                                                        || (snakeWind[i].x == x + 1 && snakeWind[i].y == y + 1)) {
        b = true;
        break;
      }

      // Big food does not have food
      if ((foodSnakeWind.x == x && foodSnakeWind.y == y) || (foodSnakeWind.x == x + 1 && foodSnakeWind.y == y) || (foodSnakeWind.x == x && foodSnakeWind.y == y + 1) 
                                                          || (foodSnakeWind.x == x + 1 && foodSnakeWind.y == y + 1)) {
        b = true;
        break;
      }
    }
    if (b) continue;
    bigFoodSnakeWind.x = x;
    bigFoodSnakeWind.y = y;
    tft.fillRoundRect(x * 8, y * 8, 16, 16, 5, red);
    return;
  }
}

void drawRunSnakeWind(int x, int y) {
  coordinates tmp = snakeWind[snakeWind.size() - 1];
  int b = 0;
  if (x == foodSnakeWind.x && y == foodSnakeWind.y) {
    tone(buzzer, 349, 120);
    increaseScore();
    b = 1;
  } else if (bigFoodSnakeWind.x != -1) { // Big food is exist
    // Eat big food
    if ((x == bigFoodSnakeWind.x && y == bigFoodSnakeWind.y) || (x == bigFoodSnakeWind.x + 1 && y == bigFoodSnakeWind.y) || (x == bigFoodSnakeWind.x && y == bigFoodSnakeWind.y + 1) 
                                                              || (x == bigFoodSnakeWind.x + 1 && y == bigFoodSnakeWind.y + 1)) {
      commonScore += 4;
      tone(buzzer, 1349, 120);
      increaseScore();
      b = 2;
    }
  }
  
  // Snake-run animation
  for (int i = snakeWind.size() - 1; i > 0; --i) snakeWind[i] = snakeWind[i - 1];
  snakeWind[0].x = x;
  snakeWind[0].y = y;
  if (b) {
    snakeWind.push_back(tmp);
    if (b == 1) generateFoodSnakeWind();
    else {
      tft.fillRect(bigFoodSnakeWind.x * 8, bigFoodSnakeWind.y * 8, 16, 16, black);
      bigFoodSnakeWind.x = -1;
    }
  } else tft.fillRect(tmp.x * 8, tmp.y * 8, 8, 8, black);
  drawHeadSnakeWind();
  tft.fillRoundRect(snakeWind[1].x * 8, snakeWind[1].y * 8, 8, 8, 1, green);
}

// Update best snake wind with map and speed
void subCheckGameOverSnakeWind() {
  switch (mapSnakeWind) {
    case 0: 
      if (speedSnakeWind == 100 && commonScore > bestSnakeWindFreeEasy) {
        bestSnakeWindFreeEasy = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindFreeEasy, commonScore);
        EEPROM.commit();
      } else if (speedSnakeWind == 80 && commonScore > bestSnakeWindFreeMedium) {
        bestSnakeWindFreeMedium = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindFreeMedium, commonScore);
        EEPROM.commit();
      } else if (commonScore > bestSnakeWindFreeHard) {
        bestSnakeWindFreeHard = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindFreeHard, commonScore);
        EEPROM.commit();
      }
      break;
    case 1:
      if (speedSnakeWind == 100 && commonScore > bestSnakeWindHomeEasy) {
        bestSnakeWindHomeEasy = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindHomeEasy, commonScore);
        EEPROM.commit();
      } else if (speedSnakeWind == 80 && commonScore > bestSnakeWindHomeMedium) {
        bestSnakeWindHomeMedium = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindHomeMedium, commonScore);
        EEPROM.commit();
      } else if (commonScore > bestSnakeWindHomeHard) {
        bestSnakeWindHomeHard = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindHomeHard, commonScore);
        EEPROM.commit();
      }
      break;
    default:
      if (speedSnakeWind == 100 && commonScore > bestSnakeWindParkEasy) {
        bestSnakeWindParkEasy = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindParkEasy, commonScore);
        EEPROM.commit();
      } else if (speedSnakeWind == 80 && commonScore > bestSnakeWindParkMedium) {
        bestSnakeWindParkMedium = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindParkMedium, commonScore);
        EEPROM.commit();
      } else if (commonScore > bestSnakeWindParkHard) {
        bestSnakeWindParkHard = commonScore;          
        EEPROM.write(currentPlayer + addressBestSnakeWindParkHard, commonScore);
        EEPROM.commit();
      }
  }
}

bool checkGameOverSnakeWind() {
  // Touch wall
  if (wallSnakeWind[snakeWind[0].x][snakeWind[0].y]) {
    subCheckGameOverSnakeWind();
    return true;
  }
  for (int i = 1; i < snakeWind.size(); ++i) {
    // Eat body
    if (snakeWind[i].x == snakeWind[0].x && snakeWind[i].y == snakeWind[0].y) {
      subCheckGameOverSnakeWind();
      return true;
    }
  }
  return false;
}

// Snake moves top. right, bottom, left
void moveSnakeWind() {
  if (!digitalRead(top) && directionSnakeWind != 2) {
    directionSnakeWind = 0;
    if (!snakeWind[0].y) drawRunSnakeWind(snakeWind[0].x, 29);
    else drawRunSnakeWind(snakeWind[0].x, snakeWind[0].y - 1);
  } else if (!digitalRead(right) && directionSnakeWind != 3) {
    directionSnakeWind = 1;
    if (snakeWind[0].x == 29) drawRunSnakeWind(0, snakeWind[0].y);
    else drawRunSnakeWind(snakeWind[0].x + 1, snakeWind[0].y);
  } else if (!digitalRead(bottom) && directionSnakeWind != 0) {
    directionSnakeWind = 2;
    if (snakeWind[0].y == 29) drawRunSnakeWind(snakeWind[0].x, 0);
    else drawRunSnakeWind(snakeWind[0].x, snakeWind[0].y + 1);
  } else if (!digitalRead(left) && directionSnakeWind != 1) {
    directionSnakeWind = 3;
    if (!snakeWind[0].x) drawRunSnakeWind(29, snakeWind[0].y);
    else drawRunSnakeWind(snakeWind[0].x - 1, snakeWind[0].y);
  } else {
    if (directionSnakeWind == 0) {
      if (!snakeWind[0].y) drawRunSnakeWind(snakeWind[0].x, 29);
      else drawRunSnakeWind(snakeWind[0].x, snakeWind[0].y - 1);
    } else if (directionSnakeWind == 1) {
      if (snakeWind[0].x == 29) drawRunSnakeWind(0, snakeWind[0].y);
      else drawRunSnakeWind(snakeWind[0].x + 1, snakeWind[0].y);
    } else if (directionSnakeWind == 2) {
      if (snakeWind[0].y == 29) drawRunSnakeWind(snakeWind[0].x, 0);
      else drawRunSnakeWind(snakeWind[0].x, snakeWind[0].y + 1);
    } else {
      if (!snakeWind[0].x) drawRunSnakeWind(29, snakeWind[0].y);
      else drawRunSnakeWind(snakeWind[0].x - 1, snakeWind[0].y);
    }
  }
}

void drawMapSnakeWind() {
  if (mapSnakeWind == 1) { // Map Home
    tft.fillRect(0, 0, 240, 8, red);
    tft.fillRect(0, 232, 240, 8, red);
    tft.fillRect(0, 8, 8, 224, red);
    tft.fillRect(232, 8, 8, 224, red);
  } else if (mapSnakeWind == 2) { // Map Park
    tft.fillRect(0, 0, 80, 8, red);
    tft.fillRect(160, 0, 80, 8, red);
    tft.fillRect(0, 232, 80, 8, red);
    tft.fillRect(160, 232, 80, 8, red);
    tft.fillRect(0, 8, 8, 72, red);
    tft.fillRect(232, 8, 8, 72, red);
    tft.fillRect(0, 160, 8, 72, red);
    tft.fillRect(232, 160, 8, 72, red);
    
    tft.fillRect(48, 48, 48, 8, red);
    tft.fillRect(144, 48, 48, 8, red);
    tft.fillRect(48, 184, 48, 8, red);
    tft.fillRect(144, 184, 48, 8, red);
    tft.fillRect(48, 56, 8, 40, red);
    tft.fillRect(48, 144, 8, 40, red);
    tft.fillRect(184, 56, 8, 40, red);
    tft.fillRect(184, 144, 8, 40, red);
  }
}

void drawSubScreenSnakeWind(int score) {
  switch(mapSnakeWind) {
    case 0:
      if (speedSnakeWind == 100) drawSubScreen(bestSnakeWindFreeEasy, score);
      else if (speedSnakeWind == 80) drawSubScreen(bestSnakeWindFreeMedium, score);
      else drawSubScreen(bestSnakeWindFreeHard, score);
      break;
    case 1:
      if (speedSnakeWind == 100) drawSubScreen(bestSnakeWindHomeEasy, score);
      else if (speedSnakeWind == 80) drawSubScreen(bestSnakeWindHomeMedium, score);
      else drawSubScreen(bestSnakeWindHomeHard, score);
      break;
    default:
      if (speedSnakeWind == 100) drawSubScreen(bestSnakeWindParkEasy, score);
      else if (speedSnakeWind == 80) drawSubScreen(bestSnakeWindParkMedium, score);
      else drawSubScreen(bestSnakeWindParkHard, score);
  }
  drawMapSnakeWind();
}

int newGameSnakeWind() {
  memset(wallSnakeWind, false, sizeof(wallSnakeWind));
  switch (selectThree(false, "--FREE--", "--HOME--", "---PARK---")) {
    case 0:
      mapSnakeWind = 0; 
      break;
    case 1:
      // Configure Home wall
      wallSnakeWind[0][0] = wallSnakeWind[0][1] = wallSnakeWind[0][2] = wallSnakeWind[0][3] = wallSnakeWind[0][4] = wallSnakeWind[0][5] 
                          = wallSnakeWind[0][6] = wallSnakeWind[0][7] = wallSnakeWind[0][8] = wallSnakeWind[0][9] = true;

      wallSnakeWind[0][10] = wallSnakeWind[0][11] = wallSnakeWind[0][12] = wallSnakeWind[0][13] = wallSnakeWind[0][14] = wallSnakeWind[0][15] 
                            = wallSnakeWind[0][16] = wallSnakeWind[0][17] = wallSnakeWind[0][18] = wallSnakeWind[0][19] = true;

      wallSnakeWind[0][20] = wallSnakeWind[0][21] = wallSnakeWind[0][22] = wallSnakeWind[0][23] = wallSnakeWind[0][24] = wallSnakeWind[0][25] 
                            = wallSnakeWind[0][26] = wallSnakeWind[0][27] = wallSnakeWind[0][28] = wallSnakeWind[0][29] = true;

      wallSnakeWind[29][0] = wallSnakeWind[29][1] = wallSnakeWind[29][2] = wallSnakeWind[29][3] = wallSnakeWind[29][4] = wallSnakeWind[29][5]
                            = wallSnakeWind[29][6] = wallSnakeWind[29][7] = wallSnakeWind[29][8] = wallSnakeWind[29][9] = true;
      wallSnakeWind[29][10] = wallSnakeWind[29][11] = wallSnakeWind[29][12] = wallSnakeWind[29][13] = wallSnakeWind[29][14] = wallSnakeWind[29][15] 
                            = wallSnakeWind[29][16] = wallSnakeWind[29][17] = wallSnakeWind[29][18] = wallSnakeWind[29][19] = true;
      wallSnakeWind[29][20] = wallSnakeWind[29][21] = wallSnakeWind[29][22] = wallSnakeWind[29][23] = wallSnakeWind[29][24] = wallSnakeWind[29][25] 
                            = wallSnakeWind[29][26] = wallSnakeWind[29][27] = wallSnakeWind[29][28] = wallSnakeWind[29][29] = true;

      wallSnakeWind[1][0] = wallSnakeWind[2][0] = wallSnakeWind[3][0] = wallSnakeWind[4][0] = wallSnakeWind[5][0] = wallSnakeWind[6][0]
                          = wallSnakeWind[7][0] = wallSnakeWind[8][0] = wallSnakeWind[9][0] = true;
      wallSnakeWind[10][0] = wallSnakeWind[11][0] = wallSnakeWind[12][0] = wallSnakeWind[13][0] = wallSnakeWind[14][0] = wallSnakeWind[15][0] 
                            = wallSnakeWind[16][0] = wallSnakeWind[17][0] = wallSnakeWind[18][0] = wallSnakeWind[19][0] = true;
      wallSnakeWind[20][0] = wallSnakeWind[21][0] = wallSnakeWind[22][0] = wallSnakeWind[23][0] = wallSnakeWind[24][0] = wallSnakeWind[25][0] 
                            = wallSnakeWind[26][0] = wallSnakeWind[27][0] = wallSnakeWind[28][0] = true;

      wallSnakeWind[1][29] = wallSnakeWind[2][29] = wallSnakeWind[3][29] = wallSnakeWind[4][29] = wallSnakeWind[5][29] = wallSnakeWind[6][29] 
                            = wallSnakeWind[7][29] = wallSnakeWind[8][29] = wallSnakeWind[9][29] = true;
      wallSnakeWind[10][29] = wallSnakeWind[11][29] = wallSnakeWind[12][29] = wallSnakeWind[13][29] = wallSnakeWind[14][29] = wallSnakeWind[15][29] 
                            = wallSnakeWind[16][29] = wallSnakeWind[17][29] = wallSnakeWind[18][29] = wallSnakeWind[19][29] = true;
      wallSnakeWind[20][29] = wallSnakeWind[21][29] = wallSnakeWind[22][29] = wallSnakeWind[23][29] = wallSnakeWind[24][29] = wallSnakeWind[25][29] 
                            = wallSnakeWind[26][29] = wallSnakeWind[27][29] = wallSnakeWind[28][29] = true;

      mapSnakeWind = 1;
      break;
    default:
      // Configure Park wall
      wallSnakeWind[0][0] = wallSnakeWind[0][1] = wallSnakeWind[0][2] = wallSnakeWind[0][3] = wallSnakeWind[0][4] = wallSnakeWind[0][5] 
                          = wallSnakeWind[0][6] = wallSnakeWind[0][7] = wallSnakeWind[0][8] = wallSnakeWind[0][9] = true;
      wallSnakeWind[0][20] = wallSnakeWind[0][21] = wallSnakeWind[0][22] = wallSnakeWind[0][23] = wallSnakeWind[0][24] = wallSnakeWind[0][25] 
                            = wallSnakeWind[0][26] = wallSnakeWind[0][27] = wallSnakeWind[0][28] = wallSnakeWind[0][29] = true;

      wallSnakeWind[29][0] = wallSnakeWind[29][1] = wallSnakeWind[29][2] = wallSnakeWind[29][3] = wallSnakeWind[29][4] = wallSnakeWind[29][5] 
                            = wallSnakeWind[29][6] = wallSnakeWind[29][7] = wallSnakeWind[29][8] = wallSnakeWind[29][9] = true;
      wallSnakeWind[29][20] = wallSnakeWind[29][21] = wallSnakeWind[29][22] = wallSnakeWind[29][23] = wallSnakeWind[29][24] = wallSnakeWind[29][25] 
                            = wallSnakeWind[29][26] = wallSnakeWind[29][27] = wallSnakeWind[29][28] = wallSnakeWind[29][29] = true;

      wallSnakeWind[1][0] = wallSnakeWind[2][0] = wallSnakeWind[3][0] = wallSnakeWind[4][0] = wallSnakeWind[5][0] = wallSnakeWind[6][0] 
                          = wallSnakeWind[7][0] = wallSnakeWind[8][0] = wallSnakeWind[9][0] = true;
      wallSnakeWind[20][0] = wallSnakeWind[21][0] = wallSnakeWind[22][0] = wallSnakeWind[23][0] = wallSnakeWind[24][0] = wallSnakeWind[25][0] 
                            = wallSnakeWind[26][0] = wallSnakeWind[27][0] = wallSnakeWind[28][0] = true;

      wallSnakeWind[1][29] = wallSnakeWind[2][29] = wallSnakeWind[3][29] = wallSnakeWind[4][29] = wallSnakeWind[5][29] = wallSnakeWind[6][29] 
                            = wallSnakeWind[7][29] = wallSnakeWind[8][29] = wallSnakeWind[9][29] = true;
      wallSnakeWind[20][29] = wallSnakeWind[21][29] = wallSnakeWind[22][29] = wallSnakeWind[23][29] = wallSnakeWind[24][29] = wallSnakeWind[25][29] 
                            = wallSnakeWind[26][29] = wallSnakeWind[27][29] = wallSnakeWind[28][29] = true;



      wallSnakeWind[6][6] = wallSnakeWind[6][7] = wallSnakeWind[6][8] = wallSnakeWind[6][9] = wallSnakeWind[6][10] = wallSnakeWind[6][11] = true;
      wallSnakeWind[6][18] = wallSnakeWind[6][19] = wallSnakeWind[6][20] = wallSnakeWind[6][21] = wallSnakeWind[6][22] = wallSnakeWind[6][23] = true;

      wallSnakeWind[23][6] = wallSnakeWind[23][7] = wallSnakeWind[23][8] = wallSnakeWind[23][9] = wallSnakeWind[23][10] = wallSnakeWind[23][11] = true;
      wallSnakeWind[23][18] = wallSnakeWind[23][19] = wallSnakeWind[23][20] = wallSnakeWind[23][21] = wallSnakeWind[23][22] = wallSnakeWind[23][23] = true;

      wallSnakeWind[7][6] = wallSnakeWind[8][6] = wallSnakeWind[9][6] = wallSnakeWind[10][6] = wallSnakeWind[11][6] = true;
      wallSnakeWind[18][6] = wallSnakeWind[19][6] = wallSnakeWind[20][6] = wallSnakeWind[21][6] = wallSnakeWind[22][6] = true;

      wallSnakeWind[7][23] = wallSnakeWind[8][23] = wallSnakeWind[9][23] = wallSnakeWind[10][23] = wallSnakeWind[11][23] = true;
      wallSnakeWind[18][23] = wallSnakeWind[19][23] = wallSnakeWind[20][23] = wallSnakeWind[21][23] = wallSnakeWind[22][23] = true;

      mapSnakeWind = 2;
  }

  switch (selectThree(false, "--EASY--", "-MEDIUM-", "---HARD---")) {
    case 0: 
      speedSnakeWind = 100;
      break;
    case 1:
      speedSnakeWind = 80;
      break;
    default:
      speedSnakeWind = 60;
  }

  drawSubScreenSnakeWind(0);

  // Init snake wind game
  snakeWind.clear();
  snakeWind.push_back({15, 15});
  snakeWind.push_back({14, 15});

  drawHeadSnakeWind();
  tft.fillRoundRect(snakeWind[1].x * 8, snakeWind[1].y * 8, 8, 8, 1, green);
  generateFoodSnakeWind();

  directionSnakeWind = 1;

  // Snake wind actives
  while (1) {
    for (int i = 0; i < 100; ++i) {
      if (!digitalRead(pau)) return 0;
      moveSnakeWind();
      if (checkGameOverSnakeWind()) return 1;
      delay(speedSnakeWind);
    }
    generateBigFoodSnakeWind();
    for (int i = 0; i < 40; ++i) {
      if (!digitalRead(pau)) return 0;
      moveSnakeWind();
      if (checkGameOverSnakeWind()) return 1;
      delay(speedSnakeWind);
    }
    if (bigFoodSnakeWind.x != -1) {
      tft.fillRect(bigFoodSnakeWind.x * 8, bigFoodSnakeWind.y * 8, 16, 16, black);
      bigFoodSnakeWind.x = -1;
    }
  }
}

int continueSnakeWind() {
  // Continue statement
  drawSubScreenSnakeWind(commonScore);

  drawHeadSnakeWind();
  for (int i = 1; i < snakeWind.size(); ++i) tft.fillRoundRect(snakeWind[i].x * 8, snakeWind[i].y * 8, 8, 8, 1, green);
  tft.fillRoundRect(foodSnakeWind.x * 8, foodSnakeWind.y * 8, 8, 8, 3, white);
  if (bigFoodSnakeWind.x != -1) tft.fillRoundRect(bigFoodSnakeWind.x * 8, bigFoodSnakeWind.y * 8, 16, 16, 5, red);

  for (int i = 0; i < 20; ++i) {
    if (!digitalRead(pau)) return 0;
    moveSnakeWind();
    if (checkGameOverSnakeWind()) return 1;
    delay(speedSnakeWind);
  }
  if (bigFoodSnakeWind.x != -1) {
    tft.fillRect(bigFoodSnakeWind.x * 8, bigFoodSnakeWind.y * 8, 16, 16, black);
    bigFoodSnakeWind.x = -1;
  }
  
  // Snake wind actives
  while (1) {
    for (int i = 0; i < 100; ++i) {
      if (!digitalRead(pau)) return 0;
      moveSnakeWind();
      if (checkGameOverSnakeWind()) return 1;
      delay(speedSnakeWind);
    }
    generateBigFoodSnakeWind();
    for (int i = 0; i < 40; ++i) {
      if (!digitalRead(pau)) return 0;
      moveSnakeWind();
      if (checkGameOverSnakeWind()) return 1;
      delay(speedSnakeWind);
    }
    if (bigFoodSnakeWind.x != -1) {
      tft.fillRect(bigFoodSnakeWind.x * 8, bigFoodSnakeWind.y * 8, 16, 16, black);
      bigFoodSnakeWind.x = -1;
    }
  }
}