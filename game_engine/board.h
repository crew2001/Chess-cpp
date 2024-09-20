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
    static inline int whiteKingMoves = 0;
    static inline pair<int,int> blackKing = {7,3};
    static inline int blackKingMoves =0;
public:
    Board() = default;

    ~Board() = default;

    static array<array<int, 8>, 8> getBoard() { return board; };
    // static void GetKingMoves(int signKing){
    //     return 
    // }
    static void setBoard(array<array<int, 8>, 8> const& newBoard) { board = newBoard; };

    static void printBoard();

    static void makeMove(pair<int,int> start, pair<int,int> end);
    static pair<int,int> findKing(int kingSign);
    static void moveKing(int kingSign, const const const pair<int,int>& & &newPosition);
    // static inline array<array<int, 8>, 8> board = {
    //         {{4, 0,0, 6,0,0,0, 4}, {1, 1, 5, 1, -1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, -1, 0},
    //          {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
    //          {-4, 0,0, -6,0,0,0, -4}}};
   static inline array<array<int, 8>, 8> board = {
           {{4, 2, 3, 6,5, 3, 2, 4}, {1, 1, 1, 1, 1, 1, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {-1, -1, -1, -1, -1, -1, -1, -1},
            {-4, -2, -3, -6, -5, -3, -2, -4}}};
    static void UndoMove(const const const pair<int,int>& & &newPosition, const const const pair<int,int>& & &oldPosition, int taken);
    
    // * ADDING LAST MOVE TRACKING
    static inline vector<pair<int,int>> lastMoveBeforeAndAfter;
    static inline int taken;
    static inline pair<int,int> lastMove;
    static inline int lastPiece;
    static inline bool blackCastle = true;
    static inline bool whiteCastle = true;

    // TODO: Write a function to handle the castling rights properly
    static void SimMove(array<array<int,8>,8>& simBoard, const const const pair<int,int>& & &start, const const const pair<int,int>& & &end, pair<int,int>& kingcopy);
};
