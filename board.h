//
// Created by cillian on 24/08/23.
//

#pragma once

#include <vector>
#include <array>
#include <iostream>

using namespace std;

class Board {
public:
    Board() {};

    ~Board() {};

    array<array<int, 8>, 8> getBoard() { return board; };

    void setBoard(array<array<int, 8>, 8> newBoard) { board = newBoard; };

    void printBoard();

    void makeMove(vector<int> start, vector<int> end);

public:

private:
    array<array<int, 8>, 8> board = {
            {{4, 2, 3, 5, 6, 3, 2, 4}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
             {-4, -2, -3, -5, -6, -3, -2, -4}}};

};
