#ifndef GAME_CONSTANTS_H_
#define GAME_CONSTANTS_H_

// Класс с некоторыми константами.
// Они неявно считаются inline.

namespace game {
    class Constants {
        public:
            constexpr static int MaxLevel = 3; // Максимальный уровень
            constexpr static int MaxBattles = 5; // Количество битв, для победы
            constexpr static int MaxStartStatValue = 3; // Максимальное старт. знач. характеристик
    }; // end class
} // end namespace

#endif // end #ifndef