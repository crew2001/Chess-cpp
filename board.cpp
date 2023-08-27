//
// Created by cillian on 24/08/23.
//

#include "board.h"

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " , ";
        }
        cout << endl;
    }
}

void Board::makeMove(pair<int, int> start, pair<int, int> end) {
    int temp = board[start.first][start.second];
    if(abs(temp)==6){
        moveKing(temp,end);
        if (start.second-end.second==2){
            if(temp<0){
                board[end.first][end.second-1]=0;
                board[start.first][start.second-1]=-4;
                blackCastle= false;
            }
            else{
                board[end.first][end.second-1]=0;
                board[start.first][start.second-1]=4;
                whiteCastle= false;
            }
        }
        else if (start.second-end.second==-2){
                if(temp<0){
                    board[end.first][end.second+2]=0;
                    board[start.first][start.second+1]=-4;
                    blackCastle= false;
                }
                else{
                    board[end.first][end.second+2]=0;
                    board[start.first][start.second+1]=4;
                    whiteCastle= false;
                }
            }
    }
    // * ADDING PAWN TO QUEEN AT END
    if ((temp==1 && end.first==7)){
        temp = 5;
    }
    if (temp==-1 && end.first==0){
        temp = -5;
    }
    board[end.first][end.second]=temp;
    board[start.first][start.second]=0;
    lastMove = end;
    lastPiece=temp;

}

void Board::moveKing(int kingSign, pair<int, int> newPosition) {
    if (kingSign<0){
        blackKing = newPosition;
    }
    else{
        whiteKing = newPosition;
    }
}

pair<int,int> Board::findKing(int kingSign){
    if (kingSign>0){
        return whiteKing;
    }
    else{
        return blackKing;
    }
}

void Board::UndoMove(pair<int, int> newPosition, pair<int, int> oldPosition, int taken) {
    int temp = board[newPosition.first][newPosition.second];
    board[newPosition.first][newPosition.second] = taken;
    board[oldPosition.first][oldPosition.second] = temp;
}






