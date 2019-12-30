# CMakeList.txt : CMake project for TimeLogger, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

add_executable (LogAnalyzer "main.cpp" 
                            "TimeUtils.cpp"
                            "TimeUtils.h"
                            "../Common/constants.cpp")

# TODO: Add tests and install targets if needed.
