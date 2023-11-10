#pragma once

#include "eventmanager.h"
#include "pieces.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
using namespace std;

class Window
{
private:
  sf::RenderWindow *window{};
  sf::VideoMode videoMode;
  vector<sf::Texture> m_textures = Pieces::loadTextures();
  vector<sf::Sprite> sprites;
  bool isOpen;
  void initWindow(int window_size);
  int WINDOW_SIZE;
  void windowParams(int window_size);

public:
  Window(int window_size);
  ~Window() = default;
  void draw(const sf::Drawable &l_drawable);
  void drawBackground();
  void drawPieces();
  void getSprites();
  void showMoves(const pair<int, int> &x);
  void render();
  void drawCheckNotification(float xpos, float ypos);
  void clear() { window->clear(); };
  void piecesOnBoard();
  void display() { this->window->display(); };

  bool isWindowOpen() { return this->isOpen; };

  void closeWindow() { this->isOpen = false; };

  bool pollEvents(sf::Event &event);
  sf::RenderWindow *getWindow() { return this->window; };
};