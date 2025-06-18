cmake_minimum_required(VERSION 3.10)
project(AdvancedTicTacToe)
set(CMAKE_CXX_STANDARD 17)

# إضافة مسار ملفات الـ .h
include_directories(include)

# إنشاء الملف التنفيذي الرئيسي
add_executable(game
    main.cpp
    src/User.cpp
    src/UserManager.cpp
    src/game_logic.cpp
    src/game_ui.cpp
    src/ai_logic.cpp
    src/leaderboard.cpp
)

enable_testing()
add_subdirectory(googletest)

add_executable(test_user_manager
    tests/usermanager_test.cpp
    src/User.cpp
    src/UserManager.cpp
)

target_link_libraries(test_user_manager gtest gtest_main)
add_executable(test_history
    tests/history_test.cpp
)

target_link_libraries(test_history gtest gtest_main)

add_executable(test_leaderboard
    tests/leaderboard_test.cpp
    src/leaderboard.cpp
    src/game_logic.cpp
)

target_link_libraries(test_leaderboard gtest gtest_main)
add_executable(test_ai
    tests/ai_test.cpp
    src/ai_logic.cpp
)

target_link_libraries(test_ai gtest gtest_main)
