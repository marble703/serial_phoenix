# serial_phoenix

串口封装库，基于 `serial_driver` 。

## 要点
- 可以在 ament/ROS2 工作区中使用，也可以按普通 CMake 项目消费

## 编译
```
cmake -S . -B build
cmake --build build
```
可执行文件位于 `build/` 下的 `bin/serial_phoenix_main`，库位于 `lib/`。

## 头文件与用法
- 头文件安装布局为 `include/serial_phoenix/serial.hpp`。
- 在代码中直接包含：
```cpp
#include <serial_phoenix/serial.hpp>
```

## 依赖
- build-time: `ament_cmake`，或直接 `cmake` + `serial_driver`。
- run-time: `serial_driver` 库及其运行时依赖。