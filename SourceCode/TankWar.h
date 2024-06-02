// State of gun direction
int stateVietNamTankWar, stateAmerica1TankWar, stateAmerica2TankWar, stateAmerica3TankWar, stateAmerica4TankWar;

coordinates vietNamTankWar, america1TankWar, america2TankWar, america3TankWar, america4TankWar;

void drawVietNamTankWar() {
  switch (stateVietNamTankWar) {
    case 1:
      tft.fillRoundRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNamTankWar.x * 8 + 6, vietNamTankWar.y * 8 + 8, 12, 12, 3, yellow);
      tft.fillRect(vietNamTankWar.x * 8 + 10, vietNamTankWar.y * 8 + 2, 4, 6, indigo);
      break;
    case 2:
      tft.fillRoundRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNamTankWar.x * 8 + 4, vietNamTankWar.y * 8 + 6, 12, 12, 3, yellow);
      tft.fillRect(vietNamTankWar.x * 8 + 16, vietNamTankWar.y * 8 + 10, 6, 4, indigo);
      break;
    case 3:
      tft.fillRoundRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNamTankWar.x * 8 + 6, vietNamTankWar.y * 8 + 4, 12, 12, 3, yellow);
      tft.fillRect(vietNamTankWar.x * 8 + 10, vietNamTankWar.y * 8 + 16, 4, 6, indigo);
      break;
    default:
      tft.fillRoundRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, 5, red);
      tft.fillRoundRect(vietNamTankWar.x * 8 + 8, vietNamTankWar.y * 8 + 6, 12, 12, 3, yellow);
      tft.fillRect(vietNamTankWar.x * 8 + 2, vietNamTankWar.y * 8 + 10, 6, 4, indigo);
  }
}

