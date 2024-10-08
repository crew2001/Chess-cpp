#include "rules.h"
#include <vector>

Rules::Rules(int in_pieceID, int in_row, int in_col)
    : row(in_row), col(in_col), m_pieceID(in_pieceID) {
  this->Setup(Board::board);
  //    this->GetMoves();
}

// Rules::Rules(pair<int,int> newPiece, const array<array<int,8>,8>& currBoard){
//     this->Setup(currBoard[newPiece.first][newPiece.second],newPiece.first,newPiece.second,currBoard);
// }

void Rules::Setup(const array<array<int, 8>, 8> &moveBoard) {

  switch (abs(m_pieceID)) {
  case 1:
    return PawnMoves(moveBoard);
  case 2:
    return KnightMoves(moveBoard);
  case 3:
    return BishopMoves(moveBoard);
  case 4:
    return RookMoves(moveBoard);
  case 5:
    return QueenMoves(moveBoard);
  case 6:
    return KingMoves(moveBoard);
  default:
    return;
  }
}

vector<pair<int, int>> Rules::GetMoves() {
  vector<pair<int, int>> returnMoves;
  for (pair<int, int> x : availableMoves) {
    if (CanMove({row, col}, x)) {
      returnMoves.emplace_back(x);
    }
  }
  return returnMoves;
}

void Rules::PawnMoves(const array<array<int, 8>, 8> &moveBoard) {
  //    if white
  if (m_pieceID > 0) {
    if (moveBoard[row + 1][col] == 0) {
      availableMoves.emplace_back(row + 1, col);
      if (row == 1 && moveBoard[row + 2][col] == 0) {
        availableMoves.emplace_back(row + 2, col);
      }
    }
    for (int i = -1; i < 2; i += 2) {
      if (moveBoard[row + i * i][col + i] * moveBoard[row][col] < 0) {
        availableMoves.emplace_back(row + i * i, col + i);
      }
    }
    if (row == 4 && Board::lastMove.first == 4 &&
        (Board::lastMove.second == col + 1 ||
         Board::lastMove.second == col - 1)) {
      availableMoves.emplace_back(Board::lastMove.first + 1,
                                  Board::lastMove.second);
      enPassente = true;
    }
  } // else black
  else {
    if (moveBoard[row - 1][col] == 0) {
      availableMoves.emplace_back(row - 1, col);
      if (row == 6 && moveBoard[row - 2][col] == 0) {
        availableMoves.emplace_back(row - 2, col);
      }
    }
    for (int i = -1; i < 2; i += 2) {
      if (moveBoard[row - i * i][col - i] * moveBoard[row][col] < 0) {
        availableMoves.emplace_back(row - i * i, col - i);
      }
    }
    if (row == 3 && Board::lastMove.first == row &&
        (Board::lastMove.second == col + 1 ||
         Board::lastMove.second == col - 1)) {
      availableMoves.emplace_back(Board::lastMove.first - 1,
                                  Board::lastMove.second);
      enPassente = true;
    }
  }
}

void Rules::KnightMoves(const array<array<int, 8>, 8> &moveBoard) {
  vector<pair<int, int>> perms = {{1, 2},  {2, 1},  {-1, 2},  {2, -1},
                                  {-2, 1}, {1, -2}, {-2, -1}, {-1, -2}};
  for (pair<int, int> x : perms) {
    int newRow = row + x.first;
    int newCol = col + x.second;
    if (newRow < 0 || newRow > 7 || (newCol < 0 || newCol > 7))
      continue;
    else {
      if (moveBoard[newRow][newCol] == 0) {
        availableMoves.emplace_back(newRow, newCol);
      }
      // use fact that same colour will times to positive
      else if (moveBoard[row][col] * moveBoard[newRow][newCol] < 0) {
        availableMoves.emplace_back(newRow, newCol);
      } else
        continue;
    }
  }
}

void Rules::BishopMoves(const array<array<int, 8>, 8> &moveBoard) {
  DiagonalMoves(moveBoard);
}

void Rules::RookMoves(const array<array<int, 8>, 8> &moveBoard) {
  LateralMoves(moveBoard);
}

void Rules::QueenMoves(const array<array<int, 8>, 8> &moveBoard) {
  LateralMoves(moveBoard);
  DiagonalMoves(moveBoard);
}

