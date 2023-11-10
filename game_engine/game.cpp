//
// Created by cillian on 24/08/23.
//

#include "game.h"

Game::Game(int window_size) : m_evman(window_size), window_size(window_size),endGame(false), turn(0)
{
  this->initWindow();
}


void Game::initWindow()
{
  m_window = new Window(window_size);
}

void Game::update() { PollEvents(); }

void Game::render()
{
  this->m_window->clear();
  //    Render stuff here
  this->m_window->drawBackground();
  this->m_window->drawPieces();
  ShowMoves();
  DrawCheckNotification();
  this->m_window->display();
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
// TODO : Not sure why the check circle is showing in top left corner
void Game::DrawCheckNotification()
{
    float square_size = float(window_size)/8.f;
  // IF WHITE KING CHECK THEN DRAW RED CIRCLE ONTO WHITE KING
  if (Rules::KingCheck(1, Board::board))
  {
    float ypos = ((float)Board::findKing(1).first) * square_size +
                 (square_size*3.f/8.f);
    float xpos = ((float)Board::findKing(1).second) * square_size +
                 (square_size*3.f/8.f);
    m_window->drawCheckNotification(xpos, ypos);
  }
  else if (Rules::KingCheck(-1, Board::board))
  {
    float ypos = ((float)Board::findKing(-1).first) * square_size +
                 (square_size*3.f/8.f);
    float xpos = ((float)Board::findKing(-1).second) * square_size +
                 (square_size*3.f/8.f);
    m_window->drawCheckNotification(xpos, ypos);
  }
}

void Game::getEvent()
{
  m_evman.HandleEvent(event, turn);
}

void Game::PollEvents()
{
  while (m_window->pollEvents(event))
  {
    if (event.type == sf::Event::MouseButtonPressed)
    {
      if (canMove.empty())
      {
        m_evman.HandleEvent(event, turn);
        m_evman.GetMoves();
        canMove = m_evman.ReturnMoves();
        firstClick = m_evman.ReturnClickPos();
        cout << "Game : first click, row = " << firstClick.first << " col = " << firstClick.second << endl;
        break;
      }
      else
      {
        m_evman.HandleEvent(event, canMove, firstClick);
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
        break;
      }
    }
  }
}