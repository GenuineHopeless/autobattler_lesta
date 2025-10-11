#ifndef _GAME_INFO_HPP_
#define _GAME_INFO_HPP_

// Класс Info со статическими методами
// В основном, отображает полезную информацию в консоли и
// довольно активно используется в game_events.cpp

// Можно было бы Info сделать частью Events, но я посчитал нужным
// их разграничить для удобства отладки и разделения задач

#include "game_types.hpp"

#include <string>
#include <vector>

namespace game {

    class Info {
        public:
            static void stats_info(const Stats& stats);
            static void class_info();
            static void player_info(const Player& player);
            static void enemy_info(const Creature& enemy);
            static void weapon_info(WeaponId weapon_id);
            static void skills_info(const std::vector<SkillId>& skills);
            static void skill_use_info(const Creature& crt, SkillId skill);
            static void battle_status_info(const Creature& plr, const Creature& enm);
            static void level_up_info(const Player& player);
            static std::string bonus_str(const BonusInfo& bonus);
    }; // end class
} // end namespace

#endif // end #ifndef