//
// Created by cillian on 24/08/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <array>
#include "board.h"
//#include "game.h"

using namespace std;

class EventManager {
private:
    int row,col,PieceChosen;
    Board m_board;

public:
    EventManager(){};

    ~EventManager() = default;
//    void HandleEvent(sf::Event& event,Board& board);
void HandleEvent(sf::Event& event);
};

