//
// Created by cillian on 24/08/23.
//

#include "eventmanager.h"

/**
 * @brief Handles first click of mouse and checks if piece is correct colour
 *
 * @param event : first click of mouse
 * @param turn : current turn, even is white, odd is black
 */
void EventManager::HandleEvent(const sf::Event &event, int turn)
{
  if (EventManager::CheckMate(-1))
  {
    cout << "CHECKMATE, white wins" << endl;
    //        this->window->close();
  }
  if (EventManager::CheckMate(1))
  {
    cout << "CHECKMATE, black wins" << endl;
    //        this->window->close();
  }
  //    x is col and y is row
  float xpos = event.mouseButton.x;
  float ypos = event.mouseButton.y;
  cout << "Ev man : xpos = " << xpos << " ypos = " << ypos << endl;
  float squareSize = float(window_size) / 8.0;
  col = floor(xpos / squareSize);
  row = floor((ypos) / squareSize);
  cout << "Ev man : row = " << row << " col = " << col << endl;
  PieceChosen = (Board::board)[row][col];
  if ((turn % 2 == 0 && PieceChosen < 0) ||
      (turn % 2 == 1 && PieceChosen > 0))
  {
    CorrectPiece = false;
  }
  else
  {
    CorrectPiece = true;
  }
}

/**
 * @brief Handles second click of mouse and checks if move is valid, if is then returns a vector of the two positions, as pairs
 *
 * @param event : second click of mouse
 * @param gameMoves : vector of pairs of positions of allowed moves from first click
 * @param currentPiece : piece that was clicked on first
 */
void EventManager::HandleEvent(const sf::Event &event,
                               vector<pair<int, int>> &gameMoves,
                               const pair<int, int> &currentPiece)
{
  float xpos = event.mouseButton.x;
  float ypos = event.mouseButton.y;
  cout << "Ev man : xpos = " << xpos << " ypos = " << ypos << endl;
  float squareSize = float(window_size) / 8.0;
  col = floor(xpos / squareSize);
  row = floor((ypos) / squareSize);
  cout << "Ev man : row = " << row << " col = " << col << endl;
  //    PieceChosen = (m_board.getBoard())[row][col];
  pair<int, int> searchVect = {row, col};
  if (find(gameMoves.begin(), gameMoves.end(), searchVect) != gameMoves.end())
  {
    if (Rules::CanMove(currentPiece, {row, col}))
    {
      gameMoves = {{currentPiece}, {row, col}};
    }
    else
    {
      gameMoves = {{}};
    }
  }
  else
  {
    gameMoves = {{}};
  }
}
// TODO : Can this be wrapped in ReturnMoves?
void EventManager::GetMoves()
{
  if (CorrectPiece)
  {
    Rules rules(PieceChosen, row, col);
    m_available = rules.GetMoves();
  }
  else
  {
    m_available = {};
  }
}

void EventManager::printBoard()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      cout << arrboard[i][j] << " , ";
    }
    cout << endl;
  }
}

bool EventManager::CheckMate(int sideSign)
{
  // * CHECK IF THE LAST PIECE WAS PAWN OR KNIGHT
  // * IF SO THEN KING HAS TO MOVE/ATTACKING PIECE NEEDS TO BE TAKEN
  if (!(Rules::KingCheck(sideSign, Board::board)))
  {
    return false;
  }
  int attacking = Board::lastPiece;
  pair<int, int> kingUnderAttack =
      (attacking < 0) ? Board::findKing(1) : Board::findKing(-1);
  Rules kings(Board::board[kingUnderAttack.first][kingUnderAttack.second],
              kingUnderAttack.first, kingUnderAttack.second);
  if (!(kings.GetMoves().empty()))
    return false;
  vector<pair<int, int>> piecesOnBoard;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (Board::board[i][j] * attacking < 0)
      {
        piecesOnBoard.emplace_back(i, j);
      }
    }
  }
  for (pair<int, int> protector : piecesOnBoard)
  {
    Rules possibles(Board::board[protector.first][protector.second],
                    protector.first, protector.second);
    if (!(possibles.GetMoves().empty()))
      return false;
  }
  return true;
}
