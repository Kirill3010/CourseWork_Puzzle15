#include <iostream>
#include <limits>
#include <windows.h>
#include "Puzzle15.h"

using namespace std;

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showControls() {
    cout << "\nКерування:\n";
    cout << "W - рух плитки вгору\n";
    cout << "S - рух плитки вниз\n";
    cout << "A - рух плитки вліво\n";
    cout << "D - рух плитки вправо\n";
    cout << "Q - повернутися в меню\n";
}

void playManual(Puzzle15& game) {
    char command;

    while (true) {
        game.printBoard();

        if (game.isSolved()) {
            cout << "\nВітаю! Ви розв'язали головоломку!\n";
            return;
        }

        showControls();

        cout << "\nВаш хід: ";
        cin >> command;

        command = static_cast<char>(tolower(command));

        if (command == 'q') {
            cout << "\nПовернення в головне меню...\n";
            return;
        }

        if (command != 'w' && command != 's' && command != 'a' && command != 'd') {
            cout << "\nНевідома команда. Спробуйте ще раз.\n";
            continue;
        }

        bool moved = game.moveTile(command);

        if (!moved) {
            cout << "\nНеможливий хід. Спробуйте інший напрямок.\n";
        }
    }
}

void showMenu() {
    cout << "\n=====================================\n";
    cout << " ЛОГІЧНА ГРА-ГОЛОВОЛОМКА «ГРА У 15»\n";
    cout << "=====================================\n";
    cout << "1. Нова гра\n";
    cout << "2. Грати вручну\n";
    cout << "3. Показати поточне поле\n";
    cout << "4. Скинути поле до початкового стану\n";
    cout << "0. Вихід\n";
    cout << "Ваш вибір: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Puzzle15 game;
    int choice;

    do {
        showMenu();

        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "\nПомилка введення. Введіть число з меню.\n";
            continue;
        }

        switch (choice) {
            case 1:
                game.resetBoard();
                game.shuffleBoard();
                cout << "\nСтворено нову випадкову гру.\n";
                game.printBoard();
                break;

            case 2:
                cout << "\nРежим ручної гри запущено.\n";
                playManual(game);
                break;

            case 3:
                cout << "\nПоточне поле:\n";
                game.printBoard();
                break;

            case 4:
                game.resetBoard();
                cout << "\nПоле скинуто до початкового стану.\n";
                game.printBoard();
                break;

            case 0:
                cout << "\nЗавершення програми.\n";
                break;

            default:
                cout << "\nНевірний пункт меню. Спробуйте ще раз.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}