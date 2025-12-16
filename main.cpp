#include "serial_phoenix/include/serial.hpp"

int main() {
    auto serial = serial_phoenix::Serial();
    auto code   = serial.open("/dev/ttyACM0");
    return 0;
}