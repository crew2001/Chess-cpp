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

void Board::makeMove(vector<int> start, vector<int> end) {
    int temp = board[start[0]][start[1]];
    board[end[0]][end[1]] = temp;
    board[start[0]][start[1]] = 0;
}

void Board::makeMove(pair<int, int> start, pair<int, int> end) {
    int temp = board[start.first][start.second];
    if(abs(temp)==6){
        moveKing(temp,end);
    }
    board[end.first][end.second]=temp;
    board[start.first][start.second]=0;

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



