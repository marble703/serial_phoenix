cmake_minimum_required(VERSION 3.22)
project(serial_phoenix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)
find_package(serial_driver REQUIRED)

# Library
add_library(serial_phoenix_core serial_phoenix/src/serial.cpp)
target_include_directories(serial_phoenix_core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/serial_phoenix/include>
  $<INSTALL_INTERFACE:include>
)
ament_target_dependencies(serial_phoenix_core serial_driver)

# Example executable
add_executable(serial_phoenix_main main.cpp)
target_link_libraries(serial_phoenix_main serial_phoenix_core)

# Terminal-serial bridge example
add_executable(serial_terminal_bridge serial_phoenix/example/main.cpp)
target_link_libraries(serial_terminal_bridge serial_phoenix_core)

# Install
install(TARGETS serial_phoenix_core serial_phoenix_main serial_terminal_bridge
  EXPORT serial_phoenixTargets
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install(DIRECTORY serial_phoenix/include/ DESTINATION include)

ament_export_targets(serial_phoenixTargets HAS_LIBRARY_TARGET)
ament_export_dependencies(serial_driver)
ament_package()
