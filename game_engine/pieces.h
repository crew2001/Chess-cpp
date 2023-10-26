//
// Created by cillian on 24/08/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Pieces {
public:
    static vector<sf::Texture> textures;
    static vector<sf::Sprite> sprites;

//    static void loadTextures();
    static vector<sf::Texture> loadTextures();

    Pieces() {
        loadTextures();
    };

};
