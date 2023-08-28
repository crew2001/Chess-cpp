//
// Created by cillian on 24/08/23.
//

#pragma once
#include <algorithm>
#include <vector>
#include "board.h"

class Rules
{
private:
    int row;
    int col;
    int m_pieceID;
    vector<pair<int, int>> availableMoves;

public:
    Rules(int pieceID, int in_row, int in_col);
    //    Rules(pair<int,int> newPiece,const array<array<int,8>,8>& currBoard);

    vector<pair<int, int>> GetMoves();

    void Setup(const array<array<int, 8>, 8> &moveBoard);
    void DiagonalMoves(const array<array<int, 8>, 8> &moveBoard);
    void LateralMoves(const array<array<int, 8>, 8> &moveBoard);
    void PawnMoves(const array<array<int, 8>, 8> &moveBoard);
    void KnightMoves(const array<array<int, 8>, 8> &moveBoard);
    void BishopMoves(const array<array<int, 8>, 8> &moveBoard);
    void RookMoves(const array<array<int, 8>, 8> &moveBoard);
    void QueenMoves(const array<array<int, 8>, 8> &moveBoard);
    void KingMoves(const array<array<int, 8>, 8> &moveBoard);

    void DiagonalMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void LateralMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void PawnMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void KnightMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void BishopMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void RookMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void QueenMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);
    void KingMoves(const array<array<int, 8>, 8> &moveBoard, vector<pair<int, int>> &moves);

    //    static vector<pair<int,int>> GetPieceMoves(pair<int,int> piecePos);

    static bool KingCheck(int npID, const array<array<int, 8>, 8> &currBoard);
    static bool KingCheck(int npID, const array<array<int, 8>, 8> &currBoard, pair<int, int> kingPosition);
    // CHECKS RETURN TRUE IF KING IS IN CHECK, FALSE IF SAFE
    static bool CheckDiagonal(const array<array<int, 8>, 8> &currBoard, int kingSign, pair<int, int> kingPos);
    static bool CheckLateral(const array<array<int, 8>, 8> &currBoard, int kingSign, pair<int, int> kingPos);
    static bool CheckPawns(const array<array<int, 8>, 8> &currBoard, int kingSign, pair<int, int> kingPos);
    static bool CheckKnights(const array<array<int, 8>, 8> &currBoard, int kingSign, pair<int, int> kingPos);

    //  CHECK IF THE MOVE MADE PUTS YOUR OWN KING IN CHECK
    static bool CanMove(pair<int, int> start, pair<int, int> end);
    static inline bool enPassente = false;
    //    CHECKMATE
    //    bool CheckMate(int sideSign);
};
