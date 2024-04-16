int bestTetris = 4;

int newGameTetris() {
  drawSubScreen(bestTetris, 0);

  for (int i = 0; i < 240; i += 8) {
    for (int j = 0; j < 160; j += 8) {
      int rd = random(2);
      if (rd) {
        tft.fillRect(i, j, 8, 8, red);
      }
    }
  }

  return 1;
}

int continueTetris() {
  drawSubScreen(bestTetris, 0);
  
  return 1;
}