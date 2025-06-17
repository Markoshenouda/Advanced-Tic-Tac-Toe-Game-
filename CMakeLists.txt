# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(TicTacToe)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set include directory for header files
include_directories(include)

# Collect all .cpp source files inside src/
file(GLOB SOURCES "src/*.cpp")

# Add the executable using the collected source files
add_executable(TicTacToe ${SOURCES})

# (Optional) Show all warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(TicTacToe PRIVATE -Wall -Wextra -pedantic)
elseif (MSVC)
    target_compile_options(TicTacToe PRIVATE /W4)
endif()
