#include "window.h"

Window::Window(int window_size) : WINDOW_SIZE(window_size), isOpen(true), window(sf::VideoMode(window_size, window_size), "Game", sf::Style::Close)
{
    initWindow();
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
  window.draw(l_drawable);
}

void Window::initWindow()
{
//  videoMode = sf::VideoMode(window_size, window_size);
//  window =
//      sf::RenderWindow(videoMode, "Game", sf::Style::Close);
  window.setFramerateLimit(60);
  window.setActive(false);
}

void Window::pollEvents(pair<int, int> &click_pos)
{
  while (window.pollEvent(event))
  {
      switch(event.type){
            case sf::Event::Closed:
                window.close();
                closeWindow();
                break;
            case sf::Event::MouseButtonPressed: {
                int xpos = event.mouseButton.x;
                int ypos = event.mouseButton.y;
                double squareSize = double(WINDOW_SIZE) / 8.0;
                int col = floor(xpos / squareSize);
                int row = floor((ypos) / squareSize);
                click_pos = {col, row};
                break;
            }
            default:
                break;
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
  float squareSize = float(WINDOW_SIZE) / 8.f;

  ypos = ypos + (squareSize / 2.f) - 10.f;
  xpos = xpos + (squareSize / 2.f) - 10.f;
  sf::CircleShape move(10.f);
  move.setFillColor(sf::Color::Cyan);
  move.setPosition(xpos, ypos);
  draw(move);
}
