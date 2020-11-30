# CMakeList.txt : CMake project for Day_03, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.10)

# Add source to this project's executable.
add_executable (Day_07 "Day_07.cpp" "Day_07.h")

# TODO: Add tests and install targets if needed.
target_compile_options(Day_07 PRIVATE /W4 /WX /permissive-)