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
    PieceChosen = (m_board.getBoard())[row][col];
    cout << "(eMan)row,col,piece = " << row << " , " << col << " , " <<  PieceChosen << endl;
}



