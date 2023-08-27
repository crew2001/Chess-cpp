//
// Created by cillian on 24/08/23.
//

#pragma once

#include <vector>
#include <array>
#include <iostream>
using namespace std;

class Board {
    static inline pair<int,int> whiteKing = {0,3};
    static inline pair<int,int> blackKing = {7,3};

public:
    Board() {};

    ~Board() {};

    array<array<int, 8>, 8> getBoard() { return board; };

    void setBoard(array<array<int, 8>, 8> newBoard) { board = newBoard; };

    static void printBoard();

    static void makeMove(pair<int,int> start, pair<int,int> end);
    static pair<int,int> findKing(int kingSign);
    static void makeMove(vector<int> start, vector<int> end);
    static void moveKing(int kingSign,pair<int,int> newPosition);
    static inline array<array<int, 8>, 8> board = {
            {{4, 2, 3, 6,5, 3, 2, 4}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
             {-4, -2, -3, -6, -5, -3, -2, -4}}};
    static void UndoMove(pair<int,int> newPosition, pair<int,int> oldPosition, int taken);
};
