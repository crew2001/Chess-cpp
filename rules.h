//
// Created by cillian on 24/08/23.
//

#pragma once

#include <vector>
#include "board.h"

class Rules{
private:
    Board* m_board;

    int row, col;
//    array<array<int,8>,8> m_board_arr= Board::board;
    int m_pieceID;
    vector<vector<int>> availableMoves;
public:
    Rules(int pieceID,int in_row,int in_col);
    vector<vector<int>> GetMoves() const{
        return availableMoves;
    };
    void Setup(int pieceID,int row,int col);
    void DiagonalMoves();
    void LateralMoves();
    void PawnMoves();
    void KnightMoves();
    void BishopMoves();
    void RookMoves();
    void QueenMoves();
    void KingMoves();

};
