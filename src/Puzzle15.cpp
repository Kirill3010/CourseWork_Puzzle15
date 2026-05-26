#include "Puzzle15.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <cctype>

using namespace std;

Puzzle15::Puzzle15() {
    resetBoard();
}

void Puzzle15::resetBoard() {
    board = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
    };
}

vector<int> Puzzle15::getBoard() const {
    return board;
}

void Puzzle15::printBoard() const {
    cout << "\n+----+----+----+----+\n";

    for (int i = 0; i < 16; i++) {
        cout << "|";

        if (board[i] == 0) {
            cout << "    ";
        } else {
            cout << setw(3) << board[i] << " ";
        }

        if ((i + 1) % 4 == 0) {
            cout << "|\n+----+----+----+----+\n";
        }
    }
}

int Puzzle15::findEmpty() const {
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        if (board[i] == 0) {
            return i;
        }
    }

    return -1;
}

bool Puzzle15::moveTile(char direction) {
    int emptyIndex = findEmpty();

    if (emptyIndex == -1) {
        return false;
    }

    int row = emptyIndex / 4;
    int col = emptyIndex % 4;

    int newRow = row;
    int newCol = col;

    direction = static_cast<char>(tolower(direction));

    if (direction == 'w') {
        newRow++;
    } else if (direction == 's') {
        newRow--;
    } else if (direction == 'a') {
        newCol++;
    } else if (direction == 'd') {
        newCol--;
    } else {
        return false;
    }

    if (newRow < 0 || newRow >= 4 || newCol < 0 || newCol >= 4) {
        return false;
    }

    int targetIndex = newRow * 4 + newCol;

    swap(board[emptyIndex], board[targetIndex]);

    return true;
}

bool Puzzle15::isSolved() const {
    for (int i = 0; i < 15; i++) {
        if (board[i] != i + 1) {
            return false;
        }
    }

    return board[15] == 0;
}

void Puzzle15::shuffleBoard(int moves) {
    vector<char> directions = {'w', 'a', 's', 'd'};

    random_device rd;
    mt19937 generator(rd());

    for (int i = 0; i < moves; i++) {
        shuffle(directions.begin(), directions.end(), generator);

        for (char direction : directions) {
            if (moveTile(direction)) {
                break;
            }
        }
    }
}