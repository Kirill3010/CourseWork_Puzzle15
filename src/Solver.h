#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <string>

class Solver {
public:
    static std::string solve(const std::vector<int>& startBoard);

private:
    static int manhattanDistance(const std::vector<int>& board);
    static std::string boardToString(const std::vector<int>& board);
    static std::vector<std::pair<std::vector<int>, char>> getNeighbors(const std::vector<int>& board);
};

#endif