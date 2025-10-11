// Основной файл с функцией main()

// В целях масштабирования проекта, всё, что может потребоваться
// вынесено в следующие файлы:
// 1. game_constants.hpp
// 2. game_data.cpp
// 3. gametypes.hpp
// 4. game_types.cpp

// !!! Используются особенности C++20

#include "game_input.hpp"
#include "game_console.hpp"
#include "game_events.hpp"

int main() {
    using game::Console;

    game::Input player_input;
    bool game_running = true;
    bool game_result = true;

    while (game_running) {
        Console::clear();

        Console::print("MENU\n");

        Console::print("Welcome to autobattler!\n");

        Console::print("Input [1] to start the game.");
        Console::print("Input [2] to exit the game.\n");

        player_input.getInput("12");

        if (!player_input.isValid()) { // Неккоректный ввод, continue
            Console::print("Wrong input!");
            Console::enter();
            continue;
        }

        // Ввод корректен, осталось его обработать
        if (player_input.getValue() == '1') {
            Console::print("Starting the game!");
            Console::enter();

            // Начинаем игру
            game_result = game::Events::game();
            // Уведомляем о результатах
            Console::clear();
            Console::print("GAME RESULT\n");
            if (game_result) {
                Console::print("You won");
            }
            else {
                Console::print("You lose");
            }
            Console::enter();
        }
        else {
            Console::print("Exiting the game!");
            Console::enter();
            game_running = false;
            // Уведомляем о выходе
        }
    } // end while

    return 0;
}