#include <iostream>
#include <limits>
#include <windows.h>
#include <thread>
#include <chrono>
#include <cctype>

#include "Puzzle15.h"
#include "Solver.h"

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

void showProgramInfo() {
    cout << "\n=====================================\n";
    cout << " ІНФОРМАЦІЯ ПРО ПРОГРАМУ\n";
    cout << "=====================================\n";
    cout << "Назва: Логічна гра-головоломка «Гра у 15»\n";
    cout << "Тип програми: консольний застосунок C++\n";
    cout << "Розмір поля: 4x4\n";
    cout << "Мета гри: розташувати числа від 1 до 15 у правильному порядку.\n\n";

    cout << "Основні можливості:\n";
    cout << "- випадкова генерація початкового поля;\n";
    cout << "- ручне проходження гри користувачем;\n";
    cout << "- автоматичний пошук рішення;\n";
    cout << "- безперервна демонстрація рішення;\n";
    cout << "- покрокова демонстрація рішення;\n";
    cout << "- перевірка розв'язності позиції;\n";
    cout << "- використання контейнерних класів C++.\n\n";

    cout << "Використані структури даних:\n";
    cout << "- vector для збереження ігрового поля;\n";
    cout << "- priority_queue для алгоритму A*;\n";
    cout << "- unordered_map для збереження вартості станів.\n\n";

    cout << "Алгоритм автоматичного рішення: A*.\n";
    cout << "Евристика: Манхеттенська відстань.\n";
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

void demonstrateSolution(Puzzle15& game, bool stepByStep) {
    if (game.isSolved()) {
        cout << "\nГоловоломка вже розв'язана.\n";
        game.printBoard();
        return;
    }

    if (!game.isSolvable()) {
        cout << "\nПоточна позиція не є розв'язною.\n";
        cout << "Створіть нову гру.\n";
        return;
    }

    cout << "\nПошук автоматичного рішення...\n";
    cout << "Зачекайте, це може зайняти кілька секунд.\n";

    string solution = Solver::solve(game.getBoard());

    if (solution.empty()) {
        cout << "\nРішення не знайдено або перевищено ліміт пошуку.\n";
        cout << "Спробуйте створити нову гру.\n";
        return;
    }

    cout << "\nРішення знайдено.\n";
    cout << "Кількість ходів: " << solution.length() << "\n";

    if (stepByStep) {
        clearInput();
    }

    for (int i = 0; i < static_cast<int>(solution.length()); i++) {
        char move = solution[i];

        game.moveTile(move);

        cout << "\nКрок " << i + 1 << " з " << solution.length() << "\n";
        cout << "Хід: " << move << "\n";

        game.printBoard();

        if (stepByStep) {
            cout << "Натисніть Enter для наступного кроку...";
            cin.get();
        } else {
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    }

    cout << "\nАвтоматичну демонстрацію завершено.\n";
}

void showMenu() {
    cout << "\n=====================================\n";
    cout << " ЛОГІЧНА ГРА-ГОЛОВОЛОМКА «ГРА У 15»\n";
    cout << "=====================================\n";
    cout << "1. Нова гра\n";
    cout << "2. Грати вручну\n";
    cout << "3. Показати поточне поле\n";
    cout << "4. Скинути поле до початкового стану\n";
    cout << "5. Автоматичне рішення - безперервний режим\n";
    cout << "6. Автоматичне рішення - покроковий режим\n";
    cout << "7. Інформація про програму\n";
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

                if (game.isSolvable()) {
                    cout << "Позиція є розв'язною.\n";
                } else {
                    cout << "Позиція не є розв'язною.\n";
                }

                game.printBoard();
                break;

            case 2:
                cout << "\nРежим ручної гри запущено.\n";
                playManual(game);
                break;

            case 3:
                cout << "\nПоточне поле:\n";
                game.printBoard();

                if (game.isSolvable()) {
                    cout << "Позиція є розв'язною.\n";
                } else {
                    cout << "Позиція не є розв'язною.\n";
                }
                break;

            case 4:
                game.resetBoard();
                cout << "\nПоле скинуто до початкового стану.\n";
                game.printBoard();
                break;

            case 5:
                demonstrateSolution(game, false);
                break;

            case 6:
                demonstrateSolution(game, true);
                break;

            case 7:
                showProgramInfo();
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