#ifndef PUZZLE15_H
#define PUZZLE15_H

#include <vector>

class Puzzle15 {
private:
    std::vector<int> board;

public:
    Puzzle15();

    void resetBoard();
    void shuffleBoard(int moves = 80);
    void printBoard() const;

    bool moveTile(char direction);
    bool isSolved() const;

    int findEmpty() const;

    std::vector<int> getBoard() const;
};

#endif