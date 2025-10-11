#ifndef GAME_DATA_HPP_
#define GAME_DATA_HPP_

// Класс Data со статическими полями в рамках данного проекта выступает
// в роли базы данных практически со всей игровой информацией.

#include "game_types.hpp"

#include <map>

namespace game {
    
    class Data {
        public:
            static const std::map<StatId, StatInfo> StatData; // Информация по статам
            static const std::map<WeaponTypeId, WeaponTypeInfo> WeaponTypeData; // Информация по типам оружия
            static const std::map<ClassId, ClassInfo> ClassData; // Информация по классам персонажа
            static const std::map<SkillId, SkillInfo> SkillData; // Информация по игровым способностям
            static const std::map<WeaponId, WeaponInfo> WeaponData; // Информация по оружию
            static const std::map<EnemyId, EnemyInfo> EnemyData; // Информация по врагам
    }; // end class
} // end namespace

#endif // end #ifndef