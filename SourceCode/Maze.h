// Khai báo biến toàn cục lưu vị trí của con chuột
int xMouse, yMouse;

// Mảng lưu trạng thái của các ô trong mê cung 29x29 
char maze[841];

// Mảng lưu trạng thái của các hàng và cột trong mê cung
bool rowMaze[15][14], colMaze[15][14];

// Hàm lưu trạng thái của mê cung vào các mảng rowMaze và colMaze
void saveMaze() {
  // Duyệt qua từng ô trong mê cung
  for (int y = 0; y < 29; ++y) {
    for (int x = 0; x < 29; ++x) {
      // Nếu ô đó có tường
      if (maze[y + 29 * x]) {  
        // Nếu là hàng và cột lẻ, đánh dấu cột
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = true;
        // Nếu là hàng chẵn và cột lẻ, đánh dấu hàng
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = true;
      } else {
        // Nếu không có tường
        // Nếu là hàng và cột lẻ, gỡ đánh dấu cột
        if (y % 2 && !(x % 2)) colMaze[x / 2][y / 2] = false;
        // Nếu là hàng chẵn và cột lẻ, gỡ đánh dấu hàng
        else if (!(y % 2) && x % 2) rowMaze[y / 2][x / 2] = false;
      }
    }
  }
}

// Hàm tạo mê cung
void carveMaze(int x, int y) {
  int x1, y1, x2, y2, dx, dy;
  int dir = random(4), count = 0; // Chọn hướng ngẫu nhiên và biến đếm

  // Vòng lặp đảm bảo không quá 4 lần thử
  while (count < 4) {
    dx = dy = 0; // Khởi tạo delta x và delta y

    // Xác định delta x và delta y dựa trên hướng chọn
    if (dir == 0) dx = 1;
    else if (dir == 1) dy = 1;
    else if (dir == 2) dx = -1;
    else dy = -1;

    x1 = x + dx; // Tọa độ x của ô tiếp theo
    y1 = y + dy; // Tọa độ y của ô tiếp theo
    x2 = x1 + dx; // Tọa độ x của ô sau ô tiếp theo
    y2 = y1 + dy; // Tọa độ y của ô sau ô tiếp theo

    // Kiểm tra xem có thể "đào" hành lang từ ô hiện tại không
    if (x2 > 0 && x2 < 29 && y2 > 0 && y2 < 29 && maze[y1 * 29 + x1] == 1 && maze[y2 * 29 + x2] == 1) {
      // Nếu có thể "đào", gỡ bỏ tường của ô hiện tại và ô tiếp theo
      maze[y1 * 29 + x1] = maze[y2 * 29 + x2] = 0;
      x = x2; // Cập nhật tọa độ x mới
      y = y2; // Cập nhật tọa độ y mới
      dir = random(4); // Chọn hướng mới ngẫu nhiên
      count = 0; // Đặt lại biến đếm
    } else {
      // Nếu không thể "đào", chọn hướng tiếp theo và tăng biến đếm
      dir = (dir + 1) % 4;
      ++count;
    }
  }
}// Hàm tạo mê cung
void generateMaze() {
  // Khởi tạo mê cung với tất cả các ô đều có tường (giá trị 1)
  for (int x = 0; x < 841; ++x) 
    maze[x] = 1;
  
  // Mở một lối vào ở ô 30
  maze[30] = 0; 

  // Dùng hàm carveMaze để tạo mê cung
  for (int y = 1; y < 29; y += 2) {
    for (int x = 1; x < 29; x += 2) 
      carveMaze(x, y);
  }
  
  // Mở lối vào và ra ở ô 1 và 839
  maze[1] = maze[839] = 0;
}

