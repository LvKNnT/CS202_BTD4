#ifndef ROUND_H
#define ROUND_H

#include <vector>
#include "RoundUnits.h"

class Round {
public:
    int extraCash;
    std::vector<EnemyWave> bloonTypes; // Pair of BloonType and the number of bloons of that type in this round

    Round(int extraCash = 0, std::vector<EnemyWave> bloonTypes = {})
        : extraCash(extraCash), bloonTypes(bloonTypes) {};
    Round(const Round& other)
        : extraCash(other.extraCash), bloonTypes(other.bloonTypes) {}
    ~Round() = default;

    Round& operator=(const Round& other) {
        if (this != &other) {
            extraCash = other.extraCash;
            bloonTypes = other.bloonTypes;
        }

        return *this;
    }
};

#endif // ROUND_H