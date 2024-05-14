bool leftTriangle;

void iconFlappyBird() {
  tft.fillRect(96, 56, 144, 104, black);
  tft.fillRoundRect(144, 96, 48, 48, 11, yellow);
  tft.fillRoundRect(128, 108, 32, 32, 11, white);
  tft.fillRoundRect(168, 96, 24, 24, 11, white);
  tft.fillRoundRect(180, 104, 8, 8, 3, black);
  tft.fillRoundRect(176, 132, 28, 6, 3, red);
}

void iconMaze() {
  tft.fillRect(96, 56, 144, 104, black);
  tft.fillRect(112, 56, 96, 8, red);
  tft.fillRect(136, 80, 72, 8, red);
  tft.fillRect(112, 104, 24, 8, red);
  tft.fillRect(160, 104, 24, 8, red);
  tft.fillRect(136, 128, 24, 8, red);
  tft.fillRect(112, 152, 96, 8, red);
  tft.fillRect(112, 56, 8, 48, red);
  tft.fillRect(112, 128, 8, 24, red);
  tft.fillRect(160, 128, 8, 24, red);
  tft.fillRect(184, 80, 8, 48, red);
  tft.fillRect(208, 56, 8, 32, red);
  tft.fillRect(208, 104, 8, 56, red);
  tft.fillRoundRect(120, 112, 16, 16, 5, green);
}

void iconPonk() {
  tft.fillRect(96, 56, 144, 104, black);
  tft.fillRoundRect(156, 136, 8, 8, 5, yellow);
  tft.fillRoundRect(140, 144, 40, 8, 3, green);
  for (int i = 0; i < 15; ++i) {
    for (int j = 0; j < 5; ++j) {
      int rd = random(2);
      if (rd) tft.fillRect(96 + i * 8, 72 + j * 8, 8, 8, red);
    }
  }
}

void iconSnakeWind() {
  tft.fillRect(96, 56, 144, 104, black);
  tft.fillRoundRect(96, 136, 16, 16, 3, green);
  tft.fillRoundRect(112, 136, 16, 16, 3, green);
  tft.fillRoundRect(128, 136, 16, 16, 3, green);
  tft.fillRoundRect(128, 120, 16, 16, 3, green);
  tft.fillRoundRect(128, 104, 16, 16, 3, green);
  tft.fillRoundRect(144, 104, 16, 16, 3, green);
  tft.fillRoundRect(160, 104, 16, 16, 3, green);
  tft.fillRoundRect(176, 104, 16, 16, 5, yellow);
  tft.fillRoundRect(184, 108, 4, 4, 3, black);
  tft.fillRoundRect(224, 104, 16, 16, 7, white);
}

void iconTankWar() {
  tft.fillRect(96, 56, 144, 104, black);
  tft.fillRoundRect(112, 120, 96, 24, 11, green);
  tft.fillRoundRect(136, 96, 48, 24, 7, yellow);
  tft.fillRoundRect(113, 121, 22, 22, 11, red);
  tft.fillRoundRect(137, 121, 22, 22, 11, red);
  tft.fillRoundRect(161, 121, 22, 22, 11, red);
  tft.fillRoundRect(185, 121, 22, 22, 11, red);
  tft.fillRoundRect(168, 104, 32, 6, 5, red);
  tft.fillRoundRect(116, 124, 16, 16, 11, green);
  tft.fillRoundRect(140, 124, 16, 16, 11, green);
  tft.fillRoundRect(164, 124, 16, 16, 11, green);
  tft.fillRoundRect(188, 124, 16, 16, 11, green);
}

void drawGameName(String s) {
  tft.fillRect(104, 176, 136, 32, black);
  tft.setCursor(104, 176);
  tft.setTextColor(white);
  tft.println(s);
}

void subSelectGame() {
  switch (currentGame) {
    case 0:
      iconFlappyBird();
      drawGameName("FLAPPY BIRD");
      break;
    case 1:
      iconMaze();
      drawGameName("CRAZY MAZE");
      break;
    case 2:
      iconPonk();
      drawGameName("PONK PONK");
      break;
    case 3:
      iconSnakeWind();
      drawGameName("SNAKE WIND");
      break;
    default:
      iconTankWar();
      drawGameName("TANK WAR I");
  }
}

void forwardGame() {
  if (!digitalRead(left)) {
    if (!leftTriangle) {
      tft.fillTriangle(8, 120, 24, 104, 24, 136, red);
      tft.fillTriangle(312, 120, 296, 104, 296, 136, indigo);
      leftTriangle = true;
    }

    if (!currentGame) currentGame = 4;
    else --currentGame; 
    subSelectGame(); 
  } else if (!digitalRead(right)) {
    if (leftTriangle) {
      tft.fillTriangle(8, 120, 24, 104, 24, 136, indigo);
      tft.fillTriangle(312, 120, 296, 104, 296, 136, red);
      leftTriangle = false;
    } 

    if (currentGame == 4) currentGame = 0;
    else ++currentGame;
    subSelectGame();
  }
}

void selectGame() {
  tft.fillScreen(black);
  tft.setTextSize(2);

  leftTriangle = true;
  tft.fillTriangle(8, 120, 24, 104, 24, 136, red);
  tft.fillTriangle(312, 120, 296, 104, 296, 136, indigo);

  subSelectGame();

  while (1) {
    if (!digitalRead(enter)) return;
    forwardGame();
    delay(100);
  }
}

int switchNewGame() {
  music();
  switch (currentGame) {
    case 0:
      return newGameFlappyBird();
    case 1:
      return newGameMaze();
    case 2:
      return newGamePonk();
    case 3:
      return newGameSnakeWind();
    default:
      return newGameTankWar();
  }
}

int switchContinue() {
  switch (currentGame) {
    case 0:
      return continueFlappyBird();
    case 1:
      return continueMaze();
    case 2:
      return continuePonk();
    case 3:
      return continueSnakeWind();
    default:
      return continueTankWar();
  }
}