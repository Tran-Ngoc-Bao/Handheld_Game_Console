int barier, stateBall, countBrick, xBall, yBall;

bool brick[15][15];

bool bounce0() {
  if (yBall == 13) {
    if (xBall == barier) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 1;
    } else if (xBall == barier + 1) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 5;
    } else if (xBall == barier + 2) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 2;
    } else return true;
  } else if (brick[yBall + 1][xBall]) {
    brick[yBall + 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall + 1) * 16, 16, 16, black);
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(xBall * 16, --yBall * 16, 16, 16, 7, yellow);
    stateBall = 5;
    --countBrick;
    increaseScore();
  } else {
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
  }
  return false;
}

bool bounce1() {
  if (!xBall && !yBall) {
    tft.fillRect(xBall * 16, 0, 16, 16, black);
    tft.fillRoundRect(++xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
    stateBall = 4;
  } else if (!xBall) {
    if (brick[yBall - 1][0]) {
      brick[yBall - 1][0] = false;
      tft.fillRect(0, (yBall - 1) * 16, 16, 16, black);
      tft.fillRect(0, yBall * 16, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
      stateBall = 4;
      --countBrick;
      increaseScore();
    } else stateBall = 2;
  } else if (!yBall) {
    if (brick[0][xBall - 1]) {
      brick[0][xBall - 1] = false;
      tft.fillRect((xBall - 1) * 16, 0, 16, 16, black);
      tft.fillRect(xBall * 16, 0, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
      stateBall = 4;
      --countBrick;
      increaseScore();
    } else stateBall = 3;
  } else if (brick[yBall][xBall - 1]) {
    brick[yBall][xBall - 1] = false;
    tft.fillRect((xBall - 1) * 16, yBall * 16, 16, 16, black);
    stateBall = 2;
    --countBrick;
      increaseScore();
  } else if (brick[yBall - 1][xBall]) {
    brick[yBall - 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall - 1) * 16, 16, 16, black);
    stateBall = 3;
    --countBrick;
      increaseScore();
  } else {
    if (brick[yBall - 1][xBall - 1]) {
      brick[yBall - 1][xBall - 1] = false;
      tft.fillRect((xBall - 1) * 16, (yBall - 1) * 16, 16, 16, black);
      --countBrick;
      increaseScore();
    } 
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
  }
  return false;
}

bool bounce2() {
  if (xBall == 14 && !yBall) {
    tft.fillRect(224, 0, 16, 16, black);
    tft.fillRoundRect(--xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
    stateBall = 3;
  } else if (xBall == 14) {
    if (brick[yBall - 1][14]) {
      brick[yBall - 1][14] = false;
      tft.fillRect(224, (yBall - 1) * 16, 16, 16, black);
      tft.fillRect(224, yBall * 16, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
      stateBall = 3;
      --countBrick;
      increaseScore();
    } else stateBall = 1;
  } else if (!yBall) {
    if (brick[0][xBall + 1]) {
      brick[0][xBall + 1] = false;
      tft.fillRect((xBall + 1) * 16, 0, 16, 16, black);
      tft.fillRect(xBall * 16, 0, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
      stateBall = 3;
      --countBrick;
      increaseScore();
    } else stateBall = 4;
  } else if (brick[yBall][xBall + 1]) {
    brick[yBall][xBall + 1] = false;
    tft.fillRect((xBall + 1) * 16, yBall * 16, 16, 16, black);
    stateBall = 1;
    --countBrick;
      increaseScore();
  } else if (brick[yBall - 1][xBall]) {
    brick[yBall - 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall - 1) * 16, 16, 16, black);
    stateBall = 4;
    --countBrick;
      increaseScore();
  } else {
    if (brick[yBall - 1][xBall + 1]) {
      brick[yBall - 1][xBall + 1] = false;
      tft.fillRect((xBall + 1) * 16, (yBall - 1) * 16, 16, 16, black);
      --countBrick;
      increaseScore();
    } 
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
  }
  return false;
}

bool bounce3() {
  if (yBall == 13) {
    if (!xBall) {
      if (!barier || barier == 1) {
        tft.fillRect(0, 208, 16, 16, black);
        tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
        stateBall = 2;
      } else return true;
    } else if (xBall == barier || xBall == barier + 1) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 1;
    } else if (xBall == barier + 2 || xBall == barier + 3) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 2;
    } else return true;
    return false;
  } else if (!xBall) {
    if (brick[yBall + 1][0]) {
      brick[yBall + 1][0] = false;
      tft.fillRect(0, (yBall + 1) * 16, 16, 16, black);
      tft.fillRect(0, yBall * 16, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 2;
      --countBrick;
      increaseScore();
    } else stateBall = 4;
  } else if (brick[yBall + 1][xBall]) {
    brick[yBall + 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall + 1) * 16, 16, 16, black);
    stateBall = 1;
    --countBrick;
      increaseScore();
  } else if (brick[yBall][xBall - 1]) {
    brick[yBall][xBall - 1] = false;
    tft.fillRect((xBall - 1) * 16, yBall * 16, 16, 16, black);
    stateBall = 4;
    --countBrick;
      increaseScore();
  } else {
    if (brick[yBall + 1][xBall - 1]) {
      brick[yBall + 1][xBall - 1] = false;
      tft.fillRect((xBall - 1) * 16, (yBall + 1) * 16, 16, 16, black);
      --countBrick;
      increaseScore();
    } 
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(--xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
  }
  return false;
}

bool bounce4() {
  if (yBall == 13) {
    if (xBall == 14) {
      if (barier == 11 || barier == 12) {
        tft.fillRect(224, 208, 16, 16, black);
        tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
        stateBall = 1;
      } else return true;
    } else if (xBall == barier - 1 || xBall == barier) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 1;
    } else if (xBall == barier + 1 || xBall == barier + 2) {
      tft.fillRect(xBall * 16, 208, 16, 16, black);
      tft.fillRoundRect(++xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 2;
    } else return true;
    return false;
  } else if (xBall == 14) {
    if (brick[yBall + 1][14]) {
      brick[yBall + 1][14] = false;
      tft.fillRect(224, (yBall + 1) * 16, 16, 16, black);
      tft.fillRect(224, yBall * 16, 16, 16, black);
      tft.fillRoundRect(--xBall * 16, --yBall * 16, 16, 16, 7, yellow);
      stateBall = 1;
      --countBrick;
      increaseScore();
    } else stateBall = 3;
  } else if (brick[yBall + 1][xBall]) {
    brick[yBall + 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall + 1) * 16, 16, 16, black);
    stateBall = 2;
    --countBrick;
      increaseScore();
  } else if (brick[yBall][xBall + 1]) {
    brick[yBall][xBall + 1] = false;
    tft.fillRect((xBall + 1) * 16, yBall * 16, 16, 16, black);
    stateBall = 3;
    --countBrick;
      increaseScore();
  } else {
    if (brick[yBall + 1][xBall + 1]) {
      brick[yBall + 1][xBall + 1] = false;
      tft.fillRect((xBall + 1) * 16, (yBall + 1) * 16, 16, 16, black);
      --countBrick;
      increaseScore();
    } 
    tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
    tft.fillRoundRect(++xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
  }
  return false;
}

bool bounce5() {
  tft.fillRect(xBall * 16, yBall * 16, 16, 16, black);
  if (!yBall) {
    tft.fillRoundRect(xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
    stateBall = 0;
  } else if (brick[yBall - 1][xBall]) {
    brick[yBall - 1][xBall] = false;
    tft.fillRect(xBall * 16, (yBall - 1) * 16, 16, 16, black);
    tft.fillRoundRect(xBall * 16, ++yBall * 16, 16, 16, 7, yellow);
    stateBall = 0;
    --countBrick;
      increaseScore();
  } else tft.fillRoundRect(xBall * 16, --yBall * 16, 16, 16, 7, yellow);
  return false;
}

bool moveBall() {
  switch (stateBall) {
    case 0: return bounce0();
    case 1: return bounce1();
    case 2: return bounce2();
    case 3: return bounce3();
    case 4: return bounce4();
    default: return bounce5();
  }
}

void moveBarier() {
  if (!digitalRead(left) && barier) {
    tft.fillRect(barier * 16, 224, 48, 16, black);
    tft.fillRoundRect(--barier * 16, 224, 48, 8, 5, green);
  } else if (!digitalRead(right) && barier != 12) {
    tft.fillRect(barier * 16, 224, 48, 16, black);
    tft.fillRoundRect(++barier * 16, 224, 48, 8, 5, green);
  }
}

int newGamePonk() {
  drawSubScreen(bestPonk, 0);

  countBrick = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 15; ++j) {
      int rd = random(2);
      if (rd) {
        ++countBrick;
        brick[i][j] = true;
        tft.fillRoundRect(j * 16, i * 16, 16, 16, 3, red);
      } else brick[i][j] = false;
    }
  }
  for (int i = 8; i < 15; ++i) {
    for (int j = 0; j < 15; ++j) brick[i][j] = false;
  }

  barier = 6;
  tft.fillRoundRect(96, 224, 48, 8, 5, green);

  xBall = 7;
  yBall = 13;
  stateBall = 5;
  tft.fillRoundRect(112, 208, 16, 16, 7, yellow);

  delay(1000);

  while (1) {
    if (!digitalRead(pau)) return 0;
    if (moveBall() || !countBrick) {
      if (commonScore > bestPonk) {
        bestPonk = commonScore;  
        EEPROM.write(2, commonScore);
        EEPROM.commit();
      }
      return 1;
    }
    moveBarier();
    delay(150);
  }
}

int continuePonk() {
  drawSubScreen(bestPonk, commonScore);
  
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 15; ++j) {
      if (brick[i][j]) tft.fillRoundRect(j * 16, i * 16, 16, 16, 3, red);
    }
  }

  tft.fillRoundRect(barier * 16, 224, 48, 8, 5, green);
  tft.fillRoundRect(xBall * 16, yBall * 16, 16, 16, 7, yellow);

  delay(1000);

  while (1) {
    if (!digitalRead(pau)) return 0;
    if (moveBall() || !countBrick) {
      if (commonScore > bestPonk) {
        bestPonk = commonScore;
        EEPROM.write(2, commonScore);
        EEPROM.commit();
      }
      return 1;
    }
    moveBarier();
    delay(150);
  }
}