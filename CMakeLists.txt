cmake_minimum_required(VERSION 3.16)
project(CourierEdit VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(CourierEdit)

target_link_libraries(CourierEdit PRIVATE Qt6::Core)

add_subdirectory(src)