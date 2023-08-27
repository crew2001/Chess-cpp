//
// Created by cillian on 24/08/23.
//

#include "eventmanager.h"


void EventManager::HandleEvent(sf::Event &event, int turn) {
//    x is col and y is row
    int xpos = event.mouseButton.x;
    int ypos = event.mouseButton.y;
    row = (int) ((double) abs(ypos) * (8. / 1000.));
    col = (int) ((double) abs(xpos) * (8. / 1000.));
    PieceChosen = (Board::board)[row][col];
    if ((turn%2==0 && PieceChosen<0) || (turn%2==1 && PieceChosen>0)){
        CorrectPiece = false;
    }
    else{
        CorrectPiece = true;
    }

}

void
EventManager::HandleEvent(sf::Event &event, vector<pair<int, int>> &gameMoves, const pair<int, int> &currentPiece) {
    int xpos = event.mouseButton.x;
    int ypos = event.mouseButton.y;
    row = (int) ((double) abs(ypos) * (8. / 1000.));
    col = (int) ((double) abs(xpos) * (8. / 1000.));
//    PieceChosen = (m_board.getBoard())[row][col];
    pair<int, int> searchVect = {row, col};
    if (find(gameMoves.begin(), gameMoves.end(), searchVect) != gameMoves.end()) {
        if (Rules::CanMove(currentPiece,{row,col})){
            gameMoves = {{currentPiece},{row, col}};
        }
        else{
            gameMoves = {{}};
        }
    } 
    else {
        gameMoves = {{}};
    }
}


void EventManager::GetMoves() {
    Rules rules(PieceChosen, row, col);
    m_available = rules.GetMoves();
}

void EventManager::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << arrboard[i][j] << " , ";
        }
        cout << endl;
    }
}

bool EventManager::CheckMate(){
    // * CHECK IF THE LAST PIECE WAS PAWN OR KNIGHT 
    // * IF SO THEN KING HAS TO MOVE/ATTACKING PIECE NEEDS TO BE TAKEN
    int attacking = Board::lastPiece;
    pair<int,int> kingUnderAttack = (attacking<0) ? Board::findKing(1) : Board::findKing(-1);
    Rules kings(Board::board[kingUnderAttack.first][kingUnderAttack.second],kingUnderAttack.first,kingUnderAttack.second);
    if (!(kings.GetMoves().empty())) return false;
    vector<pair<int,int>> piecesOnBoard;
    for (int i =0;i<8;i++){
        for (int j=0;j<8;j++){
            if (Board::board[i][j]*attacking<0){
                piecesOnBoard.emplace_back(i,j);
            }
        }
    }
    for(pair<int,int> protector : piecesOnBoard){
        Rules possibles(Board::board[protector.first][protector.second],protector.first,protector.second);
        if (!(possibles.GetMoves().empty())) return false;
    }
    return true;

}




