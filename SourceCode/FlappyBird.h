int bestFlappyBird = 0, yBird;

int heightArray[31][2];

void drawLeftSewer(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawMidSewer(int x, int h) {
  tft.fillRect(x * 8, 0, 8, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 8, (19 - h) * 8, green);
}

void drawRightSewer(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 4, (h - 2) * 8, black);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 4, (19 - h) * 8, black);
  tft.fillRect(x * 8, 0, 4, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 8, 16, green);
  tft.fillRect(x * 8, (h + 11) * 8, 4, (19 - h) * 8, green);
}

void drawSewer(int x, int h) {
  tft.fillRect(x * 8 + 4, 0, 16, (h - 2) * 8, green);
  tft.fillRect(x * 8, (h - 2) * 8, 24, 16, green);
  tft.fillRect(x * 8, (h + 9) * 8, 24, 16, green);
  tft.fillRect(x * 8 + 4, (h + 11) * 8, 16, (19 - h) * 8, green);
}

void drawRunSewer() {
  for (int i = 0; i < 30; ++i) {
    if (heightArray[i][0]) {
      switch (heightArray[i][1]) {
        case 0:
          heightArray[i][1] = 1;
          drawMidSewer(i, heightArray[i][0]);
          break;
        case 1:
          heightArray[i][1] = 2;
          drawRightSewer(i, heightArray[i][0]);
          break;
        default:
          tft.fillRect(i * 8, 0, 8, heightArray[i][0] * 8, black);
          tft.fillRect(i * 8, (heightArray[i][0] + 9) * 8, 8, (21 - heightArray[i][0]) * 8, black);
          heightArray[i][0] = 0;
      }
    } else if (heightArray[i + 1][0]) {
      heightArray[i][0] = heightArray[i + 1][0];
      heightArray[i][1] = 0;
      drawLeftSewer(i, heightArray[i][0]);
    }
  }
}

void drawBird() {
  tft.fillRoundRect(32, yBird * 8, 24, 24, 5, yellow);
  tft.fillRoundRect(44, yBird * 8, 12, 12, 5, white);
  tft.fillRoundRect(24, yBird * 8 + 8, 16, 16, 5, white);
  tft.fillRoundRect(48, yBird * 8 + 4, 4, 4, 3, black);
  tft.fillRoundRect(48, yBird * 8 + 16, 16, 4, 3, red);
}

bool checkGameOverFB() {
  if (heightArray[4][0]) {
    if (heightArray[4][0] >= yBird || yBird >= heightArray[4][0] + 6) {
      if (commonScore > bestFlappyBird) bestFlappyBird = commonScore;
      return true;
    } 
  }
  if (heightArray[6][0]) {
    if (heightArray[6][0] >= yBird || yBird >= heightArray[6][0] + 6) {
      if (commonScore > bestFlappyBird) bestFlappyBird = commonScore;
      return true;
    }
  }
  return false;
}

void birdFly() {
  if (!digitalRead(top)) {
    tft.fillRect(32, yBird * 8, 24, 24, black);
    tft.fillRect(24, yBird * 8 + 8, 8, 16, black);
    tft.fillRect(56, yBird * 8 + 16, 8, 4, black);
    --yBird;
    drawBird();
  }
}

void animationFB() {
  drawRunSewer();
  tft.fillRect(32, yBird * 8, 24, 24, black);
  tft.fillRect(24, yBird * 8 + 8, 8, 16, black);
  tft.fillRect(56, yBird * 8 + 16, 8, 4, black);
  ++yBird;
  drawBird();
  if (heightArray[3][0] && !heightArray[4][0]) increaseScore();
}

int newGameFlappyBird() {
  drawSubScreen(bestFlappyBird, 0);

  memset(heightArray, 0, sizeof(heightArray));

  for (int i = 12; i < 30; i += 6) {
    int rd = random(7, 15);
    heightArray[i][0] = heightArray[i + 1][0] = heightArray[i + 2][0] = rd;
    heightArray[i][1] = 0;
    heightArray[i + 1][1] = 1;
    heightArray[i + 2][1] = 2;
    drawSewer(i, rd);
  }

  yBird = 15;
  drawBird();

  while (1) {
    int rd = random(7, 15);

    heightArray[30][0] = rd;
    heightArray[30][1] = 0;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = rd;
    heightArray[30][1] = 1;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = rd;
    heightArray[30][1] = 2;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = 0;
    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 5; ++i) {
        if (!digitalRead(enterPause)) return 0;
        birdFly();
        if (checkGameOverFB()) return 1;
        delay(100);
      }
      animationFB();
      if (checkGameOverFB()) return 1;
    }
  }
}

int continueFlappyBird() {
  drawSubScreen(bestFlappyBird, commonScore);

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

  while (1) {
    int rd = random(7, 15);

    heightArray[30][0] = rd;
    heightArray[30][1] = 0;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = rd;
    heightArray[30][1] = 1;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = rd;
    heightArray[30][1] = 2;
    for (int i = 0; i < 5; ++i) {
      if (!digitalRead(enterPause)) return 0;
      birdFly();
      if (checkGameOverFB()) return 1;
      delay(100);
    }
    animationFB();
    if (checkGameOverFB()) return 1;

    heightArray[30][0] = 0;
    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 5; ++i) {
        if (!digitalRead(enterPause)) return 0;
        birdFly();
        if (checkGameOverFB()) return 1;
        delay(100);
      }
      animationFB();
      if (checkGameOverFB()) return 1;
    }
  }
}