cmake_minimum_required(VERSION 3.1.0)
set (CMAKE_CXX_STANDARD 11)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(main Main.cpp)
target_link_libraries(main ${GTEST_LIBRARIES} pthread)
