int bestFlappyBird = 0, yBird;

int heightArray[31];

void drawPartSewer(int x, int h) {
  int x8 = x * 8;
  tft.fillRect(x8, 0, 8, h * 8, green);
  tft.fillRect(x8, (h - 2) * 8, 8, 16, yellow);
  tft.fillRect(x8, (h + 9) * 8, 8, 16, yellow);
  tft.fillRect(x8, (h + 11) * 8, 8, (19 - h) * 8, green);
}

void drawSewer(int x, int h) {
  int x8 = x * 8;
  tft.fillRect(x8, 0, 24, (h - 2) * 8, green);
  tft.fillRect(x8, (h - 2) * 8, 24, 16, yellow);
  tft.fillRect(x8, (h + 9) * 8, 24, 16, yellow);
  tft.fillRect(x8, (h + 11) * 8, 24, (19 - h) * 8, green);
}

void drawRunSewer() {
  for (int i = 0; i < 30; ++i) {
    if (heightArray[i] != heightArray[i + 1]) {
      if (heightArray[i]) {
        heightArray[i] = 0;
        tft.fillRect(i * 8, 0, 8, 240, black);
      } else {
        heightArray[i] = heightArray[i + 1];
        drawPartSewer(i, heightArray[i]);
      }
    }
  }
}

void drawBird() {
  int y8 = yBird * 8;
  tft.fillRoundRect(32, y8, 24, 24, 5, yellow);
  tft.fillRoundRect(44, y8, 12, 12, 5, white);
  tft.fillRoundRect(24, y8 + 8, 16, 16, 5, white);
  tft.fillRoundRect(48, y8 + 4, 4, 4, 3, black);
  tft.fillRoundRect(48, y8 + 16, 16, 4, 3, red);
}

bool checkGameOverFB() {
  if (heightArray[4]) {
    if (heightArray[4] >= yBird || yBird >= heightArray[4] + 6) {
      if (commonScore > bestFlappyBird) bestFlappyBird = commonScore;
      return true;
    } 
  }
  if (heightArray[6]) {
    if (heightArray[6] >= yBird || yBird >= heightArray[6] + 6) {
      if (commonScore > bestFlappyBird) bestFlappyBird = commonScore;
      return true;
    }
  }
  return false;
}

void birdFly() {
  if (!digitalRead(top)) {
    tft.fillRect(24, yBird * 8, 40, 24, black);
    --yBird;
    drawBird();
  }
}

void animationFB() {
  drawRunSewer();
  tft.fillRect(24, yBird * 8, 40, 24, black);
  ++yBird;
  drawBird();
  if (heightArray[3] && !heightArray[4]) increaseScore();
}

int newGameFlappyBird() {
  drawSubScreen(bestFlappyBird, 0);

  memset(heightArray, 0, sizeof(heightArray));

  for (int i = 12; i < 30; i += 6) {
    int rd = random(7, 15);
    heightArray[i] = heightArray[i + 1] = heightArray[i + 2] = rd;
    drawSewer(i, rd);
  }

  yBird = 15;
  drawBird();

  while (1) {
    int rd = random(7, 15);

    for (int j = 0; j < 3; ++j) {
      heightArray[30] = rd;
      for (int i = 0; i < 6; ++i) {
        if (!digitalRead(enterPause)) return 0;
        birdFly();
        if (checkGameOverFB()) return 1;
        delay(100);
      }
      animationFB();
      if (checkGameOverFB()) return 1;
    }

    for (int j = 0; j < 3; ++j) {
      heightArray[30] = 0;
      for (int i = 0; i < 6; ++i) {
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
    if (heightArray[i]) drawPartSewer(i, heightArray[i]);
  }

  drawBird();

  while (1) {
    int rd = random(7, 15);

    for (int j = 0; j < 3; ++j) {
      heightArray[30] = rd;
      for (int i = 0; i < 6; ++i) {
        if (!digitalRead(enterPause)) return 0;
        birdFly();
        if (checkGameOverFB()) return 1;
        delay(100);
      }
      animationFB();
      if (checkGameOverFB()) return 1;
    }

    for (int j = 0; j < 3; ++j) {
      heightArray[30] = 0;
      for (int i = 0; i < 6; ++i) {
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