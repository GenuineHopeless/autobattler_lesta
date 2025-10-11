#ifndef GAME_RANDOM_HPP_
#define GAME_RANDOM_HPP_

// Собственный простой класс Random для упрощения работы с рандомом

#include <random>

namespace game {

    class Random {
        private:
            // Под капотом храним дефолтный движок случайных чисел (gen)
            std::default_random_engine gen;
        public:
            // При создании инициализируем движок (gen) недетерменированным случайным числом (seed)
            Random() : gen(std::random_device{}()) {}

            // Генерируем случайное число из диапазона [start, end]
            int range(int start, int end);

    }; // end class
} // end namespace

#endif // end #ifndef