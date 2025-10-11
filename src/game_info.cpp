#include "game_info.hpp"
#include "game_types.hpp"
#include "game_data.hpp"

#include <iostream>
#include <string>
#include <format>
#include <variant>

void game::Info::stats_info(const Stats& stats) {
    std::cout << "[Stats]" << std::endl;

    for (const auto& stat : Data::StatData) {
        std::cout << stat.second.name << " = " << stats.at(stat.first) << std::endl;
    }
}

void game::Info::class_info() {
    std::cout << "[Class info]" << std::endl;
    std::cout << std::format(
        "{:16}{:16}{:12}{:16}{:16}",
        "Choice",
        "Name",
        "Hp bonus",
        "Weapon",
        "Level bonus"
    ) << std::endl;

    for (int i = 0; const auto& info : Data::ClassData) {
        std::cout << std::format(
            "[{}]{:13}{:16}{:<12}{:16}{:16}",
            i + 1,
            "",
            info.second.name,
            info.second.hp_per_lvl,
            Data::WeaponData.at(info.second.start_weapon).name,
            bonus_str(info.second.bonuses[0])
        ) << std::endl;
        ++i;
    }
}

void game::Info::player_info(const Player& player) {
    // Имя, уровень
    std::cout << player.name << ", " << player.level << " lvl" << std::endl;
    // Здоровье
    std::cout << "Health = " <<  player.max_health << std::endl;

    // Статы
    std::cout << std::endl;
    stats_info(player.stats);

    // Оружие
    std::cout << std::endl;
    Info::weapon_info(player.weapon);

    // Способности
    std::cout << std::endl;
    Info::skills_info(player.skills);
}

void game::Info::enemy_info(const Creature& enemy) {
    // Имя
    std::cout << enemy.name << std::endl;
    // Здоровье
    std::cout << "Health = " <<  enemy.max_health << std::endl;

    // Статы
    std::cout << std::endl;
    stats_info(enemy.stats);

    // Оружие
    std::cout << std::endl;
    Info::weapon_info(enemy.weapon);

    // Способности
    std::cout << std::endl;
    Info::skills_info(enemy.skills);
}

void game::Info::weapon_info(WeaponId weapon_id) {
    const WeaponInfo& weapon = Data::WeaponData.at(weapon_id);
    std::cout << "[Weapon]" << std::endl;
    std::cout << weapon.name << ", ";
    std::cout << "damage " << weapon.damage << ", ";
    std::cout << Data::WeaponTypeData.at(weapon.damage_type).name << std::endl;
}

void game::Info::skills_info(const std::vector<SkillId>& skills) {
    std::cout << "[Skills]" << std::endl;
    for (const auto& skill : skills) {
        std::cout << "<" << Data::SkillData.at(skill).name << ">" << std::endl;
        std::cout << Data::SkillData.at(skill).desc << std::endl;
        
    }

}

void game::Info::skill_use_info(const Creature& crt, SkillId skill) {
    std::cout << crt.name << " uses <" << Data::SkillData.at(skill).name << ">" << std::endl;
}

void game::Info::battle_status_info(const Creature& plr, const Creature& enm) {
    std::cout << plr.name << std::endl;
    std::cout << "[Health] <" << plr.health << " / " << plr.max_health << ">" << std::endl;
    std::cout << enm.name << std::endl;
    std::cout << "[Health] <" << enm.health << " / " << enm.max_health << ">" << std::endl;
}

void game::Info::level_up_info(const Player& player) {
    std::cout << std::format(
        "{:16}{:16}{:12}{:16}",
        "Choice",
        "Name",
        "Hp bonus",
        "Level bonus"
    ) << std::endl;

    for (int i = 0; const auto& info : Data::ClassData) {
        std::cout << std::format(
            "[{}]{:13}{:16}{:<12}{:16}",
            i + 1,
            "",
            info.second.name,
            info.second.hp_per_lvl,
            bonus_str(info.second.bonuses[player.upgrades.at(info.first)])
        ) << std::endl;
        ++i;
    }
}

std::string game::Info::bonus_str(const BonusInfo& bonus) {
    if (bonus.bonus_type == BonusTypeId::SKILL_TYPE) {
        return "Skill: " + Data::SkillData.at(std::get<SkillId>(bonus.bonus_value)).name;
    }
    return "Stat: " + Data::StatData.at(std::get<StatId>(bonus.bonus_value)).name + " + 1";
}