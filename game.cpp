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
    this->turn = 0;
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
                if (canMove.size()==0){
                    this->m_evman.HandleEvent(event);
                    this->m_evman.GetMoves();
                    this->canMove = m_evman.ReturnMoves();
                    this->firstClick = m_evman.ReturnClickPos();
                    break;
                }else{
                    this->m_evman.HandleEvent(event, canMove,firstClick);
                    if (canMove.size()==2){
                        Board::makeMove(canMove[0],canMove[1]);
//                        int idMoved = Board::board[canMove[1].first][canMove[1].second];
                        if (Rules::KingCheck(1,Board::board)){
                            cout << "White king is in check!" << endl;
                        }
                        if (Rules::KingCheck(-1,Board::board)){
                            cout << "Black king is in check!" << endl;
                        }
                        canMove.clear();
                        break;
                    } else{
                        canMove.clear();
                        break;
                    }
                }


        }
    }
}



void Game::render() {
    this->window->clear();
//    Render stuff here
    DrawBackground();
    DrawPieces();
    ShowMoves();

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
            if ((Board::board)[i][j]!= 0){
                int id = (Board::board)[i][j];
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
    sprites.clear();
    PiecesOnBoard();
    for (auto spr : sprites){
        Draw(spr);
    }
}

void Game::ShowMoves() {
    for (auto x : canMove){
            float ypos = ((float)x.first)*(1000.f)/(8.f)+((float)(0.85)*(1000.f/16.f));
            float xpos = ((float)x.second)*(1000.f)/(8.f)+((float)(0.85)*(1000.f/16.f));
            sf::CircleShape move(10.f);
            move.setFillColor(sf::Color::Cyan);
            move.setPosition(xpos,ypos);
            Draw(move);
    }
}
