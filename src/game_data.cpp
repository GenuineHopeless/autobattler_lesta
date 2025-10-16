#include "game_data.hpp" // для доступа к объявлениям класса Data
#include "game_types.hpp" // для доступа к объявлениям многих типов игровых данных

#include <map> // для map

const std::map<game::StatId, game::StatInfo> game::Data::StatData = {
    {
        game::StatId::STR,
        {
            .name = "Strength"
        }
    },
    {
        game::StatId::AGI,
        {
            .name = "Agility"
        }
    },
    {
        game::StatId::VIT,
        {
            .name = "Vitality"
        }
    }
};

const std::map<game::WeaponTypeId, game::WeaponTypeInfo> game::Data::WeaponTypeData = {
    {
        game::WeaponTypeId::SLASH_TYPE,
        {
            .name = "Slash"
        }
    },
    {
        game::WeaponTypeId::BLUNT_TYPE,
        {
            .name = "Blunt"
        }
    },
    {
        game::WeaponTypeId::PIERCE_TYPE,
        {
            .name = "Pierce"
        }
    },
    {
        game::WeaponTypeId::MONSTER_TYPE,
        {
            .name = "None"
        }
    }
};

const std::map<game::ClassId, game::ClassInfo> game::Data::ClassData = {
    {
        game::ClassId::ROGUE,
        {
        .name = "Rogue",
        .hp_per_lvl = 4,
        .start_weapon = WeaponId::DAGGER,
        .bonuses = {
            {.bonus_value = SkillId::STEALTH_ATTACK, .bonus_type = BonusTypeId::SKILL_TYPE},
            {.bonus_value = StatId::AGI, .bonus_type = BonusTypeId::STAT_TYPE},
            {.bonus_value = SkillId::POISON, .bonus_type = BonusTypeId::SKILL_TYPE}
            }
        }
    

    },
    {
        game::ClassId::WARRIOR,
        {
        .name = "Warrior",
        .hp_per_lvl = 5,
        .start_weapon = WeaponId::SWORD,
        .bonuses = {
            {.bonus_value = SkillId::DRIVE_ATTACK, .bonus_type = BonusTypeId::SKILL_TYPE},
            {.bonus_value = SkillId::SHIELD, .bonus_type = BonusTypeId::SKILL_TYPE},
            {.bonus_value = StatId::STR, .bonus_type = BonusTypeId::STAT_TYPE}
            }
        }
    },
    {
        game::ClassId::BARBARIAN,
        {
        .name = "Barbarian",
        .hp_per_lvl = 6,
        .start_weapon = WeaponId::CLUB,
        .bonuses = {
            {.bonus_value = SkillId::FURY, .bonus_type = BonusTypeId::SKILL_TYPE},
            {.bonus_value = SkillId::STONE_SKIN, .bonus_type = BonusTypeId::SKILL_TYPE},
            {.bonus_value = StatId::VIT, .bonus_type = BonusTypeId::STAT_TYPE}
            }
        }
    }
};

const std::map<game::SkillId, game::SkillInfo> game::Data::SkillData = {
    {
        game::SkillId::STEALTH_ATTACK,
        {
        .name = "Stealth attack",
        .desc = "+1 dmg when AGI > target's AGI"
        }
    },
    {
        game::SkillId::POISON,
        {
            .name = "Poison",
            .desc = "+1 dmg/turn starting on turn 2 (+2 on turn 3, etc.)"
        }
    },
    {
        game::SkillId::DRIVE_ATTACK,
        {
            .name = "Drive attack",
            .desc = "x2 weapon dmg on turn 1"
        }
    },
    {
        game::SkillId::SHIELD,
        {
            .name = "Shield",
            .desc = "-3 dmg taken (if STR > target's STR)"
        }
    },
    {
        game::SkillId::FURY,
        {
            .name = "Fury",
            .desc = "+2 dmg (first 3 turns), then −1 dmg"
        }
    },
    {
        game::SkillId::STONE_SKIN,
        {
            .name = "Stone skin",
            .desc = "Reduce dmg taken for VIT stat"
        }
    },
    {
        game::SkillId::WEAK_BLUNT,
        {
            .name = "Weak to blunt",
            .desc = "take x2 dmg if target's weapon type is blunt"
        }
    },
    {
        game::SkillId::STRONG_SLASH,
        {
            .name = "Strong to slash",
            .desc = "resist to dmg from slash weapons"
        }
    },
    {
        game::SkillId::FIRE_BREATH,
        {
            .name = "Fire breath",
            .desc = "+3 dmg to attack every 3 turns"
        }
    }
};

