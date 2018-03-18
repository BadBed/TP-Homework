cmake_minimum_required(VERSION 3.1.0)
set (CMAKE_CXX_STANDARD 11)

if(WITH_TEST)
	find_package(GTest REQUIRED)
	include_directories(${GTEST_INCLUDE_DIRS})
	include_directories(.)

	add_executable(main Main.cpp Test.cpp)
	target_link_libraries(main ${GTEST_LIBRARIES} pthread)
else()
	include_directories(.)
	add_executable(main Main.cpp NoTest.cpp)
endif()