int yFlappyBird;

int heightArrayFlappyBird[31][2];

void drawLeftSewerFlappyBird(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawMidSewerFlappyBird(int x, int h) {
  tft.fillRect(x * 8, 0, 8, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 8, (19 - h) * 8, green);
}

void drawRightSewerFlappyBird(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, black);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, black);
  tft.fillRect(x * 8, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawSewerFlappyBird(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 16, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 24, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 24, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 16, (19 - h) * 8, green);
}

// Animation of sewers
void drawRunSewerFlappyBird() {
  for (int i = 0; i < 30; ++i) {
    if (heightArrayFlappyBird[i][0]) {
      switch (heightArrayFlappyBird[i][1]) {
        case 0: // If left sewer 
          heightArrayFlappyBird[i][1] = 1; 
          drawMidSewerFlappyBird(i, heightArrayFlappyBird[i][0]); // Draw mid sewer
          break;
        case 1: // If mid sewer
          heightArrayFlappyBird[i][1] = 2; 
          drawRightSewerFlappyBird(i, heightArrayFlappyBird[i][0]); // Draw right sewer
          break;
        default: // If right sewer
          tft.fillRect(i * 8, 0, 8, heightArrayFlappyBird[i][0] * 8, black);
          tft.fillRect(i * 8, (heightArrayFlappyBird[i][0] + 9) * 8, 8, (21 - heightArrayFlappyBird[i][0]) * 8, black);
          heightArrayFlappyBird[i][0] = 0;
      }
    } else if (heightArrayFlappyBird[i + 1][0]) { // If next left sewer
      heightArrayFlappyBird[i][0] = heightArrayFlappyBird[i + 1][0];
      heightArrayFlappyBird[i][1] = 0;
      drawLeftSewerFlappyBird(i, heightArrayFlappyBird[i][0]);
    }
  }
}

void drawBirdFlapyBird() { 
  tft.fillRoundRect(36, yFlappyBird * 8, 16, 16, 5, yellow);
  tft.fillRoundRect(44, yFlappyBird * 8, 8, 8, 5, white);
  tft.fillRoundRect(30, yFlappyBird * 8 + 4, 10, 8, 5, white);
  tft.fillRoundRect(46, yFlappyBird * 8 + 2, 3, 3, 1, black);
  tft.fillRoundRect(48, yFlappyBird * 8 + 10, 8, 4, 3, red);
}

bool checkGameOverFlappyBird() {
  if (heightArrayFlappyBird[4][0]) { 
    // If touch sewer 
    if (heightArrayFlappyBird[4][0] >= yFlappyBird || yFlappyBird >= heightArrayFlappyBird[4][0] + 7) {
      // Update best flappy bird
      if (commonScore > bestFlappyBird) {
        bestFlappyBird = commonScore;
        EEPROM.write(addressBestFlappyBird, commonScore);
        EEPROM.commit(); 
      }
      return true;
    } 
  }

  if (heightArrayFlappyBird[6][0]) {
    if (heightArrayFlappyBird[6][0] >= yFlappyBird || yFlappyBird >= heightArrayFlappyBird[6][0] + 7) {
      if (commonScore > bestFlappyBird) {
        bestFlappyBird = commonScore;
        EEPROM.write(addressBestFlappyBird, commonScore);
        EEPROM.commit();
      }
      return true;
    }
  }

  return false;
}

void birdFlyFlappyBird() { 
  if (!digitalRead(top)) { 
    tft.fillRect(36, yFlappyBird * 8, 16, 16, black);
    tft.fillRect(30, yFlappyBird * 8 + 4, 6, 12, black);
    tft.fillRect(52, yFlappyBird * 8 + 10, 4, 4, black);

    // Animation of flapping
    --yFlappyBird; 
    tft.fillRoundRect(36, yFlappyBird * 8, 16, 16, 5, yellow);
    tft.fillRoundRect(44, yFlappyBird * 8, 8, 8, 5, white);
    tft.fillRoundRect(30, yFlappyBird * 8 + 8, 10, 8, 5, white);
    tft.fillRoundRect(46, yFlappyBird * 8 + 2, 3, 3, 1, black);
    tft.fillRoundRect(48, yFlappyBird * 8 + 10, 8, 4, 3, red);
    delay(100);

    tft.fillRect(30, yFlappyBird * 8 + 8, 8, 8, black);
    tft.fillRoundRect(36, yFlappyBird * 8 + 10, 6, 6, 5, yellow);
    tft.fillRoundRect(30, yFlappyBird * 8 + 4, 10, 8, 5, white);
  }
}

void birdFallFlappyBird() {
  tft.fillRect(36, yFlappyBird * 8, 16, 16, black);
  tft.fillRect(30, yFlappyBird * 8 + 4, 6, 12, black);
  tft.fillRect(52, yFlappyBird * 8 + 10, 4, 4, black);
  ++yFlappyBird; 
  drawBirdFlapyBird(); 
}


int generateSewerFlappyBird(int rd, int status) {
  heightArrayFlappyBird[30][0] = rd;
  heightArrayFlappyBird[30][1] = status;

  for (int i = 0; i < 5; ++i) {
    if (!digitalRead(pau)) return 0;
    birdFlyFlappyBird();
    if (checkGameOverFlappyBird()) return 1;
    delay(50);
  }

  birdFallFlappyBird();
  if (checkGameOverFlappyBird()) return 1;
  drawRunSewerFlappyBird();

  // If bird fly over sewer
  if (heightArrayFlappyBird[3][0] && !heightArrayFlappyBird[4][0]) {
    tone(buzzer, 349, 120);
    increaseScore(); 
  } 

  return 2;
}

int generateBlackFlappyBird() {
  heightArrayFlappyBird[30][0] = 0; 

  for (int i = 0; i < 5; ++i) {
    if (!digitalRead(pau)) return 0;
    birdFlyFlappyBird();
    if (checkGameOverFlappyBird()) return 1;
    delay(50);
  }

  birdFallFlappyBird();
  if (checkGameOverFlappyBird()) return 1;
  drawRunSewerFlappyBird();

  if (heightArrayFlappyBird[3][0] && !heightArrayFlappyBird[4][0]) {
    tone(buzzer, 349, 120);
    increaseScore(); 
  } 

  return 2;
}

int newGameFlappyBird() {
  drawSubScreen(bestFlappyBird, 0);

  memset(heightArrayFlappyBird, 0, sizeof(heightArrayFlappyBird)); 

  // Distance of two adjacent sewer is 3 
  for (int i = 12; i < 30; i += 6) { 
    int randomTmp = random(7, 15);
    heightArrayFlappyBird[i][0] = heightArrayFlappyBird[i + 1][0] = heightArrayFlappyBird[i + 2][0] = randomTmp;
    heightArrayFlappyBird[i][1] = 0;
    heightArrayFlappyBird[i + 1][1] = 1;
    heightArrayFlappyBird[i + 2][1] = 2;
    drawSewerFlappyBird(i, randomTmp);
  }

  yFlappyBird = 15;
  drawBirdFlapyBird();

  // Flappy bird actives
  while (1) {
    int randomTmp = random(7, 15);

    int resultTmp = generateSewerFlappyBird(randomTmp, 0);
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateSewerFlappyBird(randomTmp, 1);
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateSewerFlappyBird(randomTmp, 2);
    if (resultTmp != 2) return resultTmp;
    
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
  }
}

int continueFlappyBird() {
  drawSubScreen(bestFlappyBird, commonScore);

  // Continue statement
  for (int i = 0; i < 30; ++i) {
    if (heightArrayFlappyBird[i][0]) {
      switch (heightArrayFlappyBird[i][1]) {
        case 0:
          drawLeftSewerFlappyBird(i, heightArrayFlappyBird[i][0]);
          break;
        case 1:
          drawMidSewerFlappyBird(i, heightArrayFlappyBird[i][0]);
          break;
        default:
          drawRightSewerFlappyBird(i, heightArrayFlappyBird[i][0]);
      }
    }
  }

  drawBirdFlapyBird();

  int resultTmp;

  // Give flappy bird back to active
  if (heightArrayFlappyBird[29][0]) {
    switch (heightArrayFlappyBird[29][1]) {
      case 0:
        resultTmp = generateSewerFlappyBird(heightArrayFlappyBird[29][0], 1);
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateSewerFlappyBird(heightArrayFlappyBird[29][0], 2);
        if (resultTmp != 2) return resultTmp;
        
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        break;
      case 1:
        resultTmp = generateSewerFlappyBird(heightArrayFlappyBird[29][0], 2);
        if (resultTmp != 2) return resultTmp;
        
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        break;
      default:
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
        resultTmp = generateBlackFlappyBird();
        if (resultTmp != 2) return resultTmp;
    }
  } else {
    if (heightArrayFlappyBird[28][0]) {
      resultTmp = generateBlackFlappyBird();
      if (resultTmp != 2) return resultTmp;
      resultTmp = generateBlackFlappyBird();
      if (resultTmp != 2) return resultTmp;
    } else if (heightArrayFlappyBird[27][0]) {
      resultTmp = generateBlackFlappyBird();
      if (resultTmp != 2) return resultTmp;
    }
  }

  while (1) {
    int randomTmp = random(7, 15);

    resultTmp = generateSewerFlappyBird(randomTmp, 0);
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateSewerFlappyBird(randomTmp, 1);
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateSewerFlappyBird(randomTmp, 2);
    if (resultTmp != 2) return resultTmp;
    
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
    resultTmp = generateBlackFlappyBird();
    if (resultTmp != 2) return resultTmp;
  }
}