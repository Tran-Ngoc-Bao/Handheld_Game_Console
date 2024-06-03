// Pointer position
// Target 100 is DEL button. Target 1000 is DONE button. Other is alphabet character
int target = 0; 

// Draw alphabet character or _ character
void drawCharacter(bool b, int x, int y, int c) {
  if (b) tft.fillRoundRect(x, 100 + y, 24, 24, 5, red);
  else tft.fillRoundRect(x, 100 + y, 24, 24, 5, indigo);
  tft.setCursor(x + 7, 104 + y);
  tft.println((char) (65 + c));
}

// DEL button
void drawDelete(bool b) {
  if (b) tft.fillRoundRect(260, 140, 56, 24, 5, red);
  else tft.fillRoundRect(260, 140, 56, 24, 5, green);
  tft.setCursor(272, 144);
  tft.println("DEL");
}

// DONE button
void drawDone(bool b) {
  if (b) tft.fillRoundRect(260, 180, 56, 24, 5, red);
  else tft.fillRoundRect(260, 180, 56, 24, 5, green);
  tft.setCursor(266, 184);
  tft.println("DONE");
}

// Move top, right, bottom, left pointer
// Process at special position
void moveTarget() {
  if (!digitalRead(top) && target > 9) {
    if (target == 100) {
      target = 8;
      drawDelete(false);
      drawCharacter(true, 260, 0, 8);
    } else if (target == 1000) {
      target = 100;
      drawDone(false);
      drawDelete(true);
    } else if (target < 18) {
      drawCharacter(false, (target - 10) * 32 + 4, 40, target);
      target -= 10;
      drawCharacter(true, target * 32 + 4, 0, target);
    } else {
      drawCharacter(false, (target - 18) * 32 + 4, 80, target);
      target -= 8;
      drawCharacter(true, (target - 10) * 32 + 4, 40, target);
    }
  } else if (!digitalRead(right) && target != 9 && target != 100 && target != 1000) {
    if (target == 17) {
      target = 100;
      drawCharacter(false, 228, 40, 17);
      drawDelete(true);
    } else if (target == 25) {
      target = 1000;
      drawCharacter(false, 228, 80, 25);
      drawDone(true);
    } else if (target < 9) {
      drawCharacter(false, target * 32 + 4, 0, target);
      ++target;
      drawCharacter(true, target * 32 + 4, 0, target);
    } else if (target < 18) {
      drawCharacter(false, (target - 10) * 32 + 4, 40, target);
      ++target;
      drawCharacter(true, (target - 10) * 32 + 4, 40, target);
    } else {
      drawCharacter(false, (target - 18) * 32 + 4, 80, target);
      ++target;
      drawCharacter(true, (target - 18) * 32 + 4, 80, target);
    }
  } else if (!digitalRead(bottom) && (target < 18 || target == 100)) {
    if (target == 8 || target == 9) {
      drawCharacter(false, target * 32 + 4, 0, target);
      target = 100;
      drawDelete(true);
    } else if (target == 100) {
      target = 1000;
      drawDelete(false);
      drawDone(true);
    } else if (target < 8) {
      drawCharacter(false, target * 32 + 4, 0, target);
      target += 10;
      drawCharacter(true, (target - 10) * 32 + 4, 40, target);
    } else {
      drawCharacter(false, (target - 10) * 32 + 4, 40, target);
      target += 8;
      drawCharacter(true, (target - 18) * 32 + 4, 80, target);
    }
  } else if (!digitalRead(left) && target != 0 && target != 10 && target != 18) {
    if (target == 100) {
      target = 17;
      drawDelete(false);
      drawCharacter(true, 228, 40, 17);
    } else if (target == 1000) {
      target = 25;
      drawDone(false);
      drawCharacter(true, 228, 80, 25);
    } else if (target < 10) {
      drawCharacter(false, target * 32 + 4, 0, target);
      --target;
      drawCharacter(true, target * 32 + 4, 0, target);
    } else if (target < 18) {
      drawCharacter(false, (target - 10) * 32 + 4, 40, target);
      --target;
      drawCharacter(true, (target - 10) * 32 + 4, 40, target);
    } else {
      drawCharacter(false, (target - 18) * 32 + 4, 80, target);
      --target;
      drawCharacter(true, (target - 18) * 32 + 4, 80, target);
    }
  }
}

void enterPlayer() {
  int cntTmp = 0;
  int resultTmp[8] = { 0 };

  tft.fillScreen(black);

  tft.setTextSize(2);
  tft.setTextColor(white);

  tft.fillRoundRect(64, 40, 192, 24, 5, indigo);
  drawCharacter(false, 68, -60, 30);

  drawCharacter(true, 4, 0, 0);

  // Draw board
  for (int i = 1; i < 10; ++i) drawCharacter(false, i * 32 + 4, 0, i);
  for (int i = 0; i < 8; ++i) drawCharacter(false, i * 32 + 4, 40, i + 10);
  for (int i = 0; i < 8; ++i) drawCharacter(false, i * 32 + 4, 80, i + 18);

  drawDelete(false);
  drawDone(false);

  while (1) {
    moveTarget();
    // Process event when press enter button
    if (!digitalRead(enter)) {
      if (target == 100) {
        if (cntTmp) {
          if (cntTmp != 8) tft.fillRoundRect(64 + cntTmp * 24, 40, 24, 24, 5, indigo);
          resultTmp[--cntTmp] = 0;
          drawCharacter(false, 64 + cntTmp * 24, -60, 30);
        }
      } else if (target == 1000) {
        if (cntTmp) {
          if (countPlayer != 8) {
            for (int i = 0; i < cntTmp; ++i) EEPROM.write(countPlayer * 25 + i, resultTmp[i]);
            if (cntTmp != 8) EEPROM.write(countPlayer * 25 + cntTmp, 111);
            EEPROM.write(200, ++countPlayer);
          } else {
            for (int i = 0; i < cntTmp; ++i) EEPROM.write(i, resultTmp[i]);
            if (cntTmp != 8) EEPROM.write(cntTmp, 111);
            for (int i = 8; i < 25; ++i) EEPROM.write(i, 0);
          } 
          EEPROM.commit();
          return;
        }
      } else if (cntTmp != 8) {
        drawCharacter(false, 64 + cntTmp * 24, -60, target);
        resultTmp[cntTmp++] = target;
        if (cntTmp != 8) drawCharacter(false, 64 + cntTmp * 24, -60, 30);
      }
    }
    delay(100);
  }
}