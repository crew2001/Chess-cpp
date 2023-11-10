#include <iostream>
// #include "game_engine/game.h"
#include "game_engine/game.h"
using namespace std;
int main() {
  Game game(800);
  while(game.running()) {
    game.update();
    game.render();
  }
  return 0;
}

