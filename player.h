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


class Player{
private:
    sf::RectangleShape shape;
    void initVariables();
    void initShape();

public:
Player();
virtual ~Player();
void update();
void render(sf::RenderTarget *target);

};
