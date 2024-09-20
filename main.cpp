#include "game_engine/game.h"
#include <iostream>

using namespace std;
int main() {
  Game game;
  while (game.running()) {
    game.update();
    game.render();
  }
  return 0;
}
