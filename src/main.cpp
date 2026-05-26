#include <iostream>
#include <windows.h>
#include "Puzzle15.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Puzzle15 game;

    cout << "Логічна гра-головоломка «Гра у 15»\n";
    cout << "Перша тестова версія програми\n";

    game.shuffleBoard();
    game.printBoard();

    cout << "\nПрограма успішно запущена.\n";

    return 0;
}