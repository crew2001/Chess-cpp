# Chess program in C++


This is a work in progress project in which I am making a chess program for 2 players to play against each other in chess. 

## Outline

* chess_game executable : this will be created after running cmake .. in the build directory 
* board.cpp/.h : controls the board, such as making moves onto the board, and setting the board. The representation used has been an 8x8 array, with numbers representing the pieces. With positive = White, and negative = black
* Pieces key : ($\pm$ 1 = pawn;$\pm$ 2 = Knight; $\pm$ 3 = Bishop; $\pm$ 4 = Rook; $\pm$ 5 = Queen; $\pm$ 6 = King)
* Eventmanager.cpp/.h : handles the input of clicks onto the board, and feeds the position of the click to the Rules class
* rules.cpp/.h : the implementation of the rules of chess
* game.cpp/.h : controls the flow of the game with the game loop, as well as rendering the object to the screen
* pieces.cpp/.h : small class that handles the loading of the images of the chess pieces. 

## Requirements

The only libraries that I have used are the SFML graphics library, so an installation of that would be required to run this project. The project uses Cmake so should be able to run on any modern operating system with Cmake and SFML installed.

## Progress

* Chess program is most of the way there, with the pieces moving properly
* The game is a click based game, with the back arrow key being able to undo a move (at the moment I believe that the undo functionality is limited to one move)
* Upon clicking on a piece, the available moves will be shown in blue
* If your king is in check then there will be a red dot on the king 


## Further Work 

* Need to add better behaviour/ recognition of checkmates
* Add a new .cpp & .h pair to handle the checking of the rules file
* Improve comments/other refactoring fixes
