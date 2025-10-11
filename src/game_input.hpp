#ifndef GAME_INPUT_HPP_
#define GAME_INPUT_HPP_

// Простенький класс Input для обработки ввода игрока

namespace game {

    class Input {
        private:
            void clear();

            char value;
            bool valid;

        public:
            void getInput(const char * symbols); // Ввод
            char getValue(); // Получить значение
            bool isValid(); // Узнать, корректен ли последний ввод
    }; // end class
} // end namespace

#endif // end #ifndef