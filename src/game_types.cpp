#include "game_types.hpp"
#include "game_data.hpp"
#include "game_info.hpp"
#include "game_random.hpp"

#include <iostream>

game::Creature::Creature(EnemyId enemy_id) {
    const auto& enemy = Data::EnemyData.at(enemy_id);
    name = enemy.name;

    for (const auto& stat : Data::StatData) {
        stats[stat.first] = enemy.stats.at(stat.first);
    }

    max_health = enemy.health;
    health = max_health;
    weapon = enemy.weapon;
    skills = enemy.skills;
}

game::Player::Player(ClassId player_class, const Stats& new_stats) {
    name = "Player";
    for (const auto& stat : Data::StatData) {
        stats[stat.first] = new_stats.at(stat.first);
    }

    weapon = Data::ClassData.at(player_class).start_weapon;
    max_health = stats[StatId::VIT];
    health = max_health;
    level = 0;

    for (const auto& upgrade : Data::ClassData) {
        upgrades[upgrade.first] = 0;
    }

    level_up(player_class);
}

void game::Player::level_up(ClassId player_class) {
    const auto& class_info = Data::ClassData.at(player_class);
    const auto& bonus_info = class_info.bonuses[upgrades[player_class]];

    // Работаем с информацией о бонусе уровня
    if (bonus_info.bonus_type == BonusTypeId::SKILL_TYPE) {
        skills.push_back(std::get<SkillId>(bonus_info.bonus_value));
    }
    else {
        StatId stat_up = std::get<StatId>(bonus_info.bonus_value);
        if (stat_up == StatId::VIT){
            max_health++;
        }
        stats[stat_up]++;
    }
    
    // Высчитываем новое значение max_health
    max_health += class_info.hp_per_lvl;
    health = max_health;

    // Обновляем level и upgrades
    level++;
    upgrades[player_class]++;
}

void game::Player::restore_health() {
    health = max_health;
}

void game::Creature::attack(Creature& target, int action) const {
    // Номер хода текущего персонажа
    int personal_action = action / 2;

    // Механика попадания
    Random rand;
    int hit_chance = rand.range(1, stats.at(StatId::AGI) + target.stats[StatId::AGI]);
    if (hit_chance <= target.stats[StatId::AGI]) {
        std::cout << name << " missed" << std::endl;
        return;
    }

    // Переменные для просчёта урона
    int dmg_base = Data::WeaponData.at(weapon).damage;
    int dmg_add = stats.at(StatId::STR);
    int dmg_k = 1;

    // Обработка способностей атакующей стороны
    for (const auto& skill : skills) {
        switch (skill) {
        case SkillId::STEALTH_ATTACK:
            if (stats.at(StatId::AGI) > target.stats[StatId::AGI]) {
                Info::skill_use_info(*this, skill);
                dmg_add += 1;
            }
            break;
        
        case SkillId::POISON:
            if (personal_action) {
                Info::skill_use_info(*this, skill);
                dmg_add += personal_action;
            }
            break;
        
        case SkillId::DRIVE_ATTACK:
            if (personal_action == 0) {
                Info::skill_use_info(*this, skill);
                dmg_add += dmg_base;
            }
            break;
        
        case SkillId::FURY:
            if (personal_action < 3) {
                dmg_add += 2;
            }
            else {
                dmg_add -= 1;
            }
            Info::skill_use_info(*this, skill);
            break;

        case SkillId::FIRE_BREATH:
            if ((personal_action + 1) % 3 == 0) {
                Info::skill_use_info(*this, skill);
                dmg_add += 3;
            }
        } // end switch
    } // end for

    // Обработка способностей защищающейся стороны
    for (const auto& skill : target.skills) {
        switch (skill) {
        case SkillId::SHIELD:
            if (stats.at(StatId::STR) > target.stats[StatId::STR]) {
                Info::skill_use_info(target, skill);
                dmg_add -= 3;
            }
            break;
        
        case SkillId::STONE_SKIN:
            Info::skill_use_info(target, skill);
            dmg_add -= target.stats[StatId::VIT];
            break;
        
        case SkillId::WEAK_BLUNT:
            if (Data::WeaponData.at(weapon).damage_type == WeaponTypeId::BLUNT_TYPE) {
                Info::skill_use_info(target, skill);
                dmg_k *= 2;
            }
            break;
        
        case SkillId::STRONG_SLASH:
            if (Data::WeaponData.at(weapon).damage_type == WeaponTypeId::SLASH_TYPE) {
                Info::skill_use_info(target, skill);
                dmg_base = 0;
            }
            break;
        } // end switch
    } // end for

    // Просчитывание финального урона
    dmg_base = (dmg_base + dmg_add) * dmg_k;
    dmg_base = (dmg_base > 0) ? (dmg_base) : (0); // Урон не может быть отрицательным
    dmg_base = (dmg_base > target.health) ? (target.health) : (dmg_base); // Не может превышать текущее здоровье цели

    // Нанесение урона
    target.health -= dmg_base;
    std::cout << name << " deals " << dmg_base << " dmg" << std::endl;
    return;
} // end function