void Rules::KingMoves(const array<array<int, 8>, 8> &moveBoard) {
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int newRow = row + i;
      int newCol = col + j;
      if (newRow < 0 || newRow > 7 || (newCol < 0 || newCol > 7))
        continue;
      else {
        if (moveBoard[newRow][newCol] == 0) {
          availableMoves.emplace_back(newRow, newCol);
        }
        // use fact that same colour will times to positive
        else if (moveBoard[row][col] * moveBoard[newRow][newCol] < 0) {
          availableMoves.emplace_back(newRow, newCol);
        } else
          continue;
      }
    }
  }
  if (m_pieceID < 0) {
    if (Board::blackCastle && moveBoard[7][2] == 0 && moveBoard[7][1] == 0 &&
        moveBoard[7][0] == -4) {
      if (!KingCheck(-1, moveBoard, {7, 1}) &&
          !KingCheck(-1, moveBoard, {7, 2}) &&
          !KingCheck(-1, moveBoard, {7, 3})) {
        availableMoves.emplace_back(row, col - 2);
      }
    }
    if (Board::blackCastle && moveBoard[7][4] == 0 && moveBoard[7][5] == 0 &&
        moveBoard[7][6] == 0 && moveBoard[7][7] == -4) {
      if (!KingCheck(-1, moveBoard, {7, 4}) &&
          !KingCheck(-1, moveBoard, {7, 5}) &&
          !KingCheck(-1, moveBoard, {7, 6}) &&
          !KingCheck(-1, moveBoard, {7, 3})) {
        availableMoves.emplace_back(row, col + 2);
      }
    }
  }
  if (m_pieceID > 0) {
    //        KING SIDE CASTLE
    if (Board::whiteCastle && moveBoard[0][2] == 0 && moveBoard[0][1] == 0 &&
        moveBoard[0][0] == 4) {
      if (!KingCheck(1, moveBoard, {0, 1}) &&
          !KingCheck(1, moveBoard, {0, 2}) &&
          !KingCheck(1, moveBoard, {0, 3})) {
        availableMoves.emplace_back(row, col - 2);
      }
    }
    //        QUEEN SIDE
    if (Board::whiteCastle && moveBoard[0][4] == 0 && moveBoard[0][5] == 0 &&
        moveBoard[0][6] == 0 && moveBoard[0][7] == 4) {
      if (!KingCheck(1, moveBoard, {0, 4}) &&
          !KingCheck(1, moveBoard, {0, 5}) &&
          !KingCheck(1, moveBoard, {0, 6}) &&
          !KingCheck(1, moveBoard, {0, 3})) {
        availableMoves.emplace_back(row, col + 2);
      }
    }
  }
}

void Rules::DiagonalMoves(const array<array<int, 8>, 8> &moveBoard) {
  for (int i = -1; i < 2; i += 2) {
    for (int j = -1; j < 2; j += 2) {
      int k = 1;
      while (row + k * i >= 0 && row + k * i < 8 && col + k * j >= 0 &&
             col + k * j < 8) {
        if (moveBoard[row + i * k][col + j * k] == 0) {
          availableMoves.emplace_back(row + i * k, col + j * k);
          k++;
        } else {
          if (moveBoard[row + i * k][col + j * k] * moveBoard[row][col] <
              0) {
            availableMoves.emplace_back(row + i * k, col + j * k);
          }
          break;
        }
      }
    }
  }
}

void Rules::LateralMoves(const array<array<int, 8>, 8> &moveBoard) {
  for (int i = -1; i < 2; i += 2) {
    int k = 1;
    while (col + k * i >= 0 && col + k * i < 8) {
      if (moveBoard[row][col + k * i] == 0) {
        availableMoves.emplace_back(row, col + k * i);
        k++;
      } else {
        if (moveBoard[row][col] * moveBoard[row][col + k * i] < 0) {
          availableMoves.emplace_back(row, col + k * i);
        }
        break;
      }
    }
    k = 1;
    while (row + k * i >= 0 && row + k * i < 8) {
      if (moveBoard[row + k * i][col] == 0) {
        availableMoves.emplace_back(row + k * i, col);
        k++;
      } else {
        if (moveBoard[row][col] * moveBoard[row + k * i][col] < 0) {
          availableMoves.emplace_back(row + k * i, col);
        }
        break;
      }
    }
  }
}

// checking if there is a bishop or queen of the opposite colour along the
// diags, or if there is a knights attacking, or pawn, etc
bool Rules::KingCheck(int npID, const array<array<int, 8>, 8> &currBoard) {
  bool lat = CheckLateral(currBoard, npID, Board::findKing(npID));
  bool diag = CheckDiagonal(currBoard, npID, Board::findKing(npID));
  bool pawn = CheckPawns(currBoard, npID, Board::findKing(npID));
  bool knight = CheckKnights(currBoard, npID, Board::findKing(npID));
  if (lat || diag || pawn || knight) {
    return true;
  }
  return false;
}

