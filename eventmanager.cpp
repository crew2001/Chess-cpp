//
// Created by cillian on 24/08/23.
//

#include "eventmanager.h"


void EventManager::HandleEvent(sf::Event &event) {
//    x is col and y is row
    int xpos = event.mouseButton.x;
    int ypos = event.mouseButton.y;
    row = (int) ((double) abs(ypos) * (8. / 1000.));
    col = (int) ((double) abs(xpos) * (8. / 1000.));
    PieceChosen = (Board::board)[row][col];

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
        gameMoves = {{currentPiece},
                     {row, col}};
    } else {
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