// Hàm di chuyển con chuột trong mê cung
bool moveMouse() {
  // Kiểm tra các nút điều hướng và trạng thái của mê cung để xác định việc di chuyển con chuột

  // Nếu nhấn nút điều hướng lên và không có tường ở trên, di chuyển con chuột lên
  if (!digitalRead(top) && yMouse && !rowMaze[yMouse][xMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black); // Xóa con chuột ở vị trí hiện tại
    tft.fillRoundRect(xMouse * 16 + 10, --yMouse * 16 + 10, 12, 12, 3, green); // Vẽ con chuột mới ở vị trí mới
    return false;
  }  

  // Nếu nhấn nút điều hướng phải và không có tường bên phải, di chuyển con chuột sang phải
  if (!digitalRead(right) && !colMaze[xMouse + 1][yMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    // Nếu con chuột đang ở cột 13, nghĩa là đã đi đến đích, trả về true
    if (xMouse == 13) 
      return true;
    // Nếu không, di chuyển con chuột sang phải
    tft.fillRoundRect(++xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }

  // Nếu nhấn nút điều hướng xuống và không có tường ở dưới, di chuyển con chuột xuống
  if (!digitalRead(bottom) && yMouse != 14 && !rowMaze[yMouse + 1][xMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    tft.fillRoundRect(xMouse * 16 + 10, ++yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }

  // Nếu nhấn nút điều hướng trái và không có tường bên trái, di chuyển con chuột sang trái
  if (!digitalRead(left) && xMouse && !colMaze[xMouse][yMouse]) {
    tft.fillRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, black);
    tft.fillRoundRect(--xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);
    return false;
  }
  
  // Nếu không có bất kỳ hành động di chuyển nào được thực hiện, trả về false
  return false;
}
// Hàm bắt đầu trò chơi mới trong mê cung
int newGameMaze() {
  // Vẽ màn hình phụ với điểm số tốt nhất
  drawSubScreen(bestMaze, 0);

  // Vẽ tường xung quanh mê cung
  tft.fillRect(6, 22, 4, 208, red);
  tft.fillRect(230, 6, 4, 212, red);
  tft.fillRect(6, 6, 224, 4, red);
  tft.fillRect(6, 230, 228, 4, red);

  // Tạo và lưu trạng thái của mê cung
  generateMaze();
  saveMaze();

  // Vẽ các tường trong mê cung dựa trên trạng thái đã lưu
  for (int i = 1; i < 14; ++i) {
    int y = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (rowMaze[i][j]) tft.fillRect(j * 16 + 6, y + 6, 16, 4, red);
    }
  }

  for (int i = 1; i < 14; ++i) {
    int x = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (colMaze[i][j]) tft.fillRect(x + 6, j * 16 + 6, 4, 16, red);
    }
  }

  // Đặt con chuột vào vị trí ban đầu và vẽ nó trên màn hình
  xMouse = 0;
  yMouse = 0;
  tft.fillRoundRect(10, 10, 12, 12, 3, green);

  // Vòng lặp chính của trò chơi
  while (1) {
    // Lặp lại mỗi 10 lần, kiểm tra nút tạm dừng và di chuyển con chuột
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(enterPause)) return 0; // Nếu nhấn nút tạm dừng, thoát khỏi trò chơi
      if (moveMouse()) { // Di chuyển con chuột, nếu đạt đích, xử lý điểm số và lưu lại
        if (commonScore < bestMaze || !bestMaze) {
          bestMaze = commonScore;
          EEPROM.write(1, commonScore);
          EEPROM.commit();
        }
        return 1; // Trả về 1 để báo hiệu rằng đã kết thúc trò chơi thành công
      }
      delay(100); // Đợi 0.1 giây trước khi tiếp tục vòng lặp
    }
    increaseScore(); // Tăng điểm số nếu vẫn đang chơi
  }
}

// Hàm tiếp tục trò chơi trong mê cung
int continueMaze() {
  // Vẽ màn hình phụ với điểm số tốt nhất
  drawSubScreen(bestMaze, 0);

  // Vẽ tường xung quanh mê cung
  tft.fillRect(6, 22, 4, 208, red);
  tft.fillRect(230, 6, 4, 212, red);
  tft.fillRect(6, 6, 224, 4, red);
  tft.fillRect(6, 230, 228, 4, red);

  // Vẽ các tường trong mê cung dựa trên trạng thái đã lưu
  for (int i = 1; i < 14; ++i) {
    int y = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (rowMaze[i][j]) tft.fillRect(j * 16 + 6, y + 6, 16, 4, red);
    }
  }

  for (int i = 1; i < 14; ++i) {
    int x = i * 16;
    for (int j = 0; j < 14; ++j) {
      if (colMaze[i][j]) tft.fillRect(x + 6, j * 16 + 6, 4, 16, red);
    }
  }

  // Vẽ con chuột ở vị trí cuối cùng
  tft.fillRoundRect(xMouse * 16 + 10, yMouse * 16 + 10, 12, 12, 3, green);

  // Vòng lặp chính của trò chơi
  while (1) {
    // Lặp lại mỗi 10 lần, kiểm tra nút tạm dừng và di chuyển con chuột
    for (int i = 0; i < 10; ++i) {
      if (!digitalRead(enterPause)) return 0; // Nếu nhấn nút tạm dừng, thoát khỏi trò chơi
      if (moveMouse()) { // Di chuyển con chuột, nếu đạt đích, xử lý điểm số và lưu lại
        if (commonScore < bestMaze || !bestMaze) {
          bestMaze = commonScore;
          EEPROM.write(1, commonScore);
          EEPROM.commit();
        }
        return 1; // Trả về 1 để báo hiệu rằng đã kết thúc trò chơi thành công
      }
      delay(100); // Đợi 0.1 giây trước khi tiếp tục vòng lặp
    }
    increaseScore(); // Tăng điểm số nếu vẫn đang chơi
  }
}

