#include "game_console.hpp"

#include <iostream>
#include <limits>

void game::Console::clear() {
    std::cout << "\033[2J\033[1;1H";
}

void game::Console::enter() {
    char c;
    std::cout << "[PRESS ENTER]";
    std::cin.get(c);

    if (std::cin && (c != '\n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        std::cin.clear();
    }
}

void game::Console::print(const char * text) {
    std::cout << text << std::endl;
}