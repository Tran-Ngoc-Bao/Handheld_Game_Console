// Khai báo các biến trạng thái cho Việt Nam và Hoa Kỳ
int stateVietNam, stateAmerica1, stateAmerica2, stateAmerica3, stateAmerica4;

// Khai báo cấu trúc dữ liệu để lưu trữ tọa độ của các đối tượng
coordinates vietNam, america1, america2, america3, america4;

// Hàm để vẽ biểu đồ trạng thái của Việt Nam trên màn hình
void drawVietNam() {
  // Tính toán tọa độ mới theo lưới pixel 8x8
  int x8 = vietNam.x * 8, y8 = vietNam.y * 8;
  
  // Xác định trạng thái của Việt Nam và vẽ biểu đồ tương ứng
  switch (stateVietNam) {
    // Trạng thái 1: Vẽ một hình chữ nhật lớn màu đỏ, một hình chữ nhật nhỏ màu vàng, và một hình chữ nhật nhỏ màu xanh lam trên
    case 1:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 6, y8 + 8, 12, 12, 3, yellow);
      tft.fillRect(x8 + 10, y8 + 2, 4, 6, indigo);
      break;
    // Trạng thái 2: Vẽ một hình chữ nhật lớn màu đỏ, một hình chữ nhật nhỏ màu vàng, và một hình chữ nhật nhỏ màu xanh lam phải
    case 2:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 4, y8 + 6, 12, 12, 3, yellow);
      tft.fillRect(x8 + 16, y8 + 10, 6, 4, indigo);
      break;
    // Trạng thái 3: Vẽ một hình chữ nhật lớn màu đỏ, một hình chữ nhật nhỏ màu vàng, và một hình chữ nhật nhỏ màu xanh lam dưới
    case 3:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 6, y8 + 4, 12, 12, 3, yellow);
      tft.fillRect(x8 + 10, y8 + 16, 4, 6, indigo);
      break;
    // Trạng thái mặc định: Vẽ một hình chữ nhật lớn màu đỏ, một hình chữ nhật nhỏ màu vàng, và một hình chữ nhật nhỏ màu xanh lam trái
    default:
      tft.fillRoundRect(x8, y8, 24, 24, 5, red);
      tft.fillRoundRect(x8 + 8, y8 + 6, 12, 12, 3, yellow);
      tft.fillRect(x8 + 2, y8 + 10, 6, 4, indigo);
  }
}
// Hàm để vẽ biểu đồ trạng thái của Hoa Kỳ trên màn hình
void drawAmerica(int x, int y, int state) {
  // Tính toán tọa độ mới theo lưới pixel 8x8
  int x8 = x * 8, y8 = y * 8;
  
  // Xác định trạng thái của Hoa Kỳ và vẽ biểu đồ tương ứng
  switch (state) {
    // Trạng thái 1: Vẽ một hình chữ nhật lớn màu indigo, một hình chữ nhật nhỏ màu đỏ, và một hình chữ nhật nhỏ màu trắng
    case 1:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 6, y8 + 8, 12, 12, 3, red);
      tft.fillRect(x8 + 10, y8 + 2, 4, 6, white);
      break;
    // Trạng thái 2: Vẽ một hình chữ nhật lớn màu indigo, một hình chữ nhật nhỏ màu đỏ, và một hình chữ nhật nhỏ màu trắng
    case 2:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 4, y8 + 6, 12, 12, 3, red);
      tft.fillRect(x8 + 16, y8 + 10, 6, 4, white);
      break;
    // Trạng thái 3: Vẽ một hình chữ nhật lớn màu indigo, một hình chữ nhật nhỏ màu đỏ, và một hình chữ nhật nhỏ màu trắng
    case 3:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 6, y8 + 4, 12, 12, 3, red);
      tft.fillRect(x8 + 10, y8 + 16, 4, 6, white);
      break;
    // Trạng thái mặc định: Vẽ một hình chữ nhật lớn màu indigo, một hình chữ nhật nhỏ màu đỏ, và một hình chữ nhật nhỏ màu trắng
    default:
      tft.fillRoundRect(x8, y8, 24, 24, 5, indigo);
      tft.fillRoundRect(x8 + 8, y8 + 6, 12, 12, 3, red);
      tft.fillRect(x8 + 2, y8 + 10, 6, 4, white);
  }
}

