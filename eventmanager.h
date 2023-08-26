//
// Created by cillian on 24/08/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <array>
#include "board.h"
#include "rules.h"
//#include "game.h"

using namespace std;

class EventManager {
private:
    int row;
    int col;
    int PieceChosen;
    Board m_board;

    vector<pair<int, int>> m_available;
    array<array<int, 8>, 8> arrboard = Board::board;

public:
    EventManager() {};

    bool CorrectPiece;

    ~EventManager() = default;

    void HandleEvent(sf::Event &event,int turn);

    void HandleEvent(sf::Event &event, vector<pair<int, int>> &gameMoves, const pair<int, int> &currentPiece);

    bool IsCorrect(){
        return CorrectPiece;
    };

    void GetMoves();

    vector<pair<int, int>> ReturnMoves() { return m_available; };

    pair<int, int> ReturnClickPos() { return {row, col}; }

    void printBoard();
};

