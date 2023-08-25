#include "rules.h"
#include <vector>

Rules::Rules(int in_pieceID, int in_row, int in_col)
{
    this->Setup(in_pieceID, in_row, in_col);
//    this->GetMoves();
}

void Rules::Setup(int in_pieceID,int in_row,int in_col)
{
    row = in_row;
    col = in_col;
    m_pieceID = in_pieceID;
    switch (abs(m_pieceID))
    {
        case 1:
            return PawnMoves();
        case 2:
            return KnightMoves();
        case 3:
            return BishopMoves();
        case 4:
            return RookMoves();
        case 5:
            return QueenMoves();
        case 6:
            return KingMoves();
        default:
            return;
    }
}

void Rules::PawnMoves()
{
//    if white
    if (m_pieceID > 0)
    {
        if ((Board::board)[row+1][col]==0){
            availableMoves.push_back({row + 1, col});
            if (row==1 && (Board::board)[row+2][col]==0){
                availableMoves.push_back({row+2,col});
            }
        }
        for (int i=-1;i<2;i+=2){
            if ((Board::board)[row+i*i][col+i]*(Board::board)[row][col]<0){
                availableMoves.push_back({row+i*i,col+i});
            }
        }
    } //else black
    else
    {
        if ((Board::board)[row-1][col]==0){
            availableMoves.push_back({row - 1, col});
            if (row==6 && (Board::board)[row-2][col]==0){
                availableMoves.push_back({row-2,col});
            }
        }
        for (int i=-1;i<2;i+=2){
            if ((Board::board)[row-i*i][col-i]*(Board::board)[row][col]<0){
                availableMoves.push_back({row-i*i,col-i});
            }
        }
    }
}

void Rules::KnightMoves()
{
    vector<vector<int>> perms = {{1, 2}, {2, 1}, {-1, 2}, {2, -1}, {-2, 1}, {1, -2}, {-2, -1}, {-1, -2}};
    for (auto x : perms)
    {
        int newRow = row + x[0];
        int newCol = col + x[1];
        if ((newRow < 0 || newRow > 7) || (newCol < 0 || newCol > 7))
            continue;
        else
        {
            if ((Board::board)[newRow][newCol] == 0)
            {
                availableMoves.push_back({newRow, newCol});
            }
                // use fact that same colour will times to positive
            else if (((Board::board)[row][col] * (Board::board)[newRow][newCol] < 0))
            {
                availableMoves.push_back({newRow, newCol});
            }
            else
                continue;
        }
    }
}

void Rules::BishopMoves() { DiagonalMoves(); }

void Rules::RookMoves() { LateralMoves(); }

void Rules::QueenMoves()
{
    LateralMoves();
    DiagonalMoves();
}

void Rules::KingMoves()
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int newRow = row + i;
            int newCol = col + j;
            if ((newRow < 0 || newRow > 7) || (newCol < 0 || newCol > 7))
                continue;
            else
            {
                if ((Board::board)[newRow][newCol] == 0)
                {
                    availableMoves.push_back({newRow, newCol});
                }
                    // use fact that same colour will times to positive
                else if (((Board::board)[row][col] * (Board::board)[newRow][newCol] < 0))
                {
                    availableMoves.push_back({newRow, newCol});
                }
                else
                    continue;
            }
        }
    }
}

void Rules::DiagonalMoves() {
    for (int i=-1;i<2;i+=2){
        for (int j=-1;j<2;j+=2){
            int k = 1;
            while((row+k*i >= 0) && (row+k*i <8) && (col+k*j >= 0) && (col+k*j <8)){
                if ((Board::board)[row+i*k][col+j*k]==0){
                    availableMoves.push_back({row+i*k,col+j*k});
                    k++;
                } else if((Board::board)[row+i*k][col+j*k]*(Board::board)[row][col]<0){
                    availableMoves.push_back({row+i*k,col+j*k});
                    break;
                } else break;
            }
        }
    }
}

void Rules::LateralMoves() {
    for (int i=-1;i<2;i+=2){
        int k=1;
        while((col+k*i>=0) &&(col+k*i < 8)){
            if ((Board::board)[row][col+k*i]==0){
                availableMoves.push_back({row,col+k*i});
                k++;
            }
            else if ((Board::board)[row][col]*(Board::board)[row][col+k*i]<0){
                availableMoves.push_back({row,col+k*i});
                break;
            } else break;
        }
        while((row+k*i>=0) &&(row+k*i < 8)){
            if ((Board::board)[row+k*i][col]==0){
                availableMoves.push_back({row+k*i,col});
                k++;
            }
            else if ((Board::board)[row][col]*(Board::board)[row+k*i][col]<0){
                availableMoves.push_back({row+k*i,col});
                break;
            } else break;
        }
    }
}