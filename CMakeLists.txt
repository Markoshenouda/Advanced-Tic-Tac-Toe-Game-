cmake_minimum_required(VERSION 3.26)
project(New_folder)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(New_folder
        include/User.h
        include/UserManger.h
        include/game_constants.h 
        include/game_logic.h
        include/game_ui.h
        include/leaderboard.h
        include/ai_logic.h
        src/User.cpp
        src/UserManager.cpp
        src/ai_logic.cpp
        src/game_logic.cpp
        src/game_ui.cpp
        src/leaderboard.cpp
)
