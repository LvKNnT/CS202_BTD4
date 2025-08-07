#ifndef UTILS_H
#define UTILS_H

#include "raylib.h"
#include "Properties.h"

#include <iostream>
#include <random>
#include <chrono>

namespace Utils {
    inline std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    bool isMouseInMap();
    bool isPositionInMap(Vector2 position);
    bool isColorDiffByTolerance(Color a, Color b, float tolerance);
    long long rand(long long l, long long r);
};

#endif // UTILS_H