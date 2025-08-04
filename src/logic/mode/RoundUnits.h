#ifndef ROUND_UNITS_H
#define ROUND_UNITS_H

#include "../enemy/EnemyUnits.h"

class EnemyWave {
public:
    BloonType type; // Type of the bloon
    BloonProperties properties; // Properties of the bloon, such as fortified, camo, regrow
    int count; // Number of bloons of this type in the wave
    float startTime; // Time when the wave starts
    float endTime; // Time when the wave ends
    int bloonCount = 0; // Count of bloons spawned in this wave

    EnemyWave(BloonType type = {}, BloonProperties properties = {}, int count = 0, float startTime = 0.0f, float endTime = 0.0f, int bloonCount = 0)
        : type(type), properties(properties), count(count), startTime(startTime), endTime(endTime), bloonCount(bloonCount) {}
};

#endif // ROUND_UNITS_H