#include "game_events.hpp"
#include "game_types.hpp"
#include "game_console.hpp"
#include "game_random.hpp"
#include "game_info.hpp"
#include "game_input.hpp"
#include "game_data.hpp"
#include "game_constants.hpp"

#include <iostream>

// Главный игровой процесс
bool game::Events::game() {
    bool game_running = true;
    Creature enemy;
    Random rand;
    EnemyId enemy_id;
    bool battle_result;
    int battle_wins = 0;

    // Создание игрока
    Player player = character_creation();

    while (game_running) {
        Console::clear();

        // Информация об игроке
        Console::print("CHARACTER INFO\n");
        Info::player_info(player);

        // Информация об игровом прогрессе
        Console::print("");
        Console::print("Progress");
        std::cout << battle_wins << " / " << Constants::MaxBattles << std::endl;

        Console::enter();
        Console::clear();

        // Генерация врага и отображение информации
        enemy_id = static_cast<EnemyId>(rand.range(0, game::Data::EnemyData.size() - 1));
        enemy = Creature(enemy_id);
        Console::print("ENEMY INFO\n");
        Info::enemy_info(enemy);
        Console::print("");
        Console::enter();

        // Сражение
        player.restore_health(); // Восстановить хп
        battle_result = battle(player, enemy);

        // Результат сражения
        Console::clear();
        Console::print("BATTLE RESULT\n");
        if (battle_result) {
            Console::print("You won");
            battle_wins++;
        }
        else {
            Console::print("You lose");
            game_running = false; // Выполнено условие неуспешного завершения игры
        }
        Console::enter();

        // Новый уровень
        if (battle_result) {
            if (player.level < Constants::MaxLevel) {
                Events::level_up(player);
            }
        }

        // Смена оружия
        if (battle_result) {
            Events::weapon_swap(player, Data::EnemyData.at(enemy_id).reward);
        }

        
        if (battle_wins >= Constants::MaxBattles) {
            game_running = false; // Выполнено условие успешного завершения игры
        }
    } // end while

    return battle_result;
} // end function

// Создание игрока
game::Player game::Events::character_creation() {
    Random rand;
    Input player_input;
    ClassId player_start_class;
    Stats random_stats;

    // Присваиваем случайные статы
    for (const auto& stat : Data::StatData) {
        random_stats[stat.first] = rand.range(1, Constants::MaxStartStatValue);
    }

    while (true) { // Выход из цикла будет посредством return (из-за ввода)
        Console::clear();
        Console::print("CHARACTER CREATION\n");

        // Показать статы персонажа
        Info::stats_info(random_stats);

        // Показать информацию по классам
        Console::print("");
        Info::class_info();

        // Обработка ввода игрока
        Console::print("");
        Console::print("Which class would you choose?");
        player_input.getInput("123");

        if (!player_input.isValid()) { // Неккоректный ввод, continue
            Console::print("Invalid input");
            Console::enter();
            continue;
        }

        // Ввод корректен, осталось обработать ввод игрока
        switch (player_input.getValue())
        {
        case '1':
            player_start_class = ClassId::ROGUE;
            break;
        
        case '2':
            player_start_class = ClassId::WARRIOR;
            break;
        case '3':
            player_start_class = ClassId::BARBARIAN;
            break;
        }

        Console::print("Character was created.");
        Console::enter();
        return Player{player_start_class, random_stats}; // Точка выхода из функции
    } // end while
} // end function

// Сражение
bool game::Events::battle(Creature& plr, Creature& enm) {
    int action = 0; // счетчик ходов

    Creature * first = &plr;
    Creature * second = &enm;
    Creature * tmp = nullptr;

    Console::clear();
    Console::print("BATTLE\n");
    Info::battle_status_info(plr, enm);
    Console::print("");

    // Определяем кто ходит первым, он же будет first
    if (plr.stats[StatId::AGI] < enm.stats[StatId::AGI]) {
        first = &enm;
        second = &plr;
    }

    std::cout << first->name << " goes first" << std::endl;
    Console::enter();

    while (plr.health > 0 && enm.health > 0) { // Сражение идёт, пока хп каждого > 0
        // Показать информацию
        Console::clear();
        Console::print("BATTLE\n");
        Info::battle_status_info(plr, enm);
        Console::print("");

        // first атакует second
        first->attack(*second, action);

        // first и second меняются местами
        tmp = first;
        first = second;
        second = tmp;

        // Увеличить счётчик ходов
        ++action;

        Console::enter();
    } // end while

    return plr.health > 0;
} // end function

// Повышение уровня
void game::Events::level_up(Player& player) {
    Input player_input;
    ClassId player_choice;

    while (true) // выход посредством return (из-за ввода)
    {
        Console::clear();
        Console::print("LEVEL UP\n");
        Info::level_up_info(player);

        Console::print("");
        Console::print("Which class bonus would you choose?");
        player_input.getInput("123");

        if (!player_input.isValid()) { // Неккоректный ввод, continue
            Console::print("Invalid input");
            Console::enter();
            continue;
        }

        // Ввод корректен, осталось его обработать
        switch (player_input.getValue())
        {
        case '1':
            player_choice = ClassId::ROGUE;
            break;
        
        case '2':
            player_choice = ClassId::WARRIOR;
            break;
        case '3':
            player_choice = ClassId::BARBARIAN;
            break;
        }
        player.level_up(player_choice);
        Console::enter();
        return; // Точка выхода из функции
    } // end while
} // end function

void game::Events::weapon_swap(Player& player, WeaponId reward) {
    Input player_input;

    while (true) // выход посредством return (из-за ввода)
    {
        Console::clear();
        Console::print("WEAPON SWAP\n");

        Console::print("Enemy drop:");
        Info::weapon_info(reward);

        Console::print("Your weapon:");
        Info::weapon_info(player.weapon);

        Console::print("");
        Console::print("Do you want to change your weapon?");
        Console::print("[1] Yes");
        Console::print("[2] No");
        player_input.getInput("12");

        if (!player_input.isValid()) { // Вывод некорректен, continue
            Console::print("Invalid input");
            Console::enter();
            continue;
        }

        // Ввод успешен, осталось его обработать
        if (player_input.getValue() == '1') {
            player.weapon = reward;
            Console::print("You have changed your weapon");
        }
        Console::enter();
        return; // Точка выхода из функции
    } // end while
} // end function