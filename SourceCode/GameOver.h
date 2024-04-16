int gameOver(int score) {
  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  tft.setCursor(144, 32);
  tft.println(score);

  bool newGame = true;

  posNewGame();
  negOtherGame();

  while (1) {
    if (newGame) {
      if (!digitalRead(enterPause)) return 1;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negNewGame();
        posOtherGame();
        newGame = false;
      } 
    } else {
      if (!digitalRead(enterPause)) return 2;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negOtherGame();
        posNewGame();
        newGame = true;
      } 
    }
  }
}