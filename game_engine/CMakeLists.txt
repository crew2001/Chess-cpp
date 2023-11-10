add_library(game_engine
board.cpp eventmanager.cpp game.cpp pieces.cpp rules.cpp window.cpp)

find_package(SFML 2.6 COMPONENTS graphics window REQUIRED)
target_link_libraries(game_engine sfml-graphics sfml-window)

