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
    if (temp==1 && end.first==7){
        temp = 5;
    }
    if (temp==-1 && end.first==0){
        temp = -5;
    }
    taken = board[end.first][end.second];
    board[end.first][end.second]=temp;
    board[start.first][start.second]=0;
    lastMove = end;
    lastPiece=temp;
    lastMoveBeforeAndAfter = {end,start};
    

}

void Board::moveKing(int kingSign, const pair<int, int>&newPosition) {
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

void Board::UndoMove(const pair<int, int>&newPosition, const pair<int, int>&oldPosition, int takenPiece) {
    int temp = board[newPosition.first][newPosition.second];
    // * HAVE TO UNDO THE SPECIAL MOVES THAT WERE SIMULATED/CHECKED IN RULES
    // * FIRST IS IF THE CHECKED MOVE WAS A KING, IF SO HAVE TO GIVE BACK CASTLING RIGHTS
    if(abs(temp)==6){
        moveKing(temp,oldPosition);
        if (temp<0){
            blackKingMoves--;
            if (blackKingMoves==0 ){
                blackCastle = true;
            }
        }else{
            whiteKingMoves--;
            if(whiteKingMoves==0){
                whiteCastle=true;
            }
        }
    }
    // * NOW IF PAWN WAS MOVED TO THE ENDS
    if (abs(lastPiece)==1){
        if ((newPosition.first==0 || newPosition.first == 7) && abs(temp)==5 && abs(newPosition.first-oldPosition.first)==1){
            if (temp<0){
                temp=-1;
            }
            else{
                temp = 1;
            }
        }
    }
    board[newPosition.first][newPosition.second] = takenPiece;
    board[oldPosition.first][oldPosition.second] = temp;
}

void Board::SimMove(array<array<int,8>,8>& simBoard, const pair<int,int>&start, const pair<int,int>&end, pair<int,int>& kingcopy){
    int temp = simBoard[start.first][start.second];
    if(abs(temp)==6){
        kingcopy=end;
        if (start.second-end.second==2){
            if(temp<0){
                
                simBoard[end.first][end.second-1]=0;
                simBoard[start.first][start.second-1]=-4;
            }
            else{
                
                simBoard[end.first][end.second-1]=0;
                simBoard[start.first][start.second-1]=4;
            }
        }
        else if (start.second-end.second==-2){
                if(temp<0){
                    
                    simBoard[end.first][end.second+2]=0;
                    simBoard[start.first][start.second+1]=-4;
                }
                else{

                    simBoard[end.first][end.second+2]=0;
                    simBoard[start.first][start.second+1]=4;
                }
            }
    }
    // * ADDING PAWN TO QUEEN AT END
    if (temp==1 && end.first==7){
        temp = 5;
    }
    if (temp==-1 && end.first==0){
        temp = -5;
    }
    simBoard[end.first][end.second]=temp;
    simBoard[start.first][start.second]=0;
}




