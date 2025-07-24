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

    EnemyWave(BloonType type = {}, BloonProperties properties = {}, int count = 0, float startTime = 0.0f, float endTime = 0.0f)
        : type(type), properties(properties), count(count), startTime(startTime), endTime(endTime) {}
};

#endif // ROUND_UNITS_H