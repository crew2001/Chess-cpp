//
// Created by cillian on 24/08/23.
//

#pragma once

#include "board.h"
#include <vector>
#include <array>
#include <iostream>
#include "pieces.h"
#include "eventmanager.h"
#include "rules.h"
#include "window.h"
using namespace std;
class Game
{
public:
    Game( int window_size);

    //    Accessors

    //  Modifiers

    //  Functions
    bool running() { return m_window->isWindowOpen(); }
    void update();
    void render();
    void PollEvents();
    void ShowMoves();
    void MakeMove();
    void DrawCheckNotification();
    int window_size;
    void PlayGame();

private:
    int turn;

    //    true if white is in check
    static bool whiteCheck;
    //  true if black is in check
    static bool blackCheck;
    vector<pair<int, int>> canMove;
    pair<int, int> click_pos;
    pair<int, int> firstClick;
    EventManager m_evman;
    Window *m_window;
    array<array<int, 8>, 8> arrboard = Board::board;
    bool endGame;
    void initWindow();
    // void getEvent();
};
