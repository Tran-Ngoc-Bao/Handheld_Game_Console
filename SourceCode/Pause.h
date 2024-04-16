int pause() {
  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  bool ctn = true;
  bool newGame = false;

  posContinue();
  negNewGame();
  negOtherGame();

  while (1) {
    if (ctn) {
      if (!digitalRead(enterPause)) return 0;
      if (!digitalRead(top)) {
        negContinue();
        posOtherGame();
        ctn = false;
      } else if (!digitalRead(bottom)) {
        negContinue();
        posNewGame();
        ctn = false;
        newGame = true;
      } 
    } else if (newGame) {
      if (!digitalRead(enterPause)) return 1;
      if (!digitalRead(top)) {
        negNewGame();
        posContinue();
        newGame = false;
        ctn = true;
      } else if (!digitalRead(bottom)) {
        negNewGame();
        posOtherGame();
        newGame = false;
      } 
    } else {
      if (!digitalRead(enterPause)) return 2;
      if (!digitalRead(top)) {
        negOtherGame();
        posNewGame();
        newGame = true;
      } else if (!digitalRead(bottom)) {
        negOtherGame();
        posContinue();
        ctn = true;
      } 
    }
  }
}