// Hàm để kiểm tra và "tiêu diệt" Hoa Kỳ tại một tọa độ cụ thể
bool killAmerica(int x, int y) {
  // Kiểm tra xem có đối tượng Hoa Kỳ nào ở tọa độ đã cho hay không và tiêu diệt nếu có
  if (america1.x <= x && x <= america1.x + 2 && america1.y <= y && y <= america1.y + 2) {
    // Xóa đối tượng Hoa Kỳ đã bị "tiêu diệt" bằng cách vẽ màu đen lên đó và tăng điểm số
    tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
    increaseScore();
    // Di chuyển đối tượng Hoa Kỳ đã tiêu diệt ra khỏi màn hình và vẽ lại với trạng thái mới
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
}// Hàm để bắn pháo từ Việt Nam đến Hoa Kỳ
void shootAmerica() {
  int x = vietNam.x, y = vietNam.y; // Lấy tọa độ của Việt Nam
  
  // Dựa vào trạng thái của Việt Nam, thực hiện hành động bắn pháo tương ứng
  switch (stateVietNam) {
    case 1: // Trạng thái 1: Bắn pháo lên trên
      for (int i = y - 1; i >= 0; --i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white); // Vẽ viên đạn di chuyển lên trên
        delay(10); // Dừng lại trong 10 miligiây
        if (killAmerica(x + 1, i)) break; // Nếu bắn trúng Hoa Kỳ, kết thúc vòng lặp
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black); // Nếu không, xóa viên đạn và tiếp tục di chuyển lên trên
        delay(10); // Dừng lại trong 10 miligiây
      }
      break;
    case 2: // Trạng thái 2: Bắn pháo sang phải
      for (int i = x + 4; i < 30; ++i) {
        // Tương tự như trạng thái 1, nhưng viên đạn di chuyển sang phải
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, y + 1)) break;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      break;
    case 3: // Trạng thái 3: Bắn pháo xuống dưới
      for (int i = y + 4; i < 30; ++i) {
        // Tương tự như trạng thái 1, nhưng viên đạn di chuyển xuống dưới
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(x + 1, i)) break;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      break;
    default: // Trạng thái mặc định: Bắn pháo sang trái
      for (int i = x - 1; i >= 0; --i) {
        // Tương tự như trạng thái 1, nhưng viên đạn di chuyển sang trái
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (killAmerica(i, y + 1)) break;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
  }
}

// Hàm để di chuyển Việt Nam và bắn pháo
void hitAndRunVietNam() {
  // Kiểm tra các nút nhấn để di chuyển Việt Nam và bắn pháo tương ứng
  if (!digitalRead(top) && vietNam.y) { // Nút nhấn "top" được nhấn và không ở biên trên cùng
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black); // Xóa Việt Nam khỏi vị trí hiện tại
    --vietNam.y; // Di chuyển Việt Nam lên trên
    if (stateVietNam != 1) { // Nếu trạng thái không phải là 1
      stateVietNam = 1; // Đặt trạng thái của Việt Nam là 1
      drawVietNam(); // Vẽ lại Việt Nam ở vị trí mới
      shootAmerica(); // Bắn pháo
    }else if (!digitalRead(right) && vietNam.x != 27) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);;
    ++vietNam.x;
    if (stateVietNam != 2) {
      stateVietNam = 2;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  } else if (!digitalRead(bottom) && vietNam.y != 27) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);;
    ++vietNam.y;
    if (stateVietNam != 3) {
      stateVietNam = 3;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  } else if (!digitalRead(left) && vietNam.x) {
    tft.fillRect(vietNam.x * 8, vietNam.y * 8, 24, 24, black);;
    --vietNam.x;
    if (stateVietNam != 4) {
      stateVietNam = 4;
      drawVietNam();
      shootAmerica();
    } else drawVietNam();
  }
}
// Hàm shootVietNam để bắn Việt Nam từ vị trí (x, y) theo hướng được chỉ định bởi state
bool shootVietNam(int x, int y, int state) {
  switch (state) {
    case 1:
      // Di chuyển pháo tới phía trên
      for (int i = y - 1; i >= 0; --i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white); // Vẽ pháo
        delay(10);
        // Kiểm tra xem Việt Nam có nằm trong vùng bắn không
        if (vietNam.x <= x + 1 && x <= vietNam.x + 1 && vietNam.y <= i && i <= vietNam.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black); // Xóa pháo
        delay(10);
      }
      return false; // Không bắn trúng
    case 2:
      // Di chuyển pháo tới phía phải
      for (int i = x + 4; i < 30; ++i) {
        tft.fillRoundRect(i * 8, y * 8 + 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= i && i <= vietNam.x + 2 && vietNam.y <= y + 1 && y <= vietNam.y + 1) return true;
        tft.fillRect(i * 8, y * 8 + 8, 8, 8, black);
        delay(10);
      }
      return false;
    case 3:
      // Di chuyển pháo tới phía dưới
      for (int i = y + 4; i < 30; ++i) {
        tft.fillRoundRect(x * 8 + 8, i * 8, 8, 8, 3, white);
        delay(10);
        if (vietNam.x <= x + 1 && x <= vietNam.x + 1 && vietNam.y <= i && i <= vietNam.y + 2) return true;
        tft.fillRect(x * 8 + 8, i * 8, 8, 8, black);
        delay(10);
      }
      return false;
    default:
      // Di chuyển pháo tới phía trái
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

// Hàm subHitAndRunVietNam thực hiện việc di chuyển Việt Nam và bắn pháo
void subHitAndRunVietNam() {
  for (int i = 0; i < 3; ++i) {
    hitAndRunVietNam(); // Di chuyển Việt Nam
    delay(100);
  }
}

// Hàm hitAndRunAmerica1 thực hiện di chuyển và bắn pháo của Hoa Kỳ 1
bool hitAndRunAmerica1() {
  while (1) {
    int rd = random(1, 5); // Lựa chọn ngẫu nhiên hướng di chuyển
    if (rd == 1 && america1.y > 5) { // Nếu hướng là phía trên và Hoa Kỳ 1 không ở gần biên trên cùng
      stateAmerica1 = 1;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black); // Xóa Hoa Kỳ 1 khỏi vị trí hiện tại
      --america1.y; // Di chuyển Hoa Kỳ 1 lên trên
      drawAmerica(america1.x, america1.y, 1); // Vẽ lại Hoa Kỳ 1 ở vị trí mới
      subHitAndRunVietNam(); // Di chuyển và bắn pháo của Việt Nam
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black); // Xóa Hoa Kỳ 1 khỏi vị trí hiện tại
      --america1.y; // Di chuyển Hoa Kỳ 1 lên trên
      drawAmerica(america1.x, america1.y, 1); // Vẽ lại Hoa Kỳ 1 ở vị trí mới
      subHitAndRunVietNam(); // Di chuyển và bắn pháo của Việt Nam
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black); // Xóa Hoa Kỳ 1 khỏi vị trí hiện tại
      --america1.y; // Di chuyển Hoa Kỳ 1 lên trên
      drawAmerica(america1.x, america1.y, 1); // Vẽ lại Hoa Kỳ 1 ở vị trí mới
      subHitAndRunVietNam(); // Di chuyển và bắn pháo của Việt Nam
      if (shootVietNam(america1.x, america1.y, 1)) return true; // Nếu bắn trúng Việt Nam, trả về true
      return false; // Ngược lại, trả về false
    }
    // Tương tự cho các hướng di chuyển còn lại
    if (rd == 2 && america1.x < 22) {
      stateAmerica1 = 2;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.x;
      drawAmerica(america1.x, america1.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.x;
      drawAmerica(america1.x, america1.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.x;
      drawAmerica(america1.x, america1.y, 2);
      subHitAndRunVietNam();
      if (shootVietNam(america1.x, america1.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america1.y < 22) {
      stateAmerica1 = 3;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.y;
      drawAmerica(america1.x, america1.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.y;
      drawAmerica(america1.x, america1.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      ++america1.y;
      drawAmerica(america1.x, america1.y, 3);
      subHitAndRunVietNam();
      if (shootVietNam(america1.x, america1.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america1.x > 5) {
      stateAmerica1 = 4;
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      --america1.x;
      drawAmerica(america1.x, america1.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      --america1.x;
      drawAmerica(america1.x, america1.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america1.x * 8, america1.y * 8, 24, 24, black);
      --america1.x;
      drawAmerica(america1.x, america1.y, 4);
      subHitAndRunVietNam();
      if (shootVietNam(america1.x, america1.y, 4)) return true;
      return false;
    }
  }
}
bool hitAndRunAmerica2() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america2.y > 5) {
      stateAmerica2 = 1;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.y;
      drawAmerica(america2.x, america2.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.y;
      drawAmerica(america2.x, america2.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.y;
      drawAmerica(america2.x, america2.y, 1);
      subHitAndRunVietNam();
      if (shootVietNam(america2.x, america2.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america2.x < 22) {
      stateAmerica2 = 2;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.x;
      drawAmerica(america2.x, america2.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.x;
      drawAmerica(america2.x, america2.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.x;
      drawAmerica(america2.x, america2.y, 2);
      subHitAndRunVietNam();
      if (shootVietNam(america2.x, america2.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america2.y < 22) {
      stateAmerica2 = 3;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.y;
      drawAmerica(america2.x, america2.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.y;
      drawAmerica(america2.x, america2.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      ++america2.y;
      drawAmerica(america2.x, america2.y, 3);
      subHitAndRunVietNam();
      if (shootVietNam(america2.x, america2.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america2.x > 5) {
      stateAmerica2 = 4;
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.x;
      drawAmerica(america2.x, america2.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.x;
      drawAmerica(america2.x, america2.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america2.x * 8, america2.y * 8, 24, 24, black);
      --america2.x;
      drawAmerica(america2.x, america2.y, 4);
      subHitAndRunVietNam();
      if (shootVietNam(america2.x, america1.y, 4)) return true;
      return false;
    }
  }
}

bool hitAndRunAmerica3() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america3.y > 5) {
      stateAmerica3 = 1;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.y;
      drawAmerica(america3.x, america3.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.y;
      drawAmerica(america3.x, america3.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.y;
      drawAmerica(america3.x, america3.y, 1);
      subHitAndRunVietNam();
      if (shootVietNam(america3.x, america3.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america3.x < 22) {
      stateAmerica3 = 2;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.x;
      drawAmerica(america3.x, america3.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.x;
      drawAmerica(america3.x, america3.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.x;
      drawAmerica(america3.x, america3.y, 2);
      subHitAndRunVietNam();
      if (shootVietNam(america3.x, america3.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america3.y < 22) {
      stateAmerica3 = 3;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.y;
      drawAmerica(america3.x, america3.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.y;
      drawAmerica(america3.x, america3.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      ++america3.y;
      drawAmerica(america3.x, america3.y, 3);
      subHitAndRunVietNam();
      if (shootVietNam(america3.x, america3.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america3.x > 5) {
      stateAmerica3 = 4;
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.x;
      drawAmerica(america3.x, america3.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.x;
      drawAmerica(america3.x, america3.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america3.x * 8, america3.y * 8, 24, 24, black);
      --america3.x;
      drawAmerica(america3.x, america3.y, 4);
      subHitAndRunVietNam();
      if (shootVietNam(america3.x, america3.y, 4)) return true;
      return false;
    }
  }
}

bool hitAndRunAmerica4() {
  while (1) {
    int rd = random(1, 5);
    if (rd == 1 && america4.y > 5) {
      stateAmerica4 = 1;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.y;
      drawAmerica(america4.x, america4.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.y;
      drawAmerica(america4.x, america4.y, 1);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.y;
      drawAmerica(america4.x, america4.y, 1);
      subHitAndRunVietNam();
      if (shootVietNam(america4.x, america4.y, 1)) return true;
      return false;
    }
    if (rd == 2 && america4.x < 22) {
      stateAmerica4 = 2;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.x;
      drawAmerica(america4.x, america4.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.x;
      drawAmerica(america4.x, america4.y, 2);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.x;
      drawAmerica(america4.x, america4.y, 2);
      subHitAndRunVietNam();
      if (shootVietNam(america4.x, america4.y, 2)) return true;
      return false;
    }
    if (rd == 3 && america4.y < 22) {
      stateAmerica4 = 3;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.y;
      drawAmerica(america4.x, america4.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.y;
      drawAmerica(america4.x, america4.y, 3);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      ++america4.y;
      drawAmerica(america4.x, america4.y, 3);
      subHitAndRunVietNam();
      if (shootVietNam(america4.x, america4.y, 3)) return true;
      return false;
    }
    if (rd == 4 && america4.x > 5) {
      stateAmerica4 = 4;
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.x;
      drawAmerica(america4.x, america4.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.x;
      drawAmerica(america4.x, america4.y, 4);
      subHitAndRunVietNam();
      tft.fillRect(america4.x * 8, america4.y * 8, 24, 24, black);
      --america4.x;
      drawAmerica(america4.x, america4.y, 4);
      subHitAndRunVietNam();
      if (shootVietNam(america4.x, america4.y, 4)) return true;
      return false;
    }
  }
}
// Hàm này bắt đầu một trò chơi mới "Tank War"
int newGameTankWar() {
  // Vẽ màn hình con với điểm số tốt nhất
  drawSubScreen(bestTankWar, 0);

  // Thiết lập vị trí ban đầu của các quân địch và đối thủ
  vietNam.x = vietNam.y = 15;
  america1.x = 3; america1.y = 3;
  america2.x = 24; america2.y = 3;
  america3.x = 24; america3.y = 24;
  america4.x = 3; america4.y = 24;

  // Thiết lập trạng thái ban đầu của các đối thủ và quân địch
  stateVietNam = 1;// hướng lên trên 
  stateAmerica1 = stateAmerica2 = 3;// hướng xuống dưới

  stateAmerica3 = stateAmerica4 = 1;
  
  // Vẽ quân mình và đối thủ
  drawVietNam();
  drawAmerica(3, 3, 3);
  drawAmerica(24, 3, 3);
  drawAmerica(24, 24, 1);
  drawAmerica(3, 24, 1);

  // Vòng lặp chính của trò chơi
  while (1) {
    // Nếu người chơi nhấn nút pause, trò chơi dừng lại
    if (!digitalRead(enterPause)) return 0;
    // Nếu quân địch 1 bị hạ gục, kiểm tra và cập nhật điểm số tốt nhất
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 
    // Tương tự kiểm tra các quân địch khác
    // (Các đoạn mã tương tự cho America2, America3, America4
   if (!digitalRead(enterPause)) return 0;
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
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

// Hàm này tiếp tục trò chơi "Tank War" đã bắt đầu
int continueTankWar() {
  // Vẽ màn hình con với điểm số tốt nhất
  drawSubScreen(bestTankWar, 0);

  // Vẽ quân địch và đối thủ tại vị trí hiện tại
  drawVietNam();
  drawAmerica(america1.x, america1.y, stateAmerica1);
  drawAmerica(america2.x, america2.y, stateAmerica2);
  drawAmerica(america3.x, america3.y, stateAmerica3);
  drawAmerica(america4.x, america4.y, stateAmerica4);
  
  // Vòng lặp chính của trò chơi
  while (1) {
    // Nếu người chơi nhấn nút pause, trò chơi dừng lại
    if (!digitalRead(enterPause)) return 0;
    // Kiểm tra và cập nhật điểm số tốt nhất khi một quân địch bị hạ gục
    if (hitAndRunAmerica1()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 
    // Tương tự kiểm tra các quân địch khác
    // (Các đoạn mã tương tự cho America2, America3, America4)
     if (!digitalRead(enterPause)) return 0;
    if (hitAndRunAmerica2()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
    if (hitAndRunAmerica3()) {
      if (commonScore > bestTankWar) {
        bestTankWar = commonScore;
        EEPROM.write(4, commonScore);
        EEPROM.commit();
      }
      return 1;
    } 

    if (!digitalRead(enterPause)) return 0;
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






