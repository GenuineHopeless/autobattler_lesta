#include "game_input.hpp"

#include <iostream>
#include <limits>
#include <cstring>

void game::Input::clear() {
    if (std::cin && (value != '\n')) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else {
        std::cin.clear();
    }
}

void game::Input::getInput(const char * symbols) {
    valid = false;
    std::cout << "INPUT >>> ";

    if (!std::cin.get(value).good()) { // ОШИБКА, неудачный ввод
        goto clearInput; // К очистке ввода
    }

    if (strchr(symbols, value) == NULL) { // ОШИБКА, недоступный символ
        goto clearInput; // К очистке ввода
    }

    // УСПЕХ, всё прошло успешно
    valid = true;

    clearInput: // Очистка ввода
    clear();
}

char game::Input::getValue() {
    return value;
}

bool game::Input::isValid() {
    return valid;
}