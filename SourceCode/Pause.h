int pause() {
  // Xoá màn hình hiện tại và thiết lập kích thước chữ và màu sắc cho chữ
  tft.fillScreen(black);
  tft.setTextSize(3);
  tft.setTextColor(white);

  // Khởi tạo các biến để theo dõi trạng thái của các nút nhấn
  bool ctn = true;    // Biến ctn là true nếu nút "CONTINUE" được chọn
  bool newGame = false; // Biến newGame là true nếu nút "NEW GAME" được chọn

  // Hiển thị nút "CONTINUE" là nút được chọn ban đầu, và hai nút còn lại không được chọn
  posContinue();
  negNewGame();
  negOtherGame();

  // Vòng lặp vô hạn để xử lý việc chọn tùy chọn từ người chơi
  while (1) {
    if (ctn) {
      // Nếu nút "CONTINUE" được chọn
      if (!digitalRead(enterPause)) return 0; // Nếu nhấn nút Enter, tiếp tục trò chơi
      if (!digitalRead(top)) {
        negContinue();  // Bỏ chọn nút "CONTINUE"
        posOtherGame(); // Chọn nút "OTHER GAME"
        ctn = false;    // Cập nhật biến ctn để đánh dấu đã thay đổi tùy chọn
      } else if (!digitalRead(bottom)) {
        negContinue();  // Bỏ chọn nút "CONTINUE"
        posNewGame();   // Chọn nút "NEW GAME"
        ctn = false;    // Cập nhật biến ctn để đánh dấu đã thay đổi tùy chọn
        newGame = true; // Cập nhật biến newGame để đánh dấu lựa chọn "NEW GAME"
      } 
    } else if (newGame) {
      // Nếu lựa chọn là "NEW GAME"
      if (!digitalRead(enterPause)) return 1; // Nếu nhấn nút Enter, bắt đầu trò chơi mới
      if (!digitalRead(top)) {
        negNewGame();   // Bỏ chọn nút "NEW GAME"
        posContinue();  // Chọn nút "CONTINUE"
        newGame = false; // Cập nhật biến newGame để đánh dấu đã thay đổi tùy chọn
        ctn = true;     // Cập nhật biến ctn để đánh dấu lựa chọn "CONTINUE"
      } else if (!digitalRead(bottom)) {
        negNewGame();   // Bỏ chọn nút "NEW GAME"
        posOtherGame(); // Chọn nút "OTHER GAME"
        newGame = false; // Cập nhật biến newGame để đánh dấu đã thay đổi tùy chọn
      } 
    } else {
      // Nếu lựa chọn là "OTHER GAME"
      if (!digitalRead(enterPause)) return 2; // Nếu nhấn nút Enter, quay lại màn hình chọn trò chơi
      if (!digitalRead(top)) {
        negOtherGame(); // Bỏ chọn nút "OTHER GAME"
        posNewGame();   // Chọn nút "NEW GAME"
        newGame = true; // Cập nhật biến newGame để đánh dấu lựa chọn "NEW GAME"
      } else if (!digitalRead(bottom)) {
        negOtherGame(); // Bỏ chọn nút "OTHER GAME"
        posContinue();  // Chọn nút "CONTINUE"
        ctn = true;     // Cập nhật biến ctn để đánh dấu lựa chọn "CONTINUE"
      } 
    }
  }
}
