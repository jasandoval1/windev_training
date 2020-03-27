# CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(catch2-unit-test-demo CXX)

option(ENABLE_TESTING "Enable unit tests" OFF)

add_executable(demo
    "src/main.cpp"
    "src/utils.cpp")

if(ENABLE_TESTING)
    enable_testing()
    message("Building tests...")
    add_subdirectory(deps/catch2)
    add_subdirectory(test)
endif()