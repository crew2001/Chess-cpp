//
// Created by cillian on 24/08/23.
//

#pragma once

#include "board.h"
#include <vector>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "pieces.h"
#include "eventmanager.h"
using namespace std;
class Game{
    public:
    Game();
    ~Game() = default;

//    Accessors

//  Modifiers

//  Functions
    bool running() const { return this->window->isOpen(); }
    void update();
    void render();
    void pollEvents();
    void DrawBackground();
    void Draw(sf::Drawable& l_drawable);
    void ShowMoves();
    void MakeMove();

    private:
    vector<vector<int>> canMove;
    vector<int> firstClick;
    sf::Event event;
//    Pieces m_pieces;
    vector<sf::Texture> m_textures = Pieces::loadTextures();
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    EventManager m_evman;
    vector<sf::Sprite> sprites;
    Board m_board;
    array<array<int,8>,8> arrboard = Board::board;
    bool endGame;
    void initVariables();
    void initWindow();
    void PiecesOnBoard();
    void DrawPieces();
};
