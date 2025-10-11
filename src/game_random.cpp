#include "game_random.hpp"

#include <random>

int game::Random::range(int start, int end) {
    std::uniform_int_distribution<> dist(start, end);
    int result = dist(gen);
    return result;
}
