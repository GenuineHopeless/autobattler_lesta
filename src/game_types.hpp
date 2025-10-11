#ifndef GAME_TYPES_HPP_
#define GAME_TYPES_HPP_

// Тут содержаться основные игровые типы

#include "game_constants.hpp"

#include <string>
#include <vector>
#include <variant>
#include <map>

namespace game {
    enum class ClassId {
        ROGUE,
        WARRIOR,
        BARBARIAN
    }; // end enum class

    enum class EnemyId {
        GOBLIN,
        SKELET,
        SLIME,
        GHOST,
        GOLEM,
        DRAGON
    }; // end enum class

    enum class WeaponId {
        SWORD,
        CLUB,
        DAGGER,
        AXE,
        SPEAR,
        LEGENDARY_SWORD,
        GOBLIN_WEAPON,
        SKELET_WEAPON,
        SLIME_WEAPON,
        GHOST_WEAPON,
        GOLEM_WEAPON,
        DRAGON_WEAPON
    }; // end enum class

    enum class SkillId {
        STEALTH_ATTACK,
        POISON,
        DRIVE_ATTACK,
        SHIELD,
        FURY,
        STONE_SKIN,
        WEAK_BLUNT,
        STRONG_SLASH,
        FIRE_BREATH
    }; // end enum class

    enum class WeaponTypeId {
        SLASH_TYPE,
        BLUNT_TYPE,
        PIERCE_TYPE,
        MONSTER_TYPE
    }; // end enum class

    enum class BonusTypeId {
        SKILL_TYPE,
        STAT_TYPE
    }; // end enum class

    enum class StatId {
        STR,
        AGI,
        VIT
    }; // end enum class

    struct BonusInfo {
        std::variant<SkillId, StatId> bonus_value;
        BonusTypeId bonus_type;
    };

    struct StatInfo {
        std::string name;
    }; // end struct

    struct WeaponTypeInfo {
        std::string name;
    }; // end struct

    struct WeaponInfo {
        std::string name;
        int damage;
        WeaponTypeId damage_type;
    }; // end struct

    struct SkillInfo {
        std::string name;
        std::string desc;
    }; // end struct

    struct ClassInfo {
        std::string name;
        int hp_per_lvl;
        WeaponId start_weapon;
        BonusInfo bonuses[Constants::MaxLevel];
    };

    using Stats = std::map<StatId, int>;

    struct EnemyInfo {
        std::string name;
        int health;
        WeaponId weapon;
        Stats stats;
        std::vector<SkillId> skills;
        WeaponId reward;
    }; // end struct

    class Creature {
        public:
            std::string name;
            Stats stats;
            int max_health;
            int health;
            WeaponId weapon;
            std::vector<SkillId> skills;

            Creature() = default;
            Creature(EnemyId enemy_id);

            void attack(Creature& target, int action) const;
    }; // end class

    class Player: public Creature {
        public:
            int level;
            std::map<ClassId, int> upgrades;

            Player(ClassId player_class, const Stats& new_stats);

            void level_up(ClassId player_class);
            void restore_health();
    }; // end class
}

#endif // end #ifndef