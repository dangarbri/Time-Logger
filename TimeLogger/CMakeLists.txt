# CMakeList.txt : CMake project for TimeLogger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions (-DDEBUG)
endif ()

add_executable (TimeLogger "TimeLogger.cpp" "TimeLogger.h" "Log.cpp" "Log.h")

# TODO: Add tests and install targets if needed.