const std::map<game::WeaponId, game::WeaponInfo> game::Data::WeaponData = {
    {
        game::WeaponId::SWORD,
        {
            .name = "Sword",
            .damage = 3,
            .damage_type = WeaponTypeId::SLASH_TYPE
        }
    },
    {
        game::WeaponId::CLUB,
        {
            .name = "Club",
            .damage = 3,
            .damage_type = WeaponTypeId::BLUNT_TYPE
        }
    },
    {
        game::WeaponId::DAGGER,
        {
            .name = "Dagger",
            .damage = 2,
            .damage_type = WeaponTypeId::PIERCE_TYPE
        }
    },
    {
        game::WeaponId::AXE,
        {
            .name = "Axe",
            .damage = 4,
            .damage_type = WeaponTypeId::SLASH_TYPE
        }
    },
    {
        game::WeaponId::SPEAR,
        {
            .name = "Spear",
            .damage = 3,
            .damage_type = WeaponTypeId::PIERCE_TYPE
        }
    },
    {
        game::WeaponId::LEGENDARY_SWORD,
        {
            .name = "Legendary sword",
            .damage = 10,
            .damage_type = WeaponTypeId::SLASH_TYPE
        }
    },
    {
        game::WeaponId::GOBLIN_WEAPON,
        {
            .name = "None",
            .damage = 2,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    },
    {
        game::WeaponId::SKELET_WEAPON,
        {
            .name = "None",
            .damage = 2,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    },
    {
        game::WeaponId::SLIME_WEAPON,
        {
            .name = "None",
            .damage = 1,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    },
    {
        game::WeaponId::GHOST_WEAPON,
        {
            .name = "None",
            .damage = 3,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    },
    {
        game::WeaponId::GOLEM_WEAPON,
        {
            .name = "None",
            .damage = 1,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    },
    {
        game::WeaponId::DRAGON_WEAPON,
        {
            .name = "None",
            .damage = 4,
            .damage_type = WeaponTypeId::MONSTER_TYPE
        }
    }
};

const std::map<game::EnemyId, game::EnemyInfo> game::Data::EnemyData = {
    {
        game::EnemyId::GOBLIN,
        {
            .name = "Goblin",
            .health = 5,
            .weapon = WeaponId::GOBLIN_WEAPON,
            .stats = {
                {StatId::STR, 1},
                {StatId::AGI, 1},
                {StatId::VIT, 1}
            },
            .skills = {},
            .reward = WeaponId::DAGGER
        }
    },
    {
        game::EnemyId::SKELET,
        {
            .name = "Skelet",
            .health = 10,
            .weapon = WeaponId::SKELET_WEAPON,
            .stats = {
                {StatId::STR, 2},
                {StatId::AGI, 2},
                {StatId::VIT, 1}
            },
            .skills = {SkillId::WEAK_BLUNT},
            .reward = WeaponId::CLUB
        }
    },
    {
        game::EnemyId::SLIME,
        {
            .name = "Slime",
            .health = 8,
            .weapon = WeaponId::SLIME_WEAPON,
            .stats = {
                {StatId::STR, 3},
                {StatId::AGI, 1},
                {StatId::VIT, 2}
            },
            .skills = {SkillId::STRONG_SLASH},
            .reward = WeaponId::SPEAR
        }
    },
    {
        game::EnemyId::GHOST,
        {
            .name = "Ghost",
            .health = 6,
            .weapon = WeaponId::GHOST_WEAPON,
            .stats = {
                {StatId::STR, 1},
                {StatId::AGI, 3},
                {StatId::VIT, 1}
            },
            .skills = {SkillId::STEALTH_ATTACK},
            .reward = WeaponId::SWORD
        }
    },
    {
        game::EnemyId::GOLEM,
        {
            .name = "Golem",
            .health = 10,
            .weapon = WeaponId::GOLEM_WEAPON,
            .stats = {
                {StatId::STR, 3},
                {StatId::AGI, 1},
                {StatId::VIT, 3}
            },
            .skills = {SkillId::STONE_SKIN},
            .reward = WeaponId::AXE
        }
    },
    {
        game::EnemyId::DRAGON,
        {
            .name = "Dragon",
            .health = 20,
            .weapon = WeaponId::DRAGON_WEAPON,
            .stats = {
                {StatId::STR, 3},
                {StatId::AGI, 3},
                {StatId::VIT, 3}
            },
            .skills = {SkillId::FIRE_BREATH},
            .reward = WeaponId::LEGENDARY_SWORD
        }
    }
};