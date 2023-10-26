cmake_minimum_required(VERSION 3.26)
project(chess_game)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_game main.cpp)

add_subdirectory(game_engine)

#find_package(SFML 2.6 COMPONENTS graphics window REQUIRED)
#include_directories(${SFML_INCLUDE_DIRS} game_engine)
include_directories(game_engine)
target_link_libraries(chess_game game_engine)