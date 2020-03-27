# test/CMakeLists.txt

# pull in catch_discover_tests()
include(${CMAKE_SOURCE_DIR}/deps/catch2/contrib/Catch.cmake)

# build the dummy Catch2 entry point as static lib
add_library(catch-main STATIC catch_main.cpp)
target_link_libraries(catch-main PUBLIC Catch2::Catch2)

# build our actual test suite
add_executable(tests tests.cpp ${CMAKE_SOURCE_DIR}/src/utils.cpp)
target_link_libraries(tests PRIVATE catch-main)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

# register our Catch2 tests with CTest
catch_discover_tests(tests)