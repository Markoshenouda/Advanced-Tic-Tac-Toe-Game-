# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(TicTacToe)

# Use modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files from 'include/' directory
include_directories(include)

# Collect all .cpp files in the src/ directory
file(GLOB SOURCES "src/*.cpp")

# Define the main executable
add_executable(TicTacToe ${SOURCES})

# Optional: Enable verbose compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(TicTacToe PRIVATE -Wall -Wextra -pedantic)
elseif (MSVC)
    target_compile_options(TicTacToe PRIVATE /W4)
endif()

# Optional: For future testing support
# enable_testing()
# add_test(NAME TicTacToeTest COMMAND TicTacToe)
