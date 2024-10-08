#include "pieces.h"

vector<sf::Texture> Pieces::loadTextures() {
  vector<sf::Texture> texs;
  vector<string> ts = {"wp", "wn", "wb", "wr", "wq", "wk",
                       "bp", "bn", "bb", "br", "bq", "bk"};
  for (string c : ts) {
    string filename = "../game_engine/images/" + c + ".png";
    sf::Texture tex;
    tex.loadFromFile(filename);
    texs.push_back(tex);
  }
  return texs;
}
