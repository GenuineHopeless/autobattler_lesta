#ifndef GAME_CONSOLE_HPP_
#define GAME_CONSOLE_HPP_

// Класс для упрощенной работы с консолью.

namespace game {

    class Console {
        public:
            static void clear();
            static void enter();
            static void print(const char * text);
    }; // end class
} // end namespace

#endif // end #ifndef