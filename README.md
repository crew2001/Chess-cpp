# Chess program in C++


This is a work in progress project in which I am making a chess program for 2 players to play against each other in chess. 

## Requirements

The only libraries that I have used are the SFML graphics library, so an installation of that would be required to run this project. The project uses Cmake so should be able to run on any modern operating system with Cmake and SFML installed.

## Progress

* Chess program is most of the way there, with the pieces moving properly
* The game is a click based game, with the back arrow key being able to undo a move (at the moment I believe that the undo functionality is limited to one move)
* Upon clicking on a piece, the available moves will be shown in blue
* If your king is in check then there will be a red dot on the king 

## Usage 

```
mkdir build 
cd build 
cmake .. 
```

## Next steps

* Continue with refactor, with motivation to speed up code 
* Add replay option, so that you can undo moves
* Potential for full UI that shows moves
* (Ambitious goal) AI : probably minimax with alpha-beta pruning based 
