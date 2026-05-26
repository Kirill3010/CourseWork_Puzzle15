#include "Solver.h"

#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

struct SolverNode {
    vector<int> board;
    int g;
    int h;
    string path;

    int f() const {
        return g + h;
    }
};

struct CompareNode {
    bool operator()(const SolverNode& a, const SolverNode& b) const {
        return a.f() > b.f();
    }
};

string Solver::boardToString(const vector<int>& board) {
    string result;

    for (int value : board) {
        result += char(value + 'A');
    }

    return result;
}

int Solver::manhattanDistance(const vector<int>& board) {
    int distance = 0;

    for (int i = 0; i < 16; i++) {
        int value = board[i];

        if (value == 0) {
            continue;
        }

        int currentRow = i / 4;
        int currentCol = i % 4;

        int targetRow = (value - 1) / 4;
        int targetCol = (value - 1) % 4;

        distance += abs(currentRow - targetRow) + abs(currentCol - targetCol);
    }

    return distance;
}

vector<pair<vector<int>, char>> Solver::getNeighbors(const vector<int>& board) {
    vector<pair<vector<int>, char>> neighbors;

    int emptyIndex = -1;

    for (int i = 0; i < 16; i++) {
        if (board[i] == 0) {
            emptyIndex = i;
            break;
        }
    }

    int row = emptyIndex / 4;
    int col = emptyIndex % 4;

    vector<pair<char, pair<int, int>>> directions = {
        {'w', {row + 1, col}},
        {'s', {row - 1, col}},
        {'a', {row, col + 1}},
        {'d', {row, col - 1}}
    };

    for (auto direction : directions) {
        char move = direction.first;
        int newRow = direction.second.first;
        int newCol = direction.second.second;

        if (newRow >= 0 && newRow < 4 && newCol >= 0 && newCol < 4) {
            vector<int> newBoard = board;

            int newIndex = newRow * 4 + newCol;

            swap(newBoard[emptyIndex], newBoard[newIndex]);

            neighbors.push_back({newBoard, move});
        }
    }

    return neighbors;
}

string Solver::solve(const vector<int>& startBoard) {
    vector<int> goalBoard = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 0
    };

    string goalKey = boardToString(goalBoard);

    priority_queue<SolverNode, vector<SolverNode>, CompareNode> openSet;
    unordered_map<string, int> bestCost;

    SolverNode startNode;
    startNode.board = startBoard;
    startNode.g = 0;
    startNode.h = manhattanDistance(startBoard);
    startNode.path = "";

    openSet.push(startNode);
    bestCost[boardToString(startBoard)] = 0;

    int iterations = 0;
    const int maxIterations = 500000;

    while (!openSet.empty() && iterations < maxIterations) {
        iterations++;

        SolverNode current = openSet.top();
        openSet.pop();

        string currentKey = boardToString(current.board);

        if (currentKey == goalKey) {
            return current.path;
        }

        vector<pair<vector<int>, char>> neighbors = getNeighbors(current.board);

        for (auto neighbor : neighbors) {
            vector<int> nextBoard = neighbor.first;
            char move = neighbor.second;

            string nextKey = boardToString(nextBoard);
            int newCost = current.g + 1;

            if (!bestCost.count(nextKey) || newCost < bestCost[nextKey]) {
                bestCost[nextKey] = newCost;

                SolverNode nextNode;
                nextNode.board = nextBoard;
                nextNode.g = newCost;
                nextNode.h = manhattanDistance(nextBoard);
                nextNode.path = current.path + move;

                openSet.push(nextNode);
            }
        }
    }

    return "";
}