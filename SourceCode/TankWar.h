int bestTankWar = 0;
int stateVietNam, stateAmerica1, stateAmerica2, stateAmerica3, stateAmerica4;

coordinates vietNam, america1, america2, america3, america4;

void drawVietNam() {
  int x8 = vietNam.x * 8, y8 = vietNam.y * 8;
  switch (stateVietNam) {
    case 1:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 6, y8 + 8, 12, 12, 3, yellow);
      tft.fillRect(x8 + 10, y8 + 2, 4, 6, indigo);
      break;
    case 2:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 4, y8 + 6, 12, 12, 3, yellow);
      tft.fillRect(x8 + 16, y8 + 10, 6, 4, indigo);
      break;
    case 3:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 6, y8 + 4, 12, 12, 3, yellow);
      tft.fillRect(x8 + 10, y8 + 16, 4, 6, indigo);
      break;
    default:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 8, y8 + 6, 12, 12, 3, yellow);
      tft.fillRect(x8 + 2, y8 + 10, 6, 4, indigo);
  }
}

void drawAmerica(int x, int y, int state) {
  int x8 = x * 8, y8 = y * 8;
  switch (state) {
    case 1:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 6, y8 + 8, 12, 12, 3, red);
      tft.fillRect(x8 + 10, y8 + 2, 4, 6, white);
      break;
    case 2:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 4, y8 + 6, 12, 12, 3, red);
      tft.fillRect(x8 + 16, y8 + 10, 6, 4, white);
      break;
    case 3:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 6, y8 + 4, 12, 12, 3, red);
      tft.fillRect(x8 + 10, y8 + 16, 4, 6, white);
      break;
    default:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 8, y8 + 6, 12, 12, 3, red);
      tft.fillRect(x8 + 2, y8 + 10, 6, 4, white);
  }
}

void eraseVietNam() {
  if (stateVietNam == 1 || stateVietNam == 3) tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 32, black);
  else tft.fillRect(vietNam.x * 8, vietNam.y * 8, 32, 24, black);
}

void eraseAmerica(int x, int y, int state) {
  if (state == 1 || state == 3) tft.fillRect(x * 8, y * 8, 24, 32, black);
  else tft.fillRect(x * 8, y * 8, 32, 24, black);
}

bool killAmerica(int x, int y) {
  if (america1.x <= x && x <= america1.x + 2 && america1.y <= y && y <= america1.y + 2) {
    eraseAmerica(america1.x, america1.y, stateAmerica1);
    increaseScore();
    america1.x = 3;
    america1.y = 3;
    drawAmerica(3, 3, 3);
    return true;
  }
  if (america2.x <= x && x <= america2.x + 2 && america2.y <= y && y <= america2.y + 2) {
    eraseAmerica(america2.x, america2.y, stateAmerica2);
    increaseScore();
    america2.x = 24;
    america2.y = 3;
    drawAmerica(24, 3, 3);
    return true;
  }
  if (america3.x <= x && x <= america3.x + 2 && america3.y <= y && y <= america3.y + 2) {
    eraseAmerica(america3.x, america3.y, stateAmerica3);
    increaseScore();
    america3.x = 24;
    america3.y = 24;
    drawAmerica(24, 24, 1);
    return true;
  }
  if (america4.x <= x && x <= america4.x + 2 && america4.y <= y && y <= america4.y + 2) {
    eraseAmerica(america4.x, america4.y, stateAmerica4);
    increaseScore();
    america4.x = 3;
    america4.y = 24;
    drawAmerica(3, 24, 1);
    return true;
  }
  return false;
}

void shootAmerica() {
  int x = vietNam.x, y = vietNam.y;
  switch (stateVietNam) {
    case 1:
      for (int i = y - 1; i >= 0; --i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(x + 1, i)) break;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    case 2:
      for (int i = x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, y + 1)) break;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      break;
    case 3:
      for (int i = y + 4; i < 30; ++i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(x + 1, i)) break;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    default:
      for (int i = x - 1; i >= 0; --i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, y + 1)) break;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
  }
}

void hitAndRunVietNam() {
  if (!digitalRead(top) && vietNam.y) {
    eraseVietNam();
    --vietNam.y;
    if (stateVietNam != 1) {
      stateVietNam = 1;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  } else if (!digitalRead(right) && vietNam.x != 27) {
    eraseVietNam();
    ++vietNam.x;
    if (stateVietNam != 2) {
      stateVietNam = 2;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  } else if (!digitalRead(bottom) && vietNam.y != 27) {
    eraseVietNam();
    ++vietNam.y;
    if (stateVietNam != 3) {
      stateVietNam = 3;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  } else if (!digitalRead(left) && vietNam.x) {
    eraseVietNam();
    --vietNam.x;
    if (stateVietNam != 4) {
      stateVietNam = 4;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  }
}

bool shootVietNam(int x, int y, int state) {
  switch (state) {
    case 1:
      for (int i = y - 1; i >= 0; --i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= x + 1 && x <= vietNam.x + 1 && vietNam.y <= i && i <= vietNam.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      return false;
    case 2:
      for (int i = x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= i && i <= vietNam.x + 2 && vietNam.y <= y + 1 && y <= vietNam.y + 1) return true;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      return false;
    case 3:
      for (int i = y + 4; i < 30; ++i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= x + 1 && x <= vietNam.x + 1 && vietNam.y <= i && i <= vietNam.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      return false;
    default:
      for (int i = x - 1; i >= 0; --i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= i && i <= vietNam.x + 2 && vietNam.y <= y + 1 && y <= vietNam.y + 1) return true;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      return false;
  }
}

bool hitAndRunAmerica1() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america1.y) {
      eraseAmerica(america1.x, america1.y, stateAmerica1);
      --america1.y;
      stateAmerica1 = 1;
      drawAmerica(america1.x, america1.y, 1);
      if (shootVietNam(america1.x, america1.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america1.x != 27) {
      eraseAmerica(america1.x, america1.y, stateAmerica1);
      ++america1.x;
      stateAmerica1 = 2;
      drawAmerica(america1.x, america1.y, 2);
      if (shootVietNam(america1.x, america1.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america1.y != 27) {
      eraseAmerica(america1.x, america1.y, stateAmerica1);
      ++america1.y;
      stateAmerica1 = 3;
      drawAmerica(america1.x, america1.y, 3);
      if (shootVietNam(america1.x, america1.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america1.x) {
      eraseAmerica(america1.x, america1.y, stateAmerica1);
      --america1.x;
      stateAmerica1 = 4;
      drawAmerica(america1.x, america1.y, 4);
      if (shootVietNam(america1.x, america1.y, 4)) return true;
      return false;
    }
  }
}

bool hitAndRunAmerica2() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america2.y) {
      eraseAmerica(america2.x, america2.y, stateAmerica2);
      --america2.y;
      stateAmerica2 = 1;
      drawAmerica(america2.x, america2.y, 1);
      if (shootVietNam(america2.x, america2.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america2.x != 27) {
      eraseAmerica(america2.x, america2.y, stateAmerica2);
      ++america2.x;
      stateAmerica2 = 2;
      drawAmerica(america2.x, america2.y, 2);
      if (shootVietNam(america2.x, america2.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america2.y != 27) {
      eraseAmerica(america2.x, america2.y, stateAmerica2);
      ++america2.y;
      stateAmerica2 = 3;
      drawAmerica(america2.x, america2.y, 3);
      if (shootVietNam(america2.x, america2.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america2.x) {
      eraseAmerica(america2.x, america2.y, stateAmerica2);
      --america2.x;
      stateAmerica2 = 4;
      drawAmerica(america2.x, america2.y, 4);
      if (shootVietNam(america2.x, america2.y, 4)) return true;
      return false;
    }
  }
}

bool hitAndRunAmerica3() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america3.y) {
      eraseAmerica(america3.x, america3.y, stateAmerica3);
      --america3.y;
      stateAmerica3 = 1;
      drawAmerica(america3.x, america3.y, 1);
      if (shootVietNam(america3.x, america3.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america3.x != 27) {
      eraseAmerica(america3.x, america3.y, stateAmerica3);
      ++america3.x;
      stateAmerica3 = 2;
      drawAmerica(america3.x, america3.y, 2);
      if (shootVietNam(america3.x, america3.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america3.y != 27) {
      eraseAmerica(america3.x, america3.y, stateAmerica3);
      ++america3.y;
      stateAmerica3 = 3;
      drawAmerica(america3.x, america3.y, 3);
      if (shootVietNam(america3.x, america3.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america3.x) {
      eraseAmerica(america3.x, america3.y, stateAmerica3);
      --america3.x;
      stateAmerica3 = 4;
      drawAmerica(america3.x, america3.y, 4);
      if (shootVietNam(america3.x, america3.y, 4)) return true;
      return false;
    }
  }
}

bool hitAndRunAmerica4() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america4.y) {
      eraseAmerica(america4.x, america4.y, stateAmerica4);
      --america4.y;
      stateAmerica4 = 1;
      drawAmerica(america4.x, america4.y, 1);
      if (shootVietNam(america4.x, america4.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america4.x != 27) {
      eraseAmerica(america4.x, america4.y, stateAmerica4);
      ++america4.x;
      stateAmerica4 = 2;
      drawAmerica(america4.x, america4.y, 2);
      if (shootVietNam(america4.x, america4.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america4.y != 27) {
      eraseAmerica(america4.x, america4.y, stateAmerica4);
      ++america4.y;
      stateAmerica4 = 3;
      drawAmerica(america4.x, america4.y, 3);
      if (shootVietNam(america4.x, america4.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america4.x) {
      eraseAmerica(america4.x, america4.y, stateAmerica4);
      --america4.x;
      stateAmerica4 = 4;
      drawAmerica(america4.x, america4.y, 4);
      if (shootVietNam(america4.x, america4.y, 4)) return true;
      return false;
    }
  }
}

int newGameTankWar() {
  drawSubScreen(bestTankWar, 0);

  vietNam.x = vietNam.y = 15;
  america1.x = 3; america1.y = 3;
  america2.x = 24; america2.y = 3;
  america3.x = 24; america3.y = 24;
  america4.x = 3; america4.y = 24;

  stateVietNam = 1;
  stateAmerica1 = stateAmerica2 = 3;
  stateAmerica3 = stateAmerica4 = 1;
  
  drawVietNam();
  drawAmerica(3, 3, 3);
  drawAmerica(24, 3, 3);
  drawAmerica(24, 24, 1);
  drawAmerica(3, 24, 1);

  while (1) {
    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica4()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 
  }
}

int continueTankWar() {
  drawSubScreen(bestTankWar, 0);

  drawVietNam();
  drawAmerica(america1.x, america1.y, stateAmerica1);
  drawAmerica(america2.x, america2.y, stateAmerica2);
  drawAmerica(america3.x, america3.y, stateAmerica3);
  drawAmerica(america4.x, america4.y, stateAmerica4);
  
  while (1) {
    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    for (int i = 0; i < 10; ++i) {
      hitAndRunVietNam();
      delay(100);
    }
    if (hitAndRunAmerica4()) {
      if (commonScore > bestTankWar) bestTankWar = commonScore;
      return 1;
    } 
  }
}