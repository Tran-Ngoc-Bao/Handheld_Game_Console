int gameOver(int score) {
  music();
  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  if (commonScore < 10) tft.setCursor(152, 32);
  else if (commonScore < 100) tft.setCursor(136, 32);
  else tft.setCursor(128, 32);
  tft.println(score);

  bool newGame = true;

  posNewGame();
  negOtherGame();

  while (1) {
    if (newGame) {
      if (!digitalRead(enter)) return 1;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negNewGame();
        posOtherGame();
        newGame = false;
      } 
    } else {
      if (!digitalRead(enter)) return 2;
      if (!digitalRead(top) || !digitalRead(bottom)) {
        negOtherGame();
        posNewGame();
        newGame = true;
      } 
    }
  }
}