// All attributes of ponk
int barierPonk, stateBallPonk, countBrickPonk, xBallPonk, yBallPonk
              , sizeBrickPonk, quantityBrickEdgePonk, borBallPonk, widthBarierPonk, heightBarierPonk, borBarierPonk, borBrickPonk;

bool brickPonk[30][30];

// stateBallPonk corresponds to bounce%Ponk
// bounce%Ponk functions process special case first (corner, barier, corner-barier, corner-brick)

// Bounce south
bool bounce0Ponk() {
  if (yBallPonk == quantityBrickEdgePonk - 2) {
    if (xBallPonk == barierPonk) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 1;
    } else if (xBallPonk == barierPonk + 1) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 5;
    } else if (xBallPonk == barierPonk + 2) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 2;
    } else return true;
  } else if (brickPonk[yBallPonk + 1][xBallPonk]) {
    brickPonk[yBallPonk + 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
    stateBallPonk = 5;
    --countBrickPonk;
    tone(buzzer, 349, 120);
    increaseScore();
  } else {
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  }
  return false;
}

// Bounce west north
bool bounce1Ponk() {
  if (!xBallPonk && !yBallPonk) {
    tft.fillRect(xBallPonk * sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(++xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
    stateBallPonk = 4;
  } else if (!xBallPonk) {
    if (brickPonk[yBallPonk - 1][0]) {
      brickPonk[yBallPonk - 1][0] = false;
      tft.fillRect(0, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(0, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 4;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 2;
  } else if (!yBallPonk) {
    if (brickPonk[0][xBallPonk - 1]) {
      brickPonk[0][xBallPonk - 1] = false;
      tft.fillRect((xBallPonk - 1) * sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(xBallPonk * sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 4;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 3;
  } else if (brickPonk[yBallPonk][xBallPonk - 1]) {
    brickPonk[yBallPonk][xBallPonk - 1] = false;
    tft.fillRect((xBallPonk - 1) * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 2;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else if (brickPonk[yBallPonk - 1][xBallPonk]) {
    brickPonk[yBallPonk - 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 3;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else {
    if (brickPonk[yBallPonk - 1][xBallPonk - 1]) {
      brickPonk[yBallPonk - 1][xBallPonk - 1] = false;
      tft.fillRect((xBallPonk - 1) * sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } 
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  }
  return false;
}


// Bounce east north
bool bounce2Ponk() {
  if (xBallPonk == quantityBrickEdgePonk - 1 && !yBallPonk) {
    tft.fillRect(240 - sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(--xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
    stateBallPonk = 3;
  } else if (xBallPonk == quantityBrickEdgePonk - 1) {
    if (brickPonk[yBallPonk - 1][quantityBrickEdgePonk - 1]) {
      brickPonk[yBallPonk - 1][quantityBrickEdgePonk - 1] = false;
      tft.fillRect(240 - sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(240 - sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 3;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 1;
  } else if (!yBallPonk) {
    if (brickPonk[0][xBallPonk + 1]) {
      brickPonk[0][xBallPonk + 1] = false;
      tft.fillRect((xBallPonk + 1) * sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(xBallPonk * sizeBrickPonk, 0, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 3;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 4;
  } else if (brickPonk[yBallPonk][xBallPonk + 1]) {
    brickPonk[yBallPonk][xBallPonk + 1] = false;
    tft.fillRect((xBallPonk + 1) * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 1;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else if (brickPonk[yBallPonk - 1][xBallPonk]) {
    brickPonk[yBallPonk - 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 4;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else {
    if (brickPonk[yBallPonk - 1][xBallPonk + 1]) {
      brickPonk[yBallPonk - 1][xBallPonk + 1] = false;
      tft.fillRect((xBallPonk + 1) * sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } 
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  }
  return false;
}

// Bounce west south
bool bounce3Ponk() {
  if (yBallPonk == quantityBrickEdgePonk - 2) {
    if (!xBallPonk) {
      if (!barierPonk || barierPonk == 1) {
        tft.fillRect(0, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
        tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
        stateBallPonk = 2;
      } else return true;
    } else if (xBallPonk == barierPonk || xBallPonk == barierPonk + 1) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 1;
    } else if (xBallPonk == barierPonk + 2 || xBallPonk == barierPonk + 3) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 2;
    } else return true;
    return false;
  } else if (!xBallPonk) {
    if (brickPonk[yBallPonk + 1][0]) {
      brickPonk[yBallPonk + 1][0] = false;
      tft.fillRect(0, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(0, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 2;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 4;
  } else if (brickPonk[yBallPonk + 1][xBallPonk]) {
    brickPonk[yBallPonk + 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 1;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else if (brickPonk[yBallPonk][xBallPonk - 1]) {
    brickPonk[yBallPonk][xBallPonk - 1] = false;
    tft.fillRect((xBallPonk - 1) * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 4;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else {
    if (brickPonk[yBallPonk + 1][xBallPonk - 1]) {
      brickPonk[yBallPonk + 1][xBallPonk - 1] = false;
      tft.fillRect((xBallPonk - 1) * sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } 
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(--xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  }
  return false;
}

// Bounce east south
bool bounce4Ponk() {
  if (yBallPonk == quantityBrickEdgePonk - 2) {
    if (xBallPonk == quantityBrickEdgePonk - 1) {
      if (barierPonk == 11 || barierPonk == 12) {
        tft.fillRect(240 - sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
        tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
        stateBallPonk = 1;
      } else return true;
    } else if (xBallPonk == barierPonk - 1 || xBallPonk == barierPonk) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 1;
    } else if (xBallPonk == barierPonk + 1 || xBallPonk == barierPonk + 2) {
      tft.fillRect(xBallPonk * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(++xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 2;
    } else return true;
    return false;
  } else if (xBallPonk == quantityBrickEdgePonk - 1) {
    if (brickPonk[yBallPonk + 1][quantityBrickEdgePonk - 1]) {
      brickPonk[yBallPonk + 1][quantityBrickEdgePonk - 1] = false;
      tft.fillRect(240 - sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRect(240 - sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      tft.fillRoundRect(--xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
      stateBallPonk = 1;
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } else stateBallPonk = 3;
  } else if (brickPonk[yBallPonk + 1][xBallPonk]) {
    brickPonk[yBallPonk + 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 2;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else if (brickPonk[yBallPonk][xBallPonk + 1]) {
    brickPonk[yBallPonk][xBallPonk + 1] = false;
    tft.fillRect((xBallPonk + 1) * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    stateBallPonk = 3;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else {
    if (brickPonk[yBallPonk + 1][xBallPonk + 1]) {
      brickPonk[yBallPonk + 1][xBallPonk + 1] = false;
      tft.fillRect((xBallPonk + 1) * sizeBrickPonk, (yBallPonk + 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
      --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
    } 
    tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(++xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  }
  return false;
}

// Bounce north
bool bounce5Ponk() {
  tft.fillRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
  if (!yBallPonk) {
    tft.fillRoundRect(xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
    stateBallPonk = 0;
  } else if (brickPonk[yBallPonk - 1][xBallPonk]) {
    brickPonk[yBallPonk - 1][xBallPonk] = false;
    tft.fillRect(xBallPonk * sizeBrickPonk, (yBallPonk - 1) * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, black);
    tft.fillRoundRect(xBallPonk * sizeBrickPonk, ++yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
    stateBallPonk = 0;
    --countBrickPonk;
      tone(buzzer, 349, 120);
      increaseScore();
  } else tft.fillRoundRect(xBallPonk * sizeBrickPonk, --yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);
  return false;
}

bool moveBall() {
  switch (stateBallPonk) {
    case 0: return bounce0Ponk();
    case 1: return bounce1Ponk();
    case 2: return bounce2Ponk();
    case 3: return bounce3Ponk();
    case 4: return bounce4Ponk();
    default: return bounce5Ponk();
  }
}

void moveBarierPonk() {
  if (!digitalRead(left) && barierPonk) {
    tft.fillRect(barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, sizeBrickPonk, black);
    tft.fillRoundRect(--barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, heightBarierPonk, borBarierPonk, green);
  } else if (!digitalRead(right) && barierPonk != quantityBrickEdgePonk - 3) {
    tft.fillRect(barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, sizeBrickPonk, black);
    tft.fillRoundRect(++barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, heightBarierPonk, borBarierPonk, green);
  }
}

void drawSubScreenPonk(int score) {
  switch (sizeBrickPonk) {
    case 16:
      drawSubScreen(bestPonkEasy, score);
      break;
    case 12:
      drawSubScreen(bestPonkMedium, score);
      break;
    default:
      drawSubScreen(bestPonkHard, score);
  }
}

void gameOverPonk() {
  switch (sizeBrickPonk) {
    case 16:
      if (commonScore > bestPonkEasy) {
        bestPonkEasy = commonScore;  
        EEPROM.write(currentPlayer + addressBestPonkEasy, commonScore);
        EEPROM.commit();
      }
      break;
    case 12:
      if (commonScore > bestPonkMedium) {
        bestPonkMedium = commonScore;  
        EEPROM.write(currentPlayer + addressBestPonkMedium, commonScore);
        EEPROM.commit();
      }
      break;
    default:
      if (commonScore > bestPonkHard) {
        bestPonkHard = commonScore;  
        EEPROM.write(currentPlayer + addressBestPonkHard, commonScore);
        EEPROM.commit();
      }
  }
}

int newGamePonk() {
  // Select all atributes of ponk
  switch (selectThree(false, "--EASY--", "-MEDIUM-", "---HARD---")) {
    case 0:
      sizeBrickPonk = 16;
      quantityBrickEdgePonk = 15;
      borBallPonk = 7;
      widthBarierPonk = 48;
      heightBarierPonk = 8;
      borBarierPonk = 5;
      borBrickPonk = 3;
      break;
    case 1:
      sizeBrickPonk = 12;
      quantityBrickEdgePonk = 20;
      borBallPonk = 5;
      widthBarierPonk = 36;
      heightBarierPonk = 6;
      borBarierPonk = 3;
      borBrickPonk = 2;
      break;
    default:
      sizeBrickPonk = 8;
      quantityBrickEdgePonk = 30;
      borBallPonk = 3;
      widthBarierPonk = 24;
      heightBarierPonk = 4;
      borBarierPonk = 3;
      borBrickPonk = 1;
  }

  drawSubScreenPonk(0);

  countBrickPonk = 0;
  int heightBirckTmp = quantityBrickEdgePonk / 2 + 1;

  // Create random bricks
  for (int i = 0; i < heightBirckTmp; ++i) {
    for (int j = 0; j < quantityBrickEdgePonk; ++j) {
      int randomTmp = random(2);
      if (randomTmp) {
        ++countBrickPonk;
        brickPonk[i][j] = true;
        tft.fillRoundRect(j * sizeBrickPonk, i * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBrickPonk, red);
      } else brickPonk[i][j] = false;
    }
  }

  for (int i = heightBirckTmp; i < quantityBrickEdgePonk; ++i) {
    for (int j = 0; j < quantityBrickEdgePonk; ++j) brickPonk[i][j] = false;
  }

  barierPonk = quantityBrickEdgePonk / 2 - 1;
  tft.fillRoundRect(barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, heightBarierPonk, borBarierPonk, green);

  xBallPonk = quantityBrickEdgePonk / 2;
  yBallPonk = quantityBrickEdgePonk - 2;
  stateBallPonk = 5;
  tft.fillRoundRect(quantityBrickEdgePonk / 2 * sizeBrickPonk, 240 - 2 * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);

  delay(1000);

  // Ponk actives
  while (1) {
    if (!digitalRead(pau)) return 0;
    if (moveBall() || !countBrickPonk) {
      gameOverPonk();
      return 1;
    }
    moveBarierPonk();
    delay(100);
  }
}

int continuePonk() {
  drawSubScreenPonk(commonScore);
  
  int heightBirckTmp = quantityBrickEdgePonk / 2 + 1;

  // Continue statement
  for (int i = 0; i < heightBirckTmp; ++i) {
    for (int j = 0; j < quantityBrickEdgePonk; ++j) {
      if (brickPonk[i][j]) tft.fillRoundRect(j * sizeBrickPonk, i * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBrickPonk, red);
    }
  }

  tft.fillRoundRect(barierPonk * sizeBrickPonk, 240 - sizeBrickPonk, widthBarierPonk, heightBarierPonk, borBarierPonk, green);
  tft.fillRoundRect(xBallPonk * sizeBrickPonk, yBallPonk * sizeBrickPonk, sizeBrickPonk, sizeBrickPonk, borBallPonk, yellow);

  delay(1000);

  while (1) {
    if (!digitalRead(pau)) return 0;
    if (moveBall() || !countBrickPonk) {
      gameOverPonk();
      return 1;
    }
    moveBarierPonk();
    delay(100);
  }
}