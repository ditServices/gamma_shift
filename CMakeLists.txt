cmake_minimum_required(VERSION 3.22)
project(gamma_shift)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv4)
add_subdirectory(lib/cargs)

add_executable(gamma_shift main.cpp gamma_correct.cpp gamma_correct.h image_handler.cpp image_handler.h)
target_link_libraries(gamma_shift PUBLIC PkgConfig::OPENCV cargs)
add_subdirectory(tests)
