//
// Created by cillian on 24/08/23.
//

#include "game.h"

Game::Game(int window_size) : m_evman(window_size), window_size(window_size), endGame(false), turn(0)
{
  initWindow();
}

void Game::initWindow()
{
  m_window = new Window(window_size);
}

void Game::update() {
    PollEvents();
}

void Game::render()
{
  m_window->clear();
  //    Render stuff here
  m_window->drawBackground();
  m_window->drawPieces();
  ShowMoves();
  DrawCheckNotification();
  m_window->display();
}

void Game::ShowMoves()
{
  for (auto x : canMove)
  {
    if (Rules::CanMove(firstClick, x))
    {
      m_window->showMoves(x);
    }
  }
}
void Game::DrawCheckNotification()
{
  float square_size = float(window_size) / 8.f;
  // IF WHITE KING CHECK THEN DRAW RED CIRCLE ONTO WHITE KING
  if (Rules::KingCheck(1, Board::board))
  {
      if (EventManager::CheckMate(1)){
          endGame = true;
          m_window->closeWindow();
          cout << "CHECKMATE, black wins" << endl;
      }
    float ypos = ((float)Board::findKing(1).first) * square_size +
                 (square_size * 3.f / 8.f);
    float xpos = ((float)Board::findKing(1).second) * square_size +
                 (square_size * 3.f / 8.f);
    m_window->drawCheckNotification(xpos, ypos);
  }
  else if (Rules::KingCheck(-1, Board::board))
  {
        if (EventManager::CheckMate(-1)){
            endGame = true;
            m_window->closeWindow();
            cout << "CHECKMATE, white wins" << endl;
        }
    float ypos = ((float)Board::findKing(-1).first) * square_size +
                 (square_size * 3.f / 8.f);
    float xpos = ((float)Board::findKing(-1).second) * square_size +
                 (square_size * 3.f / 8.f);
    m_window->drawCheckNotification(xpos, ypos);
  }
}

// void Game::getEvent()
// {
//   m_evman.HandleEvent(event, turn);
// }

void Game::PollEvents()
{
  m_window->pollEvents(click_pos);
  if (canMove.empty())
  {
    m_evman.HandleEvent(click_pos, turn);
    m_evman.GetMoves();
    canMove = m_evman.ReturnMoves();
    firstClick = m_evman.ReturnClickPos();
    //        break;
  }
  else
  {
    m_evman.HandleEvent(click_pos, canMove, firstClick);
    if (canMove.size() == 2)
    {
      Board::makeMove(canMove[0], canMove[1]);
      if (Rules::enPassente && abs(Board::board[canMove[1].first][canMove[1].second]) == 1)
      {
        if (canMove[1].first == 2)
        {
          Board::board[3][canMove[1].second] = 0;
          // Board::printBoard();
        }
        else if (canMove[1].first == 5)
        {
          Board::board[4][canMove[1].second] = 0;
          // Board::printBoard();
        }
      }
      Rules::enPassente = false;
      turn++;
      canMove.clear();
    }
    else
    {
      canMove.clear();
    }
    //        break;
  }
}