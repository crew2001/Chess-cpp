//
// Created by cillian on 24/08/23.
//

#include "game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
}

void Game::initVariables() {
    this->endGame = false;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(1000,1000);
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close);
}

void Game::update() {
    this->pollEvents();
}

void Game::pollEvents() {
    while(this->window->pollEvent(this->event)) {
        switch(this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                this->m_evman.HandleEvent(event);
            }
        }
    }

void Game::render() {
    this->window->clear();

//    Render stuff here
    DrawBackground();
    DrawPieces();


    this->window->display();
}

void Game::Draw(sf::Drawable& l_drawable){
    this->window->draw(l_drawable);
}



void Game::DrawBackground(){
    auto black = sf::Color(118, 150, 86);
    auto white = sf::Color(238, 238, 210);
    sf::RectangleShape square(sf::Vector2f(1000.f/8.f,1000.f/8.f));
    for (int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if ((i + j) % 2 == 0) {
                square.setFillColor(white);
                square.setPosition(j * 1000.f / 8.f, i * 1000.f / 8.f);
                Draw(square);
            } else {
                square.setFillColor(black);
                square.setPosition(j * 1000.f / 8.f, i * 1000.f / 8.f);
                Draw(square);
        }
    }
}
}

void Game::PiecesOnBoard() {
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            if ((m_board.getBoard())[i][j]!= 0){
                int id = (m_board.getBoard())[i][j];
                if (id < 0){
                    id = -id+6;
                }
                sf::Sprite sprite(m_textures[id-1]);
                sprite.setPosition(j*1000.f/8.f,i*1000.f/8.f);
                sprites.push_back(sprite);
            }
        }
    }
}

void Game::DrawPieces() {
    PiecesOnBoard();
    for (auto spr : sprites){
        Draw(spr);
    }
}
