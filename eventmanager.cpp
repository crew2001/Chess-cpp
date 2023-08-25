//
// Created by cillian on 24/08/23.
//

#include "eventmanager.h"


void EventManager::HandleEvent(sf::Event& event){
//    x is col and y is row
    int xpos = event.mouseButton.x;
    int ypos = event.mouseButton.y;
    row = (int)((double)abs(ypos) * (8. / 1000.));
    col = (int)((double)abs(xpos) * (8. / 1000.));
    PieceChosen = (Board::board)[row][col];
//    cout << "(eMan)row,col,piece = " << row << " , " << col << " , " <<  PieceChosen << endl;
}

void EventManager::HandleEvent(sf::Event &event, vector<vector<int>> &gameMoves,const vector<int>& currentPiece) {
    int xpos = event.mouseButton.x;
    int ypos = event.mouseButton.y;
    row = (int)((double)abs(ypos) * (8. / 1000.));
    col = (int)((double)abs(xpos) * (8. / 1000.));
//    PieceChosen = (m_board.getBoard())[row][col];
    vector<int> searchVect = {row,col};
    if(find(gameMoves.begin(),gameMoves.end(), searchVect)!=gameMoves.end()){
        gameMoves = {{currentPiece},{row,col}};
    }else{
        gameMoves={{}};
    }
}

void EventManager::GetMoves(){
    Rules rules(PieceChosen,row,col);
    m_available = rules.GetMoves();
}

void EventManager::printMoves() {
    for (auto x : m_available){
        cout << "(evMan) moves = " << x[0] << " , " << x[1] << endl;
    }
}