bool Rules::KingCheck(int npID, const array<array<int, 8>, 8> &currBoard,
                      pair<int, int> kingPosition) {
  bool lat = CheckLateral(currBoard, npID, kingPosition);
  bool diag = CheckDiagonal(currBoard, npID, kingPosition);
  bool pawn = CheckPawns(currBoard, npID, kingPosition);
  bool knight = CheckKnights(currBoard, npID, kingPosition);
  if (lat || diag || pawn || knight) {
    return true;
  }
  return false;
}

bool Rules::CheckDiagonal(const array<array<int, 8>, 8> &currBoard,
                          int kingSign, pair<int, int> kingPos) {
  vector<int> targets = {kingSign * -5, kingSign * -3};
  for (int i = -1; i < 2; i += 2) {
    for (int j = -1; j < 2; j += 2) {
      int k = 1;
      while (kingPos.first + k * i >= 0 && kingPos.first + k * i < 8 &&
             kingPos.second + k * j >= 0 && kingPos.second + k * j < 8) {
        int piece = currBoard[kingPos.first + i * k][kingPos.second + j * k];
        if (piece == 0) {
          k++;
        } else if (piece == kingSign * -5 || piece == kingSign * -3) {
          return true;
        } else {
          break;
        }
      }
    }
  }
  return false;
}

bool Rules::CheckLateral(const array<array<int, 8>, 8> &currBoard, int kingSign,
                         pair<int, int> kingPos) {
  vector<int> targets = {-kingSign * 5, -kingSign * 4};
  for (int i = -1; i < 2; i += 2) {
    int k = 1;
    //        searches along the row
    while (kingPos.second + k * i >= 0 && kingPos.second + k * i < 8) {
      int piece = currBoard[kingPos.first][kingPos.second + k * i];
      if (piece == 0) {
        k++;
      } else if (piece == kingSign * -5 || piece == kingSign * -4) {
        return true;
      } else
        break;
    }
    k = 1;
    //        searches along the column
    while (kingPos.first + k * i >= 0 && kingPos.first + k * i < 8) {
      int piece = currBoard[kingPos.first + k * i][kingPos.second];
      if (piece == 0) {
        k++;
      } else if (piece == kingSign * -5 || piece == kingSign * -4) {
        return true;
      } else
        break;
    }
  }
  return false;
}

bool Rules::CheckPawns(const array<array<int, 8>, 8> &currBoard, int kingSign,
                       pair<int, int> kingPos) {
  int target = kingSign * -1;
  if (currBoard[kingPos.first + 1 * kingSign][kingPos.second + 1] == target ||
      currBoard[kingPos.first + 1 * kingSign][kingPos.second - 1] == target) {
    return true;
  }
  return false;
}

bool Rules::CheckKnights(const array<array<int, 8>, 8> &currBoard, int kingSign,
                         pair<int, int> kingPos) {
  vector<pair<int, int>> perms = {{1, 2},  {2, 1},  {-1, 2},  {2, -1},
                                  {-2, 1}, {1, -2}, {-2, -1}, {-1, -2}};
  int target = kingSign * -2;
  for (pair<int, int> x : perms) {
    int rowKnight = kingPos.first + x.first;
    int colKinght = kingPos.second + x.second;
    if (rowKnight < 8 && rowKnight >= 0 && colKinght < 8 && colKinght >= 0 &&
        currBoard[rowKnight][colKinght] == target) {
      return true;
    }
  }
  return false;
}

bool Rules::CanMove(pair<int, int> start, pair<int, int> end) {
  int temp = Board::board[start.first][start.second];
  int pieceSign = temp < 0 ? -1 : 1;
  array<array<int, 8>, 8> saveBoard = Board::board;
  pair<int,int> kingcopy = pieceSign<0 ? Board::findKing(-1) : Board::findKing(1);
  Board::SimMove(saveBoard,start, end,kingcopy);
  if (KingCheck(pieceSign, saveBoard,kingcopy)) {
    return false;
  }
  return true;
}


