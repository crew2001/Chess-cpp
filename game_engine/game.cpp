//
// Created by cillian on 24/08/23.
//

#include "game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
}

/**
 * @brief Initializes the game variables
 */
void Game::initVariables() {
    this->endGame = false;
    this->turn = 0;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(1000, 1000);
    this->window =
        new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close);
}

void Game::update() { this->pollEvents(); }

/**
 * @brief Function to handle the events of the game (mouse clicks)
 */
void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    Board::UndoMove(Board::lastMoveBeforeAndAfter[0],
                                    Board::lastMoveBeforeAndAfter[1],
                                    Board::taken);
                    turn--;
                    break;
                }
            case sf::Event::MouseButtonPressed:
                // * FIRST CLICK, LOGS AVAILABLE MOVES
                if (canMove.empty()) {
                    m_evman.HandleEvent(event, turn);
                    if (m_evman.IsCorrect()) {
                        m_evman.GetMoves();
                        canMove = m_evman.ReturnMoves();
                        firstClick = m_evman.ReturnClickPos();
                    }
                    break;
                } else {
                    m_evman.HandleEvent(event, canMove, firstClick);
                    if (canMove.size() == 2) {
                        Board::makeMove(canMove[0], canMove[1]);
                        if (Rules::enPassente &&
                            abs(Board::board[canMove[1].first]
                                            [canMove[1].second]) == 1) {
                            if (canMove[1].first == 2) {
                                Board::board[3][canMove[1].second] = 0;
                                // Board::printBoard();
                            } else if (canMove[1].first == 5) {
                                Board::board[4][canMove[1].second] = 0;
                                // Board::printBoard();
                            }
                        }
                        Rules::enPassente = false;
                        turn++;
                        canMove.clear();
                        break;
                    } else {
                        canMove.clear();
                        break;
                    }
                }
        }
    }
}

/**
 * @brief Function to render the game
 */
void Game::render() {
    this->window->clear();
    //    Render stuff here
    DrawBackground();
    DrawPieces();
    DrawCheckNotification();
    ShowMoves();

    this->window->display();
}

void Game::Draw(sf::Drawable &l_drawable) { this->window->draw(l_drawable); }

/**
 * @brief Function to draw chessboard squares
 */
void Game::DrawBackground() {
    auto black = sf::Color(118, 150, 86);
    auto white = sf::Color(238, 238, 210);
    sf::RectangleShape square(sf::Vector2f(1000.f / 8.f, 1000.f / 8.f));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
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

/**
 * @brief Function to create sprites for pieces on the board
 */
void Game::PiecesOnBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Board::board[i][j] != 0) {
                int id = Board::board[i][j];
                if (id < 0) {
                    id = -id + 6;
                }
                sf::Sprite sprite(m_textures[id - 1]);
                sprite.setPosition(j * 1000.f / 8.f, i * 1000.f / 8.f);
                sprites.push_back(sprite);
            }
        }
    }
}

/**
 * @brief Function to draw the pieces on the board
 */
void Game::DrawPieces() {
    sprites.clear();
    PiecesOnBoard();
    for (auto spr : sprites) {
        Draw(spr);
    }
}

/**
 * @brief Function to show blue circles on available moves
 */
void Game::ShowMoves() {
    for (auto x : canMove) {
        if (Rules::CanMove(firstClick, x)) {
            float ypos = static_cast<float>(x.first) * 1000.f / 8.f +
                         static_cast<float>(0.85) * (1000.f / 16.f);
            float xpos = static_cast<float>(x.second) * 1000.f / 8.f +
                         static_cast<float>(0.85) * (1000.f / 16.f);
            sf::CircleShape move(10.f);
            move.setFillColor(sf::Color::Cyan);
            move.setPosition(xpos, ypos);
            Draw(move);
        }
        // else continue;
    }
}

/**
 * @brief Function to draw red circle on king if in check
 */
void Game::DrawCheckNotification() {
    // IF WHITE KING CHECK THEN DRAW RED CIRCLE ONTO WHITE KING
    if (Rules::KingCheck(1, Board::board)) {
        float ypos =
            static_cast<float>(Board::findKing(1).first) * 1000.f / 8.f +
            static_cast<float>(0.85) * (1000.f / 16.f);
        float xpos =
            static_cast<float>(Board::findKing(1).second) * 1000.f / 8.f +
            static_cast<float>(0.85) * (1000.f / 16.f);
        sf::CircleShape checkSymbol(10.f);
        checkSymbol.setFillColor(sf::Color::Red);
        checkSymbol.setPosition(xpos, ypos);
        Draw(checkSymbol);
    }
    if (Rules::KingCheck(-1, Board::board)) {
        float ypos =
            static_cast<float>(Board::findKing(-1).first) * 1000.f / 8.f +
            static_cast<float>(0.85) * (1000.f / 16.f);
        float xpos =
            static_cast<float>(Board::findKing(-1).second) * 1000.f / 8.f +
            static_cast<float>(0.85) * (1000.f / 16.f);
        sf::CircleShape checkSymbol(10.f);
        checkSymbol.setFillColor(sf::Color::Red);
        checkSymbol.setPosition(xpos, ypos);
        Draw(checkSymbol);
    }
}
