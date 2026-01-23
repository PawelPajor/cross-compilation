cmake_minimum_required(VERSION 4.0)

project(hello_gui LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_gui WIN32 win-main.cpp)
set_target_properties(hello_gui PROPERTIES WIN32_EXECUTABLE TRUE)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(hello_gui PRIVATE SDL3::SDL3)
