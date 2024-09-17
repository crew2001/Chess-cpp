//
// Created by cillian on 24/08/23.
//

#include "eventmanager.h"

/**
 * @brief Function to handle the event of the mouse click when selecting a piece
 *
 * @param event sfml mouse button event
 * @param turn the current turn of the game (even for white, odd for black)
 */
void EventManager::HandleEvent(sf::Event &event, int turn) {
  if (EventManager::CheckMate(-1)) {
    cout << "CHECKMATE, white wins" << endl;
    //        this->window->close();
  }
  if (EventManager::CheckMate(1)) {
    cout << "CHECKMATE, black wins" << endl;
    //        this->window->close();
  }
  //    x is col and y is row
  int xpos = event.mouseButton.x;
  int ypos = event.mouseButton.y;
  row = static_cast<int>(static_cast<double>(abs(ypos)) * (8. / 1000.));
  col = static_cast<int>(static_cast<double>(abs(xpos)) * (8. / 1000.));
  PieceChosen = Board::board[row][col];
  if ((turn % 2 == 0 && PieceChosen < 0) ||
      (turn % 2 == 1 && PieceChosen > 0)) {
    CorrectPiece = false;
  } else {
    CorrectPiece = true;
  }
}

/**
 * @brief Function to handle event when selecting a move
 *
 * @param event second sfml mouse button event
 * @param gameMoves current moves available
 * @param currentPiece position of the selected piece
 */
void EventManager::HandleEvent(sf::Event &event,
                               vector<pair<int, int>> &gameMoves,
                               const pair<int, int> &currentPiece) {
  int xpos = event.mouseButton.x;
  int ypos = event.mouseButton.y;
  row = static_cast<int>(static_cast<double>(abs(ypos)) * (8. / 1000.));
  col = static_cast<int>(static_cast<double>(abs(xpos)) * (8. / 1000.));
  //    PieceChosen = (m_board.getBoard())[row][col];
  pair<int, int> searchVect = {row, col};
  if (ranges::find(gameMoves, searchVect) != gameMoves.end()) {
    if (Rules::CanMove(currentPiece, {row, col})) {
      gameMoves = {{currentPiece}, {row, col}};
    } else {
      gameMoves = {{}};
    }
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

bool EventManager::CheckMate(int sideSign) {
  // * CHECK IF THE LAST PIECE WAS PAWN OR KNIGHT
  // * IF SO THEN KING HAS TO MOVE/ATTACKING PIECE NEEDS TO BE TAKEN
  if (!Rules::KingCheck(sideSign, Board::board)) {
    return false;
  }
  int attacking = Board::lastPiece;
  pair<int, int> kingUnderAttack =
      attacking < 0 ? Board::findKing(1) : Board::findKing(-1);
  Rules kings(Board::board[kingUnderAttack.first][kingUnderAttack.second],
              kingUnderAttack.first, kingUnderAttack.second);
  if (!kings.GetMoves().empty())
    return false;
  vector<pair<int, int>> piecesOnBoard;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (Board::board[i][j] * attacking < 0) {
        piecesOnBoard.emplace_back(i, j);
      }
    }
  }
  for (pair<int, int> protector : piecesOnBoard) {
    Rules possibles(Board::board[protector.first][protector.second],
                    protector.first, protector.second);
    if (!possibles.GetMoves().empty())
      return false;
  }
  return true;
}
