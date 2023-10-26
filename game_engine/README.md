# Chess engine library

Source code library for the chess game, which is packaged with the main.cpp executable 

## Outline

* chess_game executable : this will be created after running cmake .. in the build directory 
* board.cpp/.h : controls the board, such as making moves onto the board, and setting the board. The representation used has been an 8x8 array, with numbers representing the pieces. With positive = White, and negative = black
* Pieces key : ($\pm$ 1 = pawn; $\pm$ 2 = Knight; $\pm$ 3 = Bishop; $\pm$ 4 = Rook; $\pm$ 5 = Queen; $\pm$ 6 = King)
* Eventmanager.cpp/.h : handles the input of clicks onto the board, and feeds the position of the click to the Rules class
* rules.cpp/.h : the implementation of the rules of chess
* game.cpp/.h : controls the flow of the game with the game loop, as well as rendering the object to the screen
* pieces.cpp/.h : small class that handles the loading of the images of the chess pieces. 


