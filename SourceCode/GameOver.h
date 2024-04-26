int gameOver(int score) {
  tft.fillScreen(black); // clear màn hình
  tft.setTextSize(3);
  tft.setTextColor(white);

  if (commonScore < 10) tft.setCursor(152, 32);
  else if (commonScore < 100) tft.setCursor(136, 32);
  else tft.setCursor(128, 32);
  tft.println(score); // in điểm ra màn hình

  bool newGame = true;

  // lựa chọn newgame và othergame
  posNewGame();
  negOtherGame();

  while (1) {
    if (newGame) {
      if (!digitalRead(enterPause)) return 1; // chơi lại
      if (!digitalRead(top) || !digitalRead(bottom)) { 
        negNewGame();
        posOtherGame(); // chuyển sang othergame
        newGame = false;
      } 
    } else {
      if (!digitalRead(enterPause)) return 2; // chọn game khác
      if (!digitalRead(top) || !digitalRead(bottom)) { 
        negOtherGame();
        posNewGame(); // chuyển sang newgame
        newGame = true;
      } 
    }
  }
}