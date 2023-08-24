cmake_minimum_required(VERSION 3.26)
project(chess_clion)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess_clion main.cpp
        board.cpp
        game.cpp
        player.cpp
        pieces.cpp
        eventmanager.cpp)

find_package(SFML 2.6 COMPONENTS graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(chess_clion sfml-graphics sfml-window )