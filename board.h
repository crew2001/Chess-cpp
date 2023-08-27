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

    static void setBoard(array<array<int, 8>, 8> newBoard) { board = newBoard; };

    static void printBoard();

    static void makeMove(pair<int,int> start, pair<int,int> end);
    static pair<int,int> findKing(int kingSign);
    static void moveKing(int kingSign,pair<int,int> newPosition);
//    static inline array<array<int, 8>, 8> board = {
//            {{4, 0,0, 6,0,0,0, 4}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
//             {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
//             {-4, 0,0, -6,0,0,0, -4}}};
    static inline array<array<int, 8>, 8> board = {
            {{4, 2, 3, 6,5, 3, 2, 4}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
             {-4, -2, -3, -6, -5, -3, -2, -4}}};
    static void UndoMove(pair<int,int> newPosition, pair<int,int> oldPosition, int taken);
    
    // * ADDING LAST MOVE TRACKING

    static inline pair<int,int> lastMove;
    static inline int lastPiece;
    static inline bool blackCastle = true;
    static inline bool whiteCastle = true;
//    static vector<pair<int,int>> whitePieces = {{0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{1,0},{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7}};
//
//    static vector<pair<int,int>> blackPieces = {{7,0},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6},{7,7},{6,0},{6,1},{6,2},{6,3},{6,4},{6,5},{6,6},{6,7}};

};
