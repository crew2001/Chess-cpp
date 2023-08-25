#include "rules.h"
#include <vector>

Rules::Rules(int in_pieceID, int in_row, int in_col)
{
    this->Setup(in_pieceID, in_row, in_col,Board::board);
//    this->GetMoves();
}

Rules::Rules(pair<int,int> newPiece, const array<array<int,8>,8>& currBoard){
    this->Setup(currBoard[newPiece.first][newPiece.second],newPiece.first,newPiece.second,currBoard);
}

void Rules::Setup(int in_pieceID,int in_row,int in_col, const array<array<int,8>,8>& moveBoard)
{
    row = in_row;
    col = in_col;
    m_pieceID = in_pieceID;
    switch (abs(m_pieceID))
    {
        case 1:
            return PawnMoves(moveBoard);
        case 2:
            return KnightMoves(moveBoard);
        case 3:
            return BishopMoves(moveBoard);
        case 4:
            return RookMoves(moveBoard);
        case 5:
            return QueenMoves(moveBoard);
        case 6:
            return KingMoves(moveBoard);
        default:
            return;
    }
}

void Rules::PawnMoves(const array<array<int,8>,8>& moveBoard)
{
//    if white
    if (m_pieceID > 0)
    {
        if ((moveBoard)[row+1][col]==0){
            availableMoves.push_back({row + 1, col});
            if (row==1 && (moveBoard)[row+2][col]==0){
                availableMoves.push_back({row+2,col});
            }
        }
        for (int i=-1;i<2;i+=2){
            if ((moveBoard)[row+i*i][col+i]*(moveBoard)[row][col]<0){
                availableMoves.push_back({row+i*i,col+i});
            }
        }
    } //else black
    else
    {
        if ((moveBoard)[row-1][col]==0){
            availableMoves.push_back({row - 1, col});
            if (row==6 && (moveBoard)[row-2][col]==0){
                availableMoves.push_back({row-2,col});
            }
        }
        for (int i=-1;i<2;i+=2){
            if ((moveBoard)[row-i*i][col-i]*(moveBoard)[row][col]<0){
                availableMoves.push_back({row-i*i,col-i});
            }
        }
    }
}

void Rules::KnightMoves(const array<array<int,8>,8>& moveBoard)
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
            if ((moveBoard)[newRow][newCol] == 0)
            {
                availableMoves.push_back({newRow, newCol});
            }
                // use fact that same colour will times to positive
            else if (((moveBoard)[row][col] * (moveBoard)[newRow][newCol] < 0))
            {
                availableMoves.push_back({newRow, newCol});
            }
            else
                continue;
        }
    }
}

void Rules::BishopMoves(const array<array<int,8>,8>& moveBoard) { DiagonalMoves(moveBoard); }

void Rules::RookMoves(const array<array<int,8>,8>& moveBoard) { LateralMoves(moveBoard); }

void Rules::QueenMoves(const array<array<int,8>,8>& moveBoard)
{
    LateralMoves(moveBoard);
    DiagonalMoves(moveBoard);
}

void Rules::KingMoves(const array<array<int,8>,8>& moveBoard)
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
                if ((moveBoard)[newRow][newCol] == 0)
                {
                    availableMoves.push_back({newRow, newCol});
                }
                    // use fact that same colour will times to positive
                else if (((moveBoard)[row][col] * (moveBoard)[newRow][newCol] < 0))
                {
                    availableMoves.push_back({newRow, newCol});
                }
                else
                    continue;
            }
        }
    }
}

void Rules::DiagonalMoves(const array<array<int,8>,8>& moveBoard) {
    for (int i=-1;i<2;i+=2){
        for (int j=-1;j<2;j+=2){
            int k = 1;
            while((row+k*i >= 0) && (row+k*i <8) && (col+k*j >= 0) && (col+k*j <8)){
                if ((moveBoard)[row+i*k][col+j*k]==0){
                    availableMoves.push_back({row+i*k,col+j*k});
                    k++;
                } else if((moveBoard)[row+i*k][col+j*k]*(moveBoard)[row][col]<0){
                    availableMoves.push_back({row+i*k,col+j*k});
                    break;
                } else break;
            }
        }
    }
}

void Rules::LateralMoves(const array<array<int,8>,8>& moveBoard) {
    for (int i=-1;i<2;i+=2){
        int k=1;
        while((col+k*i>=0) &&(col+k*i < 8)){
            if ((moveBoard)[row][col+k*i]==0){
                availableMoves.push_back({row,col+k*i});
                k++;
            }
            else if ((moveBoard)[row][col]*(moveBoard)[row][col+k*i]<0){
                availableMoves.push_back({row,col+k*i});
                break;
            } else break;
        }
        while((row+k*i>=0) &&(row+k*i < 8)){
            if ((moveBoard)[row+k*i][col]==0){
                availableMoves.push_back({row+k*i,col});
                k++;
            }
            else if ((moveBoard)[row][col]*(moveBoard)[row+k*i][col]<0){
                availableMoves.push_back({row+k*i,col});
                break;
            } else break;
        }
    }
}

// Think the first part will be a lot easier, of checking if any of the available moves after a piece has moved has the king in them
//after that, not sure how to get the other king in, apart from checking all the moves that the king could do from that position
bool Rules::KingCheck(int npID,const array<array<int,8>,8>& currBoard ) {
    int targetKing;
    if(npID<0) targetKing=6;
    else targetKing=-6;
    for(auto square : availableMoves){
        if (currBoard[square.first][square.second] == targetKing) return true;
    }
    return false;
}

bool Rules::CheckDiagonal(const array<array<int,8>,8>& currBoard,int kingSign, pair<int,int> kingPos) {
    for (int i=-1;i<2;i+=2){
        for (int j=-1;j<2;j+=2){
            int k = 1;
            while((row+k*i >= 0) && (row+k*i <8) && (col+k*j >= 0) && (col+k*j <8)){
                if ((currBoard)[row+i*k][col+j*k]==0) {
                    k++;
                } else if((currBoard)[row+i*k][col+j*k]*kingSign<0){
                    return true;
                } else{
                    break;
                }
            }
        }
    }
    return false;
}

bool Rules::CheckLateral(const array<array<int, 8>, 8> &currBoard, int kingSign, pair<int,int> kingPos) {
    for (int i=-1;i<2;i+=2){
        int k=1;
        while((col+k*i>=0) &&(col+k*i < 8)){
            if ((currBoard)[row][col+k*i]==0){
                k++;
            }
            else if ((currBoard)[row][col]*(currBoard)[row][col+k*i]<0){
                break;
            } else break;
        }
        while((row+k*i>=0) &&(row+k*i < 8)){
            if ((currBoard)[row+k*i][col]==0){
                k++;
            }
            else if ((currBoard)[row][col]*(currBoard)[row+k*i][col]<0){
                break;
            } else break;
        }
    }
}

