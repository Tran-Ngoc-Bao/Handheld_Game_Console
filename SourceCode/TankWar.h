int stateVietNam, stateAmerica1, stateAmerica2, stateAmerica3, stateAmerica4;

coordinates vietNam, america1, america2, america3, america4;

void drawVietNam() {
  switch (stateVietNam) {
    case 1:
      tft.fillRoundRect(vietNam.x * 8, vietNam.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNam.x * 8 + 6, vietNam.y * 8 + 8, 12, 12, 3, yellow);
      tft.fillRect(vietNam.x * 8 + 10, vietNam.y * 8 + 2, 4, 6, indigo);
      break;
    case 2:
      tft.fillRoundRect(vietNam.x * 8, vietNam.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNam.x * 8 + 4, vietNam.y * 8 + 6, 12, 12, 3, yellow);
      tft.fillRect(vietNam.x * 8 + 16, vietNam.y * 8 + 10, 6, 4, indigo);
      break;
    case 3:
      tft.fillRoundRect(vietNam.x * 8, vietNam.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNam.x * 8 + 6, vietNam.y * 8 + 4, 12, 12, 3, yellow);
      tft.fillRect(vietNam.x * 8 + 10, vietNam.y * 8 + 16, 4, 6, indigo);
      break;
    default:
      tft.fillRoundRect(vietNam.x * 8, vietNam.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNam.x * 8 + 8, vietNam.y * 8 + 6, 12, 12, 3, yellow);
      tft.fillRect(vietNam.x * 8 + 2, vietNam.y * 8 + 10, 6, 4, indigo);
  }
}

void drawAmerica(int x, int y, int state) {
  switch (state) {
    case 1:
      tft.fillRoundRect(x * 8, y * 8, 24, 24, 5, indigo);
      tft.fillRoundRect(x * 8 + 6, y * 8 + 8, 12, 12, 3, red);
      tft.fillRect(x * 8 + 10, y * 8 + 2, 4, 6, white);
      break;
    case 2:
      tft.fillRoundRect(x * 8, y * 8, 24, 24, 5, indigo);
      tft.fillRoundRect(x * 8 + 4, y * 8 + 6, 12, 12, 3, red);
      tft.fillRect(x * 8 + 16, y * 8 + 10, 6, 4, white);
      break;
    case 3:
      tft.fillRoundRect(x * 8, y * 8, 24, 24, 5, indigo);
      tft.fillRoundRect(x * 8 + 6, y * 8 + 4, 12, 12, 3, red);
      tft.fillRect(x * 8 + 10, y * 8 + 16, 4, 6, white);
      break;
    default:
      tft.fillRoundRect(x * 8, y * 8, 24, 24, 5, indigo);
      tft.fillRoundRect(x * 8 + 8, y * 8 + 6, 12, 12, 3, red);
      tft.fillRect(x * 8 + 2, y * 8 + 10, 6, 4, white);
  }
}

bool killAmerica(int x, int y) {
  if (america1.x <= x && x <= america1.x + 2 && america1.y <= y && y <= america1.y + 2) {
    tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
    increaseScore();
    america1.x = 3;
    america1.y = 3;
    drawAmerica(3, 3, 3);
    return true;
  }
  if (america2.x <= x && x <= america2.x + 2 && america2.y <= y && y <= america2.y + 2) {
    tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
    increaseScore();
    america2.x = 24;
    america2.y = 3;
    drawAmerica(24, 3, 3);
    return true;
  }
  if (america3.x <= x && x <= america3.x + 2 && america3.y <= y && y <= america3.y + 2) {
    tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
    increaseScore();
    america3.x = 24;
    america3.y = 24;
    drawAmerica(24, 24, 1);
    return true;
  }
  if (america4.x <= x && x <= america4.x + 2 && america4.y <= y && y <= america4.y + 2) {
    tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
    increaseScore();
    america4.x = 3;
    america4.y = 24;
    drawAmerica(3, 24, 1);
    return true;
  }
  return false;
}

void shootAmerica() {
  switch (stateVietNam) {
    case 1:
      for (int i = vietNam.y - 1; i >= 0; --i) {
        tft.fillRoundRect(vietNam.x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(vietNam.x + 1, i)) break;
        tft.fillRect(vietNam.x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    case 2:
      for (int i = vietNam.x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, vietNam.y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, vietNam.y + 1)) break;
        tft.fillRect(i * 8, vietNam.y * 8 + 8, 8, 8, black);
        delay(10);
      }
      break;
    case 3:
      for (int i = vietNam.y + 4; i < 30; ++i) {
        tft.fillRoundRect(vietNam.x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(vietNam.x + 1, i)) break;
        tft.fillRect(vietNam.x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    default:
      for (int i = vietNam.x - 1; i >= 0; --i) {
        tft.fillRoundRect(i * 8, vietNam.y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, vietNam.y + 1)) break;
        tft.fillRect(i * 8, vietNam.y * 8 + 8, 8, 8, black);
        delay(10);
      }
  }
}

void runVietNam() {
  if (!digitalRead(top) && vietNam.y) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);
    --vietNam.y;
    stateVietNam = 1;
    drawVietNam();
  } else if (!digitalRead(right) && vietNam.x != 27) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);
    ++vietNam.x;
    stateVietNam = 2;
    drawVietNam();
  } else if (!digitalRead(bottom) && vietNam.y != 27) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);
    ++vietNam.y;
    stateVietNam = 3;
    drawVietNam();
  } else if (!digitalRead(left) && vietNam.x) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);
    --vietNam.x;
    stateVietNam = 4;
    drawVietNam();
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

void hitAndRunVietNam() {
  for (int i = 0; i < 5; ++i) {
    runVietNam();
    if (!digitalRead(enter)) shootAmerica();
    delay(100);
  }
}

bool checkHARA1(int state) {
  switch (state) {
    case 1: 
      if (vietNam.x > america1.x - 2 && vietNam.x < america1.x + 2 && vietNam.y < america1.y) return true;
      if (america2.x > america1.x - 2 && america2.x < america1.x + 2 && america2.y < america1.y) return false;
      if (america3.x > america1.x - 2 && america3.x < america1.x + 2 && america3.y < america1.y) return false;
      if (america4.x > america1.x - 2 && america4.x < america1.x + 2 && america4.y < america1.y) return false;
      return true;
    case 2:
      if (vietNam.y > america1.y - 2 && vietNam.y < america1.y + 2 && vietNam.x > america1.x) return true;
      if (america2.y > america1.y - 2 && america2.y < america1.y + 2 && america2.x > america1.x) return false;
      if (america3.y > america1.y - 2 && america3.y < america1.y + 2 && america3.x > america1.x) return false;
      if (america4.y > america1.y - 2 && america4.y < america1.y + 2 && america4.x > america1.x) return false;
      return true;
    case 3: 
      if (vietNam.x > america1.x - 2 && vietNam.x < america1.x + 2 && vietNam.y > america1.y) return true;
      if (america2.x > america1.x - 2 && america2.x < america1.x + 2 && america2.y > america1.y) return false;
      if (america3.x > america1.x - 2 && america3.x < america1.x + 2 && america3.y > america1.y) return false;
      if (america4.x > america1.x - 2 && america4.x < america1.x + 2 && america4.y > america1.y) return false;
      return true;
    default:
      if (vietNam.y > america1.y - 2 && vietNam.y < america1.y + 2 && vietNam.x < america1.x) return true;
      if (america2.y > america1.y - 2 && america2.y < america1.y + 2 && america2.x < america1.x) return false;
      if (america3.y > america1.y - 2 && america3.y < america1.y + 2 && america3.x < america1.x) return false;
      if (america4.y > america1.y - 2 && america4.y < america1.y + 2 && america4.x < america1.x) return false;
      return true;
  }
}

bool hitAndRunAmerica1() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america1.y > 3) {
      stateAmerica1 = 1;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      --america1.y;
      drawAmerica(america1.x, america1.y, 1);
      hitAndRunVietNam();
      if (checkHARA1(1) && shootVietNam(america1.x, america1.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america1.x < 24) {
      stateAmerica1 = 2;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.x;
      drawAmerica(america1.x, america1.y, 2);
      hitAndRunVietNam();
      if (checkHARA1(2) && shootVietNam(america1.x, america1.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america1.y < 24) {
      stateAmerica1 = 3;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.y;
      drawAmerica(america1.x, america1.y, 3);
      hitAndRunVietNam();
      if (checkHARA1(3) && shootVietNam(america1.x, america1.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america1.x > 3) {
      stateAmerica1 = 4;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      --america1.x;
      drawAmerica(america1.x, america1.y, 4);
      hitAndRunVietNam();
      if (checkHARA1(4) && shootVietNam(america1.x, america1.y, 4)) return true;
      return false;
    }
  }
}

bool checkHARA2(int state) {
  switch (state) {
    case 1: 
      if (vietNam.x > america2.x - 2 && vietNam.x < america2.x + 2 && vietNam.y < america2.y) return true;
      if (america1.x > america2.x - 2 && america1.x < america2.x + 2 && america1.y < america2.y) return false;
      if (america3.x > america2.x - 2 && america3.x < america2.x + 2 && america3.y < america2.y) return false;
      if (america4.x > america2.x - 2 && america4.x < america2.x + 2 && america4.y < america2.y) return false;
      return true;
    case 2:
      if (vietNam.y > america2.y - 2 && vietNam.y < america2.y + 2 && vietNam.x > america2.x) return true;
      if (america1.y > america2.y - 2 && america1.y < america2.y + 2 && america1.x > america2.x) return false;
      if (america3.y > america2.y - 2 && america3.y < america2.y + 2 && america3.x > america2.x) return false;
      if (america4.y > america2.y - 2 && america4.y < america2.y + 2 && america4.x > america2.x) return false;
      return true;
    case 3: 
      if (vietNam.x > america2.x - 2 && vietNam.x < america2.x + 2 && vietNam.y > america2.y) return true;
      if (america1.x > america2.x - 2 && america1.x < america2.x + 2 && america1.y > america2.y) return false;
      if (america3.x > america2.x - 2 && america3.x < america2.x + 2 && america3.y > america2.y) return false;
      if (america4.x > america2.x - 2 && america4.x < america2.x + 2 && america4.y > america2.y) return false;
      return true;
    default:
      if (vietNam.y > america2.y - 2 && vietNam.y < america2.y + 2 && vietNam.x < america2.x) return true;
      if (america1.y > america2.y - 2 && america1.y < america2.y + 2 && america1.x < america2.x) return false;
      if (america3.y > america2.y - 2 && america3.y < america2.y + 2 && america3.x < america2.x) return false;
      if (america4.y > america2.y - 2 && america4.y < america2.y + 2 && america4.x < america2.x) return false;
      return true;
  }
}

bool hitAndRunAmerica2() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america2.y > 3) {
      stateAmerica2 = 1;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.y;
      drawAmerica(america2.x, america2.y, 1);
      hitAndRunVietNam();
      if (checkHARA2(1) && shootVietNam(america2.x, america2.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america2.x < 24) {
      stateAmerica2 = 2;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.x;
      drawAmerica(america2.x, america2.y, 2);
      hitAndRunVietNam();
      if (checkHARA2(2) && shootVietNam(america2.x, america2.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america2.y < 24) {
      stateAmerica2 = 3;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.y;
      drawAmerica(america2.x, america2.y, 3);
      hitAndRunVietNam();
      if (checkHARA2(3) && shootVietNam(america2.x, america2.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america2.x > 3) {
      stateAmerica2 = 4;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.x;
      drawAmerica(america2.x, america2.y, 4);
      hitAndRunVietNam();
      if (checkHARA2(4) && shootVietNam(america2.x, america2.y, 4)) return true;
      return false;
    }
  }
}

bool checkHARA3(int state) {
  switch (state) {
    case 1: 
      if (vietNam.x > america3.x - 2 && vietNam.x < america3.x + 2 && vietNam.y < america3.y) return true;
      if (america1.x > america3.x - 2 && america1.x < america3.x + 2 && america1.y < america3.y) return false;
      if (america2.x > america3.x - 2 && america2.x < america3.x + 2 && america2.y < america3.y) return false;
      if (america4.x > america3.x - 2 && america4.x < america3.x + 2 && america4.y < america3.y) return false;
      return true;
    case 2:
      if (vietNam.y > america3.y - 2 && vietNam.y < america3.y + 2 && vietNam.x > america3.x) return true;
      if (america1.y > america3.y - 2 && america1.y < america3.y + 2 && america1.x > america3.x) return false;
      if (america2.y > america3.y - 2 && america2.y < america3.y + 2 && america2.x > america3.x) return false;
      if (america4.y > america3.y - 2 && america4.y < america3.y + 2 && america4.x > america3.x) return false;
      return true;
    case 3: 
      if (vietNam.x > america3.x - 2 && vietNam.x < america3.x + 2 && vietNam.y > america3.y) return true;
      if (america1.x > america3.x - 2 && america1.x < america3.x + 2 && america1.y > america3.y) return false;
      if (america2.x > america3.x - 2 && america2.x < america3.x + 2 && america2.y > america3.y) return false;
      if (america4.x > america3.x - 2 && america4.x < america3.x + 2 && america4.y > america3.y) return false;
      return true;
    default:
      if (vietNam.y > america3.y - 2 && vietNam.y < america3.y + 2 && vietNam.x < america3.x) return true;
      if (america1.y > america3.y - 2 && america1.y < america3.y + 2 && america1.x < america3.x) return false;
      if (america2.y > america3.y - 2 && america2.y < america3.y + 2 && america2.x < america3.x) return false;
      if (america4.y > america3.y - 2 && america4.y < america3.y + 2 && america4.x < america3.x) return false;
      return true;
  }
}

bool hitAndRunAmerica3() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america3.y > 3) {
      stateAmerica3 = 1;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.y;
      drawAmerica(america3.x, america3.y, 1);
      hitAndRunVietNam();
      if (checkHARA3(1) && shootVietNam(america3.x, america3.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america3.x < 24) {
      stateAmerica3 = 2;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.x;
      drawAmerica(america3.x, america3.y, 2);
      hitAndRunVietNam();
      if (checkHARA3(2) && shootVietNam(america3.x, america3.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america3.y < 24) {
      stateAmerica3 = 3;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.y;
      drawAmerica(america3.x, america3.y, 3);
      hitAndRunVietNam();
      if (checkHARA3(3) && shootVietNam(america3.x, america3.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america3.x > 3) {
      stateAmerica3 = 4;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.x;
      drawAmerica(america3.x, america3.y, 4);
      hitAndRunVietNam();
      if (checkHARA3(4) && shootVietNam(america3.x, america3.y, 4)) return true;
      return false;
    }
  }
}

bool checkHARA4(int state) {
  switch (state) {
    case 1: 
      if (vietNam.x > america4.x - 2 && vietNam.x < america4.x + 2 && vietNam.y < america4.y) return true;
      if (america1.x > america4.x - 2 && america1.x < america4.x + 2 && america1.y < america4.y) return false;
      if (america2.x > america4.x - 2 && america2.x < america4.x + 2 && america2.y < america4.y) return false;
      if (america3.x > america4.x - 2 && america3.x < america4.x + 2 && america3.y < america4.y) return false;
      return true;
    case 2:
      if (vietNam.y > america4.y - 2 && vietNam.y < america4.y + 2 && vietNam.x > america4.x) return true;
      if (america1.y > america4.y - 2 && america1.y < america4.y + 2 && america1.x > america4.x) return false;
      if (america2.y > america4.y - 2 && america2.y < america4.y + 2 && america2.x > america4.x) return false;
      if (america3.y > america4.y - 2 && america3.y < america4.y + 2 && america3.x > america4.x) return false;
      return true;
    case 3: 
      if (vietNam.x > america4.x - 2 && vietNam.x < america4.x + 2 && vietNam.y > america4.y) return true;
      if (america1.x > america4.x - 2 && america1.x < america4.x + 2 && america1.y > america4.y) return false;
      if (america2.x > america4.x - 2 && america2.x < america4.x + 2 && america2.y > america4.y) return false;
      if (america3.x > america4.x - 2 && america3.x < america4.x + 2 && america3.y > america4.y) return false;
      return true;
    default:
      if (vietNam.y > america4.y - 2 && vietNam.y < america4.y + 2 && vietNam.x < america4.x) return true;
      if (america1.y > america4.y - 2 && america1.y < america4.y + 2 && america1.x < america4.x) return false;
      if (america2.y > america4.y - 2 && america2.y < america4.y + 2 && america2.x < america4.x) return false;
      if (america3.y > america4.y - 2 && america3.y < america4.y + 2 && america3.x < america4.x) return false;
      return true;
  }
}

bool hitAndRunAmerica4() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america4.y > 3) {
      stateAmerica4 = 1;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.y;
      drawAmerica(america4.x, america4.y, 1);
      hitAndRunVietNam();
      if (checkHARA4(1) && shootVietNam(america4.x, america4.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america4.x < 24) {
      stateAmerica4 = 2;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.x;
      drawAmerica(america4.x, america4.y, 2);
      hitAndRunVietNam();
      if (checkHARA4(2) && shootVietNam(america4.x, america4.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america4.y < 24) {
      stateAmerica4 = 3;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.y;
      drawAmerica(america4.x, america4.y, 3);
      hitAndRunVietNam();
      if (checkHARA4(3) && shootVietNam(america4.x, america4.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america4.x > 3) {
      stateAmerica4 = 4;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.x;
      drawAmerica(america4.x, america4.y, 4);
      hitAndRunVietNam();
      if (checkHARA4(4) && shootVietNam(america4.x, america4.y, 4)) return true;
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
    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica4()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
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
    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica4()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 
  }
}