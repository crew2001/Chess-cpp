//
// Created by cillian on 24/08/23.
//

#include "player.h"

Player::Player() {
    this->initShape();
    this->initVariables();
}

void Player::initVariables() {

}

void Player::initShape() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(100.f,100.f));
}

void Player::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}

void Player::update() {

}

Player::~Player() {

}

