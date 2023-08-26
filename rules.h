//
// Created by cillian on 24/08/23.
//

#pragma once
#include <algorithm>
#include <vector>
#include "board.h"

class Rules{
private:
    Board* m_board;

    int row, col;
//    array<array<int,8>,8> m_board_arr= Board::board;
    int m_pieceID;
    vector<pair<int,int>> availableMoves;
public:
    Rules(int pieceID,int in_row,int in_col);
    Rules(pair<int,int> newPiece,const array<array<int,8>,8>& currBoard);

    vector<pair<int,int>> GetMoves() const{
        return availableMoves;
    };
    void Setup(int pieceID,int row,int col,const array<array<int,8>,8>& moveBoard);
    void DiagonalMoves(const array<array<int,8>,8>& moveBoard);
    void LateralMoves(const array<array<int,8>,8>& moveBoard);
    void PawnMoves(const array<array<int,8>,8>& moveBoard);
    void KnightMoves(const array<array<int,8>,8>& moveBoard);
    void BishopMoves(const array<array<int,8>,8>& moveBoard);
    void RookMoves(const array<array<int,8>,8>& moveBoard);
    void QueenMoves(const array<array<int,8>,8>& moveBoard);
    void KingMoves(const array<array<int,8>,8>& moveBoard);
//    This king check will check if the king is in check from the most recent move
    static bool KingCheck(int npID,const array<array<int,8>,8>& currBoard);
//    void simMove(pair<int,int> start, pair<int,int> end, array<array<int,8>,8>& cpyBoard);

// CHECKS RETURN TRUE IF KING IS IN CHECK, FALSE IF SAFE
    static bool CheckDiagonal(const array<array<int,8>,8>& currBoard,int kingSign, pair<int,int> kingPos);
    static bool CheckLateral(const array<array<int,8>,8>& currBoard,int kingSign, pair<int,int> kingPos);
    static bool CheckPawns(const array<array<int,8>,8>& currBoard,int kingSign, pair<int,int> kingPos );
    static bool CheckKnights(const array<array<int,8>,8>& currBoard,int kingSign, pair<int,int> kingPos );
};
