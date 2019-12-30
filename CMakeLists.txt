# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("TimeLogger")

if (CMAKE_BUILD_TYPE MATCHES Debug)
	add_definitions (-DDEBUG)
endif ()

# Include sub-projects.
include_directories("Common")
add_subdirectory ("TimeLogger")
add_subdirectory ("LogAnalyzer")