void Rules::PawnMoves(const array<array<int, 8>, 8> &moveBoard,
                      vector<pair<int, int>> &moves) {
  //    if white
  if (m_pieceID > 0) {
    if (moveBoard[row + 1][col] == 0) {
      moves.emplace_back(row + 1, col);
      if (row == 1 && moveBoard[row + 2][col] == 0) {
        moves.emplace_back(row + 2, col);
      }
    }
    for (int i = -1; i < 2; i += 2) {
      if (moveBoard[row + i * i][col + i] * moveBoard[row][col] < 0) {
        moves.emplace_back(row + i * i, col + i);
      }
    }
  } // else black
  else {
    if (moveBoard[row - 1][col] == 0) {
      moves.emplace_back(row - 1, col);
      if (row == 6 && moveBoard[row - 2][col] == 0) {
        moves.emplace_back(row - 2, col);
      }
    }
    for (int i = -1; i < 2; i += 2) {
      if (moveBoard[row - i * i][col - i] * moveBoard[row][col] < 0) {
        moves.emplace_back(row - i * i, col - i);
      }
    }
  }
}

void Rules::KnightMoves(const array<array<int, 8>, 8> &moveBoard,
                        vector<pair<int, int>> &moves) {
  vector<pair<int, int>> perms = {{1, 2},  {2, 1},  {-1, 2},  {2, -1},
                                  {-2, 1}, {1, -2}, {-2, -1}, {-1, -2}};
  for (pair<int, int> x : perms) {
    int newRow = row + x.first;
    int newCol = col + x.second;
    if (newRow < 0 || newRow > 7 || (newCol < 0 || newCol > 7))
      continue;
    else {
      if (moveBoard[newRow][newCol] == 0) {
        moves.emplace_back(newRow, newCol);
      }
      // use fact that same colour will times to positive
      else if (moveBoard[row][col] * moveBoard[newRow][newCol] < 0) {
        moves.emplace_back(newRow, newCol);
      } else
        continue;
    }
  }
}

void Rules::BishopMoves(const array<array<int, 8>, 8> &moveBoard,
                        vector<pair<int, int>> &moves) {
  DiagonalMoves(moveBoard, moves);
}

void Rules::RookMoves(const array<array<int, 8>, 8> &moveBoard,
                      vector<pair<int, int>> &moves) {
  LateralMoves(moveBoard, moves);
}

void Rules::QueenMoves(const array<array<int, 8>, 8> &moveBoard,
                       vector<pair<int, int>> &moves) {
  LateralMoves(moveBoard, moves);
  DiagonalMoves(moveBoard, moves);
}

void Rules::KingMoves(const array<array<int, 8>, 8> &moveBoard,
                      vector<pair<int, int>> &moves) {
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      int newRow = row + i;
      int newCol = col + j;
      if (newRow < 0 || newRow > 7 || (newCol < 0 || newCol > 7))
        continue;
      else {
        if (moveBoard[newRow][newCol] == 0) {
          moves.emplace_back(newRow, newCol);
        }
        // use fact that same colour will times to positive
        else if (moveBoard[row][col] * moveBoard[newRow][newCol] < 0) {
          moves.emplace_back(newRow, newCol);
        } else
          continue;
      }
    }
  }
}

void Rules::DiagonalMoves(const array<array<int, 8>, 8> &moveBoard,
                          vector<pair<int, int>> &moves) {
  for (int i = -1; i < 2; i += 2) {
    for (int j = -1; j < 2; j += 2) {
      int k = 1;
      while (row + k * i >= 0 && row + k * i < 8 && col + k * j >= 0 &&
             col + k * j < 8) {
        if (moveBoard[row + i * k][col + j * k] == 0) {
          moves.emplace_back(row + i * k, col + j * k);
          k++;
        } else if (moveBoard[row + i * k][col + j * k] *
                       moveBoard[row][col] <
                   0) {
          moves.emplace_back(row + i * k, col + j * k);
          break;
        } else
          break;
      }
    }
  }
}

void Rules::LateralMoves(const array<array<int, 8>, 8> &moveBoard,
                         vector<pair<int, int>> &moves) {
  for (int i = -1; i < 2; i += 2) {
    int k = 1;
    while (col + k * i >= 0 && col + k * i < 8) {
      if (moveBoard[row][col + k * i] == 0) {
        moves.emplace_back(row, col + k * i);
        k++;
      } else if (moveBoard[row][col] * moveBoard[row][col + k * i] < 0) {
        moves.emplace_back(row, col + k * i);
        break;
      } else
        break;
    }
    k = 1;
    while (row + k * i >= 0 && row + k * i < 8) {
      if (moveBoard[row + k * i][col] == 0) {
        moves.emplace_back(row + k * i, col);
        k++;
      } else if (moveBoard[row][col] * moveBoard[row + k * i][col] < 0) {
        moves.emplace_back(row + k * i, col);
        break;
      } else
        break;
    }
  }
}
