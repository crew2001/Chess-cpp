#include "window.h"

Window::Window(int window_size) : WINDOW_SIZE(window_size), isOpen(true)
{
  this->initWindow(window_size);
}

void Window::drawBackground()
{
  auto black = sf::Color(118, 150, 86);
  auto white = sf::Color(238, 238, 210);
  sf::RectangleShape square(sf::Vector2f(float(WINDOW_SIZE) / 8.f, float(WINDOW_SIZE) / 8.f));
  for (int i = 0; i < 8; i++)
  {

    for (int j = 0; j < 8; j++)
    {
      if ((i + j) % 2 == 0)
      {
        square.setFillColor(white);
        square.setPosition(float(j) * float(WINDOW_SIZE) / 8.f, float(i) * float(WINDOW_SIZE) / 8.f);
        draw(square);
      }
      else
      {
        square.setFillColor(black);
        square.setPosition(float(j) * float(WINDOW_SIZE) / 8.f, float(i) * float(WINDOW_SIZE) / 8.f);
        draw(square);
      }
    }
  }
}

void Window::draw(const sf::Drawable &l_drawable)
{
  this->window->draw(l_drawable);
}

void Window::initWindow(int window_size)
{
  this->videoMode = sf::VideoMode(window_size, window_size);
  this->window =
      new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close);
}

void Window::pollEvents(pair<int, int> &click_pos)
{
  while (this->window->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      this->window->close();
      closeWindow();
    }
    if (event.type == sf::Event::MouseButtonPressed)
    {
      int xpos = event.mouseButton.x;
      int ypos = event.mouseButton.y;
      double squareSize = double(WINDOW_SIZE) / 8.0;
      int col = floor(xpos / squareSize);
      int row = floor((ypos) / squareSize);
      click_pos = {col, row};
    }
  }
}

void Window::drawPieces()
{
  piecesOnBoard();
  for (const auto &spr : sprites)
  {
    draw(spr);
  }
}

void Window::drawCheckNotification(float xpos, float ypos)
{
  sf::CircleShape checkSymbol(10.f);
  checkSymbol.setFillColor(sf::Color::Red);
  checkSymbol.setPosition(xpos, ypos);
  draw(checkSymbol);
}

void Window::piecesOnBoard()
{
  sprites.clear();
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if ((Board::board)[i][j] != 0)
      {
        int id = (Board::board)[i][j];
        if (id < 0)
        {
          id = -id + 6;
        }
        sf::Sprite sprite(m_textures[id - 1]);
        sprite.setPosition(j * float(WINDOW_SIZE) / float(8), i * float(WINDOW_SIZE) / float(8));
        sprite.setScale(0.8, 0.8);
        sprites.push_back(sprite);
      }
    }
  }
}

void Window::showMoves(const pair<int, int> &x)
{
  float ypos = ((float)x.first) * float(WINDOW_SIZE) / (8.f);
  float xpos = ((float)x.second) * float(WINDOW_SIZE) / (8.f);
  //  * Make circle shape be in middle of square
  float squareSize = float(WINDOW_SIZE) / 8.0;

  ypos = ypos + (squareSize / 2.0) - 10.0;
  xpos = xpos + (squareSize / 2.0) - 10.0;
  sf::CircleShape move(10.f);
  move.setFillColor(sf::Color::Cyan);
  move.setPosition(xpos, ypos);
  draw(move);
}
