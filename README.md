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

## 示例程序：终端写串口，串口读入文件
生成的示例可执行文件为 `serial_terminal_bridge`，支持从终端输入写入串口，同时将串口读取的数据直接追加到文件

### 运行示例
```
# 构建
cmake -S . -B build
cmake --build build -j

# 运行（根据实际串口设备修改端口）
./build/serial_terminal_bridge -p /dev/ttyUSB0 -b 115200 -o ./build/serial_dump.bin -s 256
```

参数说明：
- `-p/--port`: 串口设备路径，默认 `/dev/ttyACM0`
- `-b/--baud`: 波特率，默认 `115200`
- `-o/--out`: 输出文件路径，默认 `serial_out.bin`
- `-s/--size`: 单次读取的字节数，默认 `256`

在终端中输入文本并回车即可发送到串口。程序会持续从串口读取固定大小的块并直接写入到指定文件。使用 `Ctrl+C` 可安全退出

## 头文件与用法
- 头文件安装布局为 `include/serial_phoenix/serial.hpp`。
- 在代码中直接包含：
```cpp
#include <serial_phoenix/serial.hpp>
```

## 依赖
- build-time: `ament_cmake`，或直接 `cmake` + `serial_driver`。
- run-time: `serial_driver` 库及其运行时依赖。