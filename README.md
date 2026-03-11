# PX4-Mavlink-Alert-Project
A custom PX4 module implementing real-time MAVLink status alerts and UORB subscription for drone safety monitoring.

## 功能說明
1.透過UORB訂閱vehicle_status, 捕捉Arming狀態
2.當馬達啟動,發送`MAV_SEVERITY_CRITICAL`給QGC
3. 使用邊緣觸發邏輯,節省效能

## 檔案清單
* `HelloMavlink.cpp / .hpp`: 模組核心 C++ 邏輯。
* `CMakeLists.txt`: PX4 模組編譯設定。
* `Kconfig`: 模組參數與定義檔。

## 如何編譯
1. 將檔案複製到 PX4 目錄：`src/modules/hello_mavlink/`
2. 執行編譯：`make px4_sitl jmavsim`
3. 啟動模組：在 Console 輸入 `hello_mavlink start`
