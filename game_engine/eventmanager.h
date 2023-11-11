//
// Created by cillian on 24/08/23.
//

#pragma once

#include "board.h"
#include "rules.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <vector>
#include <cmath>
// #include "game.h"

using namespace std;

class EventManager
{

private:
  int row;
  int col;
  int PieceChosen;
  Board m_board;

  vector<pair<int, int>> m_available;
  array<array<int, 8>, 8> arrboard = Board::board;
  int window_size;

public:
  EventManager(int window_size) : window_size(window_size){};

  bool CorrectPiece;

  ~EventManager() = default;

  void HandleEvent(const pair<int, int> &click_pos, int turn);

  void HandleEvent(const pair<int, int> &click_pos, vector<pair<int, int>> &gameMoves,
                   const pair<int, int> &currentPiece);

  bool IsCorrect() { return CorrectPiece; };

  void GetMoves();

  vector<pair<int, int>> ReturnMoves() const { return m_available; };

  pair<int, int> ReturnClickPos() const { return {row, col}; }

  void printBoard();

  static bool CheckMate(int sideSign);
};
