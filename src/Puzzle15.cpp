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

// Повернення поля до початкового розв'язаного стану.
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

// Виведення ігрового поля 4x4.
// Значення 0 використовується для позначення порожньої клітинки.
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

// Пошук індексу порожньої клітинки.
int Puzzle15::findEmpty() const {
    for (int i = 0; i < static_cast<int>(board.size()); i++) {
        if (board[i] == 0) {
            return i;
        }
    }

    return -1;
}

// Переміщення плитки у вибраному напрямку.
// Напрямки: W, A, S, D.
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

// Перевірка, чи знаходиться поле у фінальному стані.
bool Puzzle15::isSolved() const {
    for (int i = 0; i < 15; i++) {
        if (board[i] != i + 1) {
            return false;
        }
    }

    return board[15] == 0;
}

// Перевірка розв'язності позиції.
// Для поля 4x4 враховується кількість інверсій та рядок порожньої клітинки.
bool Puzzle15::isSolvable() const {
    int inversions = 0;

    for (int i = 0; i < 16; i++) {
        if (board[i] == 0) {
            continue;
        }

        for (int j = i + 1; j < 16; j++) {
            if (board[j] != 0 && board[i] > board[j]) {
                inversions++;
            }
        }
    }

    int emptyIndex = findEmpty();
    int emptyRowFromBottom = 4 - (emptyIndex / 4);

    if (4 % 2 == 1) {
        return inversions % 2 == 0;
    }

    return (emptyRowFromBottom % 2 == 0) != (inversions % 2 == 0);
}

// Генерація випадкового поля.
// Поле перемішується серією допустимих ходів із розв'язаного стану,
// тому згенерована позиція гарантовано є розв'язною.
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