#ifndef GAME_EVENTS_HPP_
#define GAME_EVENTS_HPP_

// Класс Events со статическими методами выступает в качестве разделения
// проекта на вполне осмысленные сцены, главная из которых game().

// game() так или иначе вызывает другие сцены, такая организация упрощает
// отладку и разрабоотку.

#include "game_types.hpp"

namespace game {

    class Events {
        public:
            static bool game(); // Главный игровой процесс
            static Player character_creation(); // Создание персонажа
            static bool battle(Creature& plr, Creature& enm); // Сражение
            static void level_up(Player& player); // Повышение уровня
            static void weapon_swap(Player& player, WeaponId reward); // Смена оружия
    }; // end class Events
} // end namespace game

#endif // end #ifndef GAME_EVENTS_HPP_