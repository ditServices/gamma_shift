project(google_tests)
add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv4)

add_executable(tests_run sample_test.cpp)
target_link_libraries(tests_run PUBLIC PkgConfig::OPENCV gtest gtest_main)