void drawAmericaTankWar(int x, int y, int state) {
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

// (x, y) is coordinates of Viet Nam bullet
bool killAmericaTankWar(int x, int y) {
  if (america1TankWar.x <= x && x <= america1TankWar.x + 2 && america1TankWar.y <= y && y <= america1TankWar.y + 2) {
    tft.fillRect(america1TankWar.x * 8, america1TankWar.y * 8, 24, 24, black);
    tone(buzzer, 349, 120);
    increaseScore();
    america1TankWar.x = 3;
    america1TankWar.y = 3;
    drawAmericaTankWar(3, 3, 3);
    return true;
  }
  if (america2TankWar.x <= x && x <= america2TankWar.x + 2 && america2TankWar.y <= y && y <= america2TankWar.y + 2) {
    tft.fillRect(america2TankWar.x * 8, america2TankWar.y * 8, 24, 24, black);
    tone(buzzer, 349, 120);
    increaseScore();
    america2TankWar.x = 24;
    america2TankWar.y = 3;
    drawAmericaTankWar(24, 3, 3);
    return true;
  }
  if (america3TankWar.x <= x && x <= america3TankWar.x + 2 && america3TankWar.y <= y && y <= america3TankWar.y + 2) {
    tft.fillRect(america3TankWar.x * 8, america3TankWar.y * 8, 24, 24, black);
    tone(buzzer, 349, 120);
    increaseScore();
    america3TankWar.x = 24;
    america3TankWar.y = 24;
    drawAmericaTankWar(24, 24, 1);
    return true;
  }
  if (america4TankWar.x <= x && x <= america4TankWar.x + 2 && america4TankWar.y <= y && y <= america4TankWar.y + 2) {
    tft.fillRect(america4TankWar.x * 8, america4TankWar.y * 8, 24, 24, black);
    tone(buzzer, 349, 120);
    increaseScore();
    america4TankWar.x = 3;
    america4TankWar.y = 24;
    drawAmericaTankWar(3, 24, 1);
    return true;
  }
  return false;
}

void shootAmericaTankWar() {
  switch (stateVietNamTankWar) {
    case 1:
      // Fly bullet animation
      for (int i = vietNamTankWar.y - 1; i >= 0; --i) {
        tft.fillRoundRect(vietNamTankWar.x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmericaTankWar(vietNamTankWar.x + 1, i)) break;
        tft.fillRect(vietNamTankWar.x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    case 2:
      for (int i = vietNamTankWar.x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, vietNamTankWar.y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmericaTankWar(i, vietNamTankWar.y + 1)) break;
        tft.fillRect(i * 8, vietNamTankWar.y * 8 + 8, 8, 8, black);
        delay(10);
      }
      break;
    case 3:
      for (int i = vietNamTankWar.y + 4; i < 30; ++i) {
        tft.fillRoundRect(vietNamTankWar.x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmericaTankWar(vietNamTankWar.x + 1, i)) break;
        tft.fillRect(vietNamTankWar.x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    default:
      for (int i = vietNamTankWar.x - 1; i >= 0; --i) {
        tft.fillRoundRect(i * 8, vietNamTankWar.y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmericaTankWar(i, vietNamTankWar.y + 1)) break;
        tft.fillRect(i * 8, vietNamTankWar.y * 8 + 8, 8, 8, black);
        delay(10);
      }
  }
}

// Viet Nam moves top, right, bottom, left with state of gun direction
void runVietNamTankWar() {
  if (!digitalRead(top) && vietNamTankWar.y) {
    tft.fillRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, black);
    --vietNamTankWar.y;
    stateVietNamTankWar = 1;
    drawVietNamTankWar();
  } else if (!digitalRead(right) && vietNamTankWar.x != 27) {
    tft.fillRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, black);
    ++vietNamTankWar.x;
    stateVietNamTankWar = 2;
    drawVietNamTankWar();
  } else if (!digitalRead(bottom) && vietNamTankWar.y != 27) {
    tft.fillRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, black);
    ++vietNamTankWar.y;
    stateVietNamTankWar = 3;
    drawVietNamTankWar();
  } else if (!digitalRead(left) && vietNamTankWar.x) {
    tft.fillRect(vietNamTankWar.x * 8, vietNamTankWar.y * 8, 24, 24, black);
    --vietNamTankWar.x;
    stateVietNamTankWar = 4;
    drawVietNamTankWar();
  }
}

void hitAndRunVietNamTankWar() {
  for (int i = 0; i < 5; ++i) {
    runVietNamTankWar();
    if (!digitalRead(enter)) shootAmericaTankWar();
    delay(100);
  }
}

// America shoot Viet Nam with coordinates (x, y) and gun direction state
bool shootVietNamTankWar(int x, int y, int state) {
  switch (state) {
    case 1:
      for (int i = y - 1; i >= 0; --i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (vietNamTankWar.x <= x + 1 && x <= vietNamTankWar.x + 1 && vietNamTankWar.y <= i && i <= vietNamTankWar.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      return false;
    case 2:
      for (int i = x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (vietNamTankWar.x <= i && i <= vietNamTankWar.x + 2 && vietNamTankWar.y <= y + 1 && y <= vietNamTankWar.y + 1) return true;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      return false;
    case 3:
      for (int i = y + 4; i < 30; ++i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (vietNamTankWar.x <= x + 1 && x <= vietNamTankWar.x + 1 && vietNamTankWar.y <= i && i <= vietNamTankWar.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      return false;
    default:
      for (int i = x - 1; i >= 0; --i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (vietNamTankWar.x <= i && i <= vietNamTankWar.x + 2 && vietNamTankWar.y <= y + 1 && y <= vietNamTankWar.y + 1) return true;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      return false;
  }
}

// Do not shoot teammate
bool checkHitAndRunAmerica1TankWar(int state) {
  switch (state) {
    case 1: 
      if (vietNamTankWar.x > america1TankWar.x - 2 && vietNamTankWar.x < america1TankWar.x + 2 && vietNamTankWar.y < america1TankWar.y) return true;
      if (america2TankWar.x > america1TankWar.x - 2 && america2TankWar.x < america1TankWar.x + 2 && america2TankWar.y < america1TankWar.y) return false;
      if (america3TankWar.x > america1TankWar.x - 2 && america3TankWar.x < america1TankWar.x + 2 && america3TankWar.y < america1TankWar.y) return false;
      if (america4TankWar.x > america1TankWar.x - 2 && america4TankWar.x < america1TankWar.x + 2 && america4TankWar.y < america1TankWar.y) return false;
      return true;
    case 2:
      if (vietNamTankWar.y > america1TankWar.y - 2 && vietNamTankWar.y < america1TankWar.y + 2 && vietNamTankWar.x > america1TankWar.x) return true;
      if (america2TankWar.y > america1TankWar.y - 2 && america2TankWar.y < america1TankWar.y + 2 && america2TankWar.x > america1TankWar.x) return false;
      if (america3TankWar.y > america1TankWar.y - 2 && america3TankWar.y < america1TankWar.y + 2 && america3TankWar.x > america1TankWar.x) return false;
      if (america4TankWar.y > america1TankWar.y - 2 && america4TankWar.y < america1TankWar.y + 2 && america4TankWar.x > america1TankWar.x) return false;
      return true;
    case 3: 
      if (vietNamTankWar.x > america1TankWar.x - 2 && vietNamTankWar.x < america1TankWar.x + 2 && vietNamTankWar.y > america1TankWar.y) return true;
      if (america2TankWar.x > america1TankWar.x - 2 && america2TankWar.x < america1TankWar.x + 2 && america2TankWar.y > america1TankWar.y) return false;
      if (america3TankWar.x > america1TankWar.x - 2 && america3TankWar.x < america1TankWar.x + 2 && america3TankWar.y > america1TankWar.y) return false;
      if (america4TankWar.x > america1TankWar.x - 2 && america4TankWar.x < america1TankWar.x + 2 && america4TankWar.y > america1TankWar.y) return false;
      return true;
    default:
      if (vietNamTankWar.y > america1TankWar.y - 2 && vietNamTankWar.y < america1TankWar.y + 2 && vietNamTankWar.x < america1TankWar.x) return true;
      if (america2TankWar.y > america1TankWar.y - 2 && america2TankWar.y < america1TankWar.y + 2 && america2TankWar.x < america1TankWar.x) return false;
      if (america3TankWar.y > america1TankWar.y - 2 && america3TankWar.y < america1TankWar.y + 2 && america3TankWar.x < america1TankWar.x) return false;
      if (america4TankWar.y > america1TankWar.y - 2 && america4TankWar.y < america1TankWar.y + 2 && america4TankWar.x < america1TankWar.x) return false;
      return true;
  }
}

bool hitAndRunAmerica1TankWar() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america1TankWar.y > 3) {
      stateAmerica1TankWar = 1;
      tft.fillRect(america1TankWar.x * 8, america1TankWar.y * 8, 24, 24, black);
      --america1TankWar.y;
      drawAmericaTankWar(america1TankWar.x, america1TankWar.y, 1);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica1TankWar(1) && shootVietNamTankWar(america1TankWar.x, america1TankWar.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america1TankWar.x < 24) {
      stateAmerica1TankWar = 2;
      tft.fillRect(america1TankWar.x * 8, america1TankWar.y * 8, 24, 24, black);
      ++america1TankWar.x;
      drawAmericaTankWar(america1TankWar.x, america1TankWar.y, 2);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica1TankWar(2) && shootVietNamTankWar(america1TankWar.x, america1TankWar.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america1TankWar.y < 24) {
      stateAmerica1TankWar = 3;
      tft.fillRect(america1TankWar.x * 8, america1TankWar.y * 8, 24, 24, black);
      ++america1TankWar.y;
      drawAmericaTankWar(america1TankWar.x, america1TankWar.y, 3);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica1TankWar(3) && shootVietNamTankWar(america1TankWar.x, america1TankWar.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america1TankWar.x > 3) {
      stateAmerica1TankWar = 4;
      tft.fillRect(america1TankWar.x * 8, america1TankWar.y * 8, 24, 24, black);
      --america1TankWar.x;
      drawAmericaTankWar(america1TankWar.x, america1TankWar.y, 4);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica1TankWar(4) && shootVietNamTankWar(america1TankWar.x, america1TankWar.y, 4)) return true;
      return false;
    }
  }
}

// Do not shoot teammate
bool checkHitAndRunAmerica2TankWar(int state) {
  switch (state) {
    case 1: 
      if (vietNamTankWar.x > america2TankWar.x - 2 && vietNamTankWar.x < america2TankWar.x + 2 && vietNamTankWar.y < america2TankWar.y) return true;
      if (america1TankWar.x > america2TankWar.x - 2 && america1TankWar.x < america2TankWar.x + 2 && america1TankWar.y < america2TankWar.y) return false;
      if (america3TankWar.x > america2TankWar.x - 2 && america3TankWar.x < america2TankWar.x + 2 && america3TankWar.y < america2TankWar.y) return false;
      if (america4TankWar.x > america2TankWar.x - 2 && america4TankWar.x < america2TankWar.x + 2 && america4TankWar.y < america2TankWar.y) return false;
      return true;
    case 2:
      if (vietNamTankWar.y > america2TankWar.y - 2 && vietNamTankWar.y < america2TankWar.y + 2 && vietNamTankWar.x > america2TankWar.x) return true;
      if (america1TankWar.y > america2TankWar.y - 2 && america1TankWar.y < america2TankWar.y + 2 && america1TankWar.x > america2TankWar.x) return false;
      if (america3TankWar.y > america2TankWar.y - 2 && america3TankWar.y < america2TankWar.y + 2 && america3TankWar.x > america2TankWar.x) return false;
      if (america4TankWar.y > america2TankWar.y - 2 && america4TankWar.y < america2TankWar.y + 2 && america4TankWar.x > america2TankWar.x) return false;
      return true;
    case 3: 
      if (vietNamTankWar.x > america2TankWar.x - 2 && vietNamTankWar.x < america2TankWar.x + 2 && vietNamTankWar.y > america2TankWar.y) return true;
      if (america1TankWar.x > america2TankWar.x - 2 && america1TankWar.x < america2TankWar.x + 2 && america1TankWar.y > america2TankWar.y) return false;
      if (america3TankWar.x > america2TankWar.x - 2 && america3TankWar.x < america2TankWar.x + 2 && america3TankWar.y > america2TankWar.y) return false;
      if (america4TankWar.x > america2TankWar.x - 2 && america4TankWar.x < america2TankWar.x + 2 && america4TankWar.y > america2TankWar.y) return false;
      return true;
    default:
      if (vietNamTankWar.y > america2TankWar.y - 2 && vietNamTankWar.y < america2TankWar.y + 2 && vietNamTankWar.x < america2TankWar.x) return true;
      if (america1TankWar.y > america2TankWar.y - 2 && america1TankWar.y < america2TankWar.y + 2 && america1TankWar.x < america2TankWar.x) return false;
      if (america3TankWar.y > america2TankWar.y - 2 && america3TankWar.y < america2TankWar.y + 2 && america3TankWar.x < america2TankWar.x) return false;
      if (america4TankWar.y > america2TankWar.y - 2 && america4TankWar.y < america2TankWar.y + 2 && america4TankWar.x < america2TankWar.x) return false;
      return true;
  }
}

bool hitAndRunAmerica2TankWar() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america2TankWar.y > 3) {
      stateAmerica2TankWar = 1;
      tft.fillRect(america2TankWar.x * 8, america2TankWar.y * 8, 24, 24, black);
      --america2TankWar.y;
      drawAmericaTankWar(america2TankWar.x, america2TankWar.y, 1);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica2TankWar(1) && shootVietNamTankWar(america2TankWar.x, america2TankWar.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america2TankWar.x < 24) {
      stateAmerica2TankWar = 2;
      tft.fillRect(america2TankWar.x * 8, america2TankWar.y * 8, 24, 24, black);
      ++america2TankWar.x;
      drawAmericaTankWar(america2TankWar.x, america2TankWar.y, 2);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica2TankWar(2) && shootVietNamTankWar(america2TankWar.x, america2TankWar.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america2TankWar.y < 24) {
      stateAmerica2TankWar = 3;
      tft.fillRect(america2TankWar.x * 8, america2TankWar.y * 8, 24, 24, black);
      ++america2TankWar.y;
      drawAmericaTankWar(america2TankWar.x, america2TankWar.y, 3);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica2TankWar(3) && shootVietNamTankWar(america2TankWar.x, america2TankWar.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america2TankWar.x > 3) {
      stateAmerica2TankWar = 4;
      tft.fillRect(america2TankWar.x * 8, america2TankWar.y * 8, 24, 24, black);
      --america2TankWar.x;
      drawAmericaTankWar(america2TankWar.x, america2TankWar.y, 4);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica2TankWar(4) && shootVietNamTankWar(america2TankWar.x, america2TankWar.y, 4)) return true;
      return false;
    }
  }
}

// Do not shoot teammate
bool checkHitAndRunAmerica3TankWar(int state) {
  switch (state) {
    case 1: 
      if (vietNamTankWar.x > america3TankWar.x - 2 && vietNamTankWar.x < america3TankWar.x + 2 && vietNamTankWar.y < america3TankWar.y) return true;
      if (america1TankWar.x > america3TankWar.x - 2 && america1TankWar.x < america3TankWar.x + 2 && america1TankWar.y < america3TankWar.y) return false;
      if (america2TankWar.x > america3TankWar.x - 2 && america2TankWar.x < america3TankWar.x + 2 && america2TankWar.y < america3TankWar.y) return false;
      if (america4TankWar.x > america3TankWar.x - 2 && america4TankWar.x < america3TankWar.x + 2 && america4TankWar.y < america3TankWar.y) return false;
      return true;
    case 2:
      if (vietNamTankWar.y > america3TankWar.y - 2 && vietNamTankWar.y < america3TankWar.y + 2 && vietNamTankWar.x > america3TankWar.x) return true;
      if (america1TankWar.y > america3TankWar.y - 2 && america1TankWar.y < america3TankWar.y + 2 && america1TankWar.x > america3TankWar.x) return false;
      if (america2TankWar.y > america3TankWar.y - 2 && america2TankWar.y < america3TankWar.y + 2 && america2TankWar.x > america3TankWar.x) return false;
      if (america4TankWar.y > america3TankWar.y - 2 && america4TankWar.y < america3TankWar.y + 2 && america4TankWar.x > america3TankWar.x) return false;
      return true;
    case 3: 
      if (vietNamTankWar.x > america3TankWar.x - 2 && vietNamTankWar.x < america3TankWar.x + 2 && vietNamTankWar.y > america3TankWar.y) return true;
      if (america1TankWar.x > america3TankWar.x - 2 && america1TankWar.x < america3TankWar.x + 2 && america1TankWar.y > america3TankWar.y) return false;
      if (america2TankWar.x > america3TankWar.x - 2 && america2TankWar.x < america3TankWar.x + 2 && america2TankWar.y > america3TankWar.y) return false;
      if (america4TankWar.x > america3TankWar.x - 2 && america4TankWar.x < america3TankWar.x + 2 && america4TankWar.y > america3TankWar.y) return false;
      return true;
    default:
      if (vietNamTankWar.y > america3TankWar.y - 2 && vietNamTankWar.y < america3TankWar.y + 2 && vietNamTankWar.x < america3TankWar.x) return true;
      if (america1TankWar.y > america3TankWar.y - 2 && america1TankWar.y < america3TankWar.y + 2 && america1TankWar.x < america3TankWar.x) return false;
      if (america2TankWar.y > america3TankWar.y - 2 && america2TankWar.y < america3TankWar.y + 2 && america2TankWar.x < america3TankWar.x) return false;
      if (america4TankWar.y > america3TankWar.y - 2 && america4TankWar.y < america3TankWar.y + 2 && america4TankWar.x < america3TankWar.x) return false;
      return true;
  }
}

bool hitAndRunAmerica3TankWar() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america3TankWar.y > 3) {
      stateAmerica3TankWar = 1;
      tft.fillRect(america3TankWar.x * 8, america3TankWar.y * 8, 24, 24, black);
      --america3TankWar.y;
      drawAmericaTankWar(america3TankWar.x, america3TankWar.y, 1);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica3TankWar(1) && shootVietNamTankWar(america3TankWar.x, america3TankWar.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america3TankWar.x < 24) {
      stateAmerica3TankWar = 2;
      tft.fillRect(america3TankWar.x * 8, america3TankWar.y * 8, 24, 24, black);
      ++america3TankWar.x;
      drawAmericaTankWar(america3TankWar.x, america3TankWar.y, 2);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica3TankWar(2) && shootVietNamTankWar(america3TankWar.x, america3TankWar.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america3TankWar.y < 24) {
      stateAmerica3TankWar = 3;
      tft.fillRect(america3TankWar.x * 8, america3TankWar.y * 8, 24, 24, black);
      ++america3TankWar.y;
      drawAmericaTankWar(america3TankWar.x, america3TankWar.y, 3);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica3TankWar(3) && shootVietNamTankWar(america3TankWar.x, america3TankWar.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america3TankWar.x > 3) {
      stateAmerica3TankWar = 4;
      tft.fillRect(america3TankWar.x * 8, america3TankWar.y * 8, 24, 24, black);
      --america3TankWar.x;
      drawAmericaTankWar(america3TankWar.x, america3TankWar.y, 4);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica3TankWar(4) && shootVietNamTankWar(america3TankWar.x, america3TankWar.y, 4)) return true;
      return false;
    }
  }
}

// Do not shoot teammate
bool checkHitAndRunAmerica4TankWar(int state) {
  switch (state) {
    case 1: 
      if (vietNamTankWar.x > america4TankWar.x - 2 && vietNamTankWar.x < america4TankWar.x + 2 && vietNamTankWar.y < america4TankWar.y) return true;
      if (america1TankWar.x > america4TankWar.x - 2 && america1TankWar.x < america4TankWar.x + 2 && america1TankWar.y < america4TankWar.y) return false;
      if (america2TankWar.x > america4TankWar.x - 2 && america2TankWar.x < america4TankWar.x + 2 && america2TankWar.y < america4TankWar.y) return false;
      if (america3TankWar.x > america4TankWar.x - 2 && america3TankWar.x < america4TankWar.x + 2 && america3TankWar.y < america4TankWar.y) return false;
      return true;
    case 2:
      if (vietNamTankWar.y > america4TankWar.y - 2 && vietNamTankWar.y < america4TankWar.y + 2 && vietNamTankWar.x > america4TankWar.x) return true;
      if (america1TankWar.y > america4TankWar.y - 2 && america1TankWar.y < america4TankWar.y + 2 && america1TankWar.x > america4TankWar.x) return false;
      if (america2TankWar.y > america4TankWar.y - 2 && america2TankWar.y < america4TankWar.y + 2 && america2TankWar.x > america4TankWar.x) return false;
      if (america3TankWar.y > america4TankWar.y - 2 && america3TankWar.y < america4TankWar.y + 2 && america3TankWar.x > america4TankWar.x) return false;
      return true;
    case 3: 
      if (vietNamTankWar.x > america4TankWar.x - 2 && vietNamTankWar.x < america4TankWar.x + 2 && vietNamTankWar.y > america4TankWar.y) return true;
      if (america1TankWar.x > america4TankWar.x - 2 && america1TankWar.x < america4TankWar.x + 2 && america1TankWar.y > america4TankWar.y) return false;
      if (america2TankWar.x > america4TankWar.x - 2 && america2TankWar.x < america4TankWar.x + 2 && america2TankWar.y > america4TankWar.y) return false;
      if (america3TankWar.x > america4TankWar.x - 2 && america3TankWar.x < america4TankWar.x + 2 && america3TankWar.y > america4TankWar.y) return false;
      return true;
    default:
      if (vietNamTankWar.y > america4TankWar.y - 2 && vietNamTankWar.y < america4TankWar.y + 2 && vietNamTankWar.x < america4TankWar.x) return true;
      if (america1TankWar.y > america4TankWar.y - 2 && america1TankWar.y < america4TankWar.y + 2 && america1TankWar.x < america4TankWar.x) return false;
      if (america2TankWar.y > america4TankWar.y - 2 && america2TankWar.y < america4TankWar.y + 2 && america2TankWar.x < america4TankWar.x) return false;
      if (america3TankWar.y > america4TankWar.y - 2 && america3TankWar.y < america4TankWar.y + 2 && america3TankWar.x < america4TankWar.x) return false;
      return true;
  }
}

bool hitAndRunAmerica4TankWar() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america4TankWar.y > 3) {
      stateAmerica4TankWar = 1;
      tft.fillRect(america4TankWar.x * 8, america4TankWar.y * 8, 24, 24, black);
      --america4TankWar.y;
      drawAmericaTankWar(america4TankWar.x, america4TankWar.y, 1);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica4TankWar(1) && shootVietNamTankWar(america4TankWar.x, america4TankWar.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america4TankWar.x < 24) {
      stateAmerica4TankWar = 2;
      tft.fillRect(america4TankWar.x * 8, america4TankWar.y * 8, 24, 24, black);
      ++america4TankWar.x;
      drawAmericaTankWar(america4TankWar.x, america4TankWar.y, 2);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica4TankWar(2) && shootVietNamTankWar(america4TankWar.x, america4TankWar.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america4TankWar.y < 24) {
      stateAmerica4TankWar = 3;
      tft.fillRect(america4TankWar.x * 8, america4TankWar.y * 8, 24, 24, black);
      ++america4TankWar.y;
      drawAmericaTankWar(america4TankWar.x, america4TankWar.y, 3);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica4TankWar(3) && shootVietNamTankWar(america4TankWar.x, america4TankWar.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america4TankWar.x > 3) {
      stateAmerica4TankWar = 4;
      tft.fillRect(america4TankWar.x * 8, america4TankWar.y * 8, 24, 24, black);
      --america4TankWar.x;
      drawAmericaTankWar(america4TankWar.x, america4TankWar.y, 4);
      hitAndRunVietNamTankWar();
      if (checkHitAndRunAmerica4TankWar(4) && shootVietNamTankWar(america4TankWar.x, america4TankWar.y, 4)) return true;
      return false;
    }
  }
}

int newGameTankWar() {
  drawSubScreen(bestTankWar, 0);

  // Init tank war
  vietNamTankWar.x = vietNamTankWar.y = 15;
  america1TankWar.x = 3; america1TankWar.y = 3;
  america2TankWar.x = 24; america2TankWar.y = 3;
  america3TankWar.x = 24; america3TankWar.y = 24;
  america4TankWar.x = 3; america4TankWar.y = 24;

  stateVietNamTankWar = 1;
  stateAmerica1TankWar = stateAmerica2TankWar = 3;
  stateAmerica3TankWar = stateAmerica4TankWar = 1;
  
  drawVietNamTankWar();
  drawAmericaTankWar(3, 3, 3);
  drawAmericaTankWar(24, 3, 3);
  drawAmericaTankWar(24, 24, 1);
  drawAmericaTankWar(3, 24, 1);

  // Tank war actives
  // Single thread so sequential activities
  while (1) {
    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica1TankWar()) {
      if (commonScore > bestTankWar) { // Update best tank war
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica2TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica3TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica4TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 
  }
}

int continueTankWar() {
  drawSubScreen(bestTankWar, 0);

  // Continue statement
  drawVietNamTankWar();
  drawAmericaTankWar(america1TankWar.x, america1TankWar.y, stateAmerica1TankWar);
  drawAmericaTankWar(america2TankWar.x, america2TankWar.y, stateAmerica2TankWar);
  drawAmericaTankWar(america3TankWar.x, america3TankWar.y, stateAmerica3TankWar);
  drawAmericaTankWar(america4TankWar.x, america4TankWar.y, stateAmerica4TankWar);
  
  while (1) {
    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica1TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica2TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica3TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(pau)) return 0;
    if (hitAndRunAmerica4TankWar()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(currentPlayer + addressBestTankWar, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 
  }
}