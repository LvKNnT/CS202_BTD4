#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>
#include "../LogicInfo.h"

class Resource {
public:
    int cash;
    int lives;
    int currentRound;
    int initialRound;
    int maxRound;

    Resource(int initialCash = 0, int initialLives = 0, int currentRound = 0, int initialRound = 0, int maxRounds = 0)
        : cash(initialCash), lives(initialLives), currentRound(currentRound), initialRound(initialRound), maxRound(maxRounds) {};
    Resource(const Resource& other)
        : cash(other.cash), lives(other.lives), currentRound(other.currentRound), initialRound(other.initialRound), maxRound(other.maxRound) {}
    ~Resource() = default;

    Resource& operator=(const Resource& other) {
        if (this != &other) {
            cash = other.cash;
            lives = other.lives;
            currentRound = other.currentRound;
            initialRound = other.initialRound;
            maxRound = other.maxRound;
        }
        return *this;
    }
    
    LogicInfo getInfo() const {
        LogicInfo info;

        info["cash"] = std::to_string(cash);
        info["lives"] = std::to_string(lives);
        info["currentRound"] = std::to_string(currentRound);
        info["initialRound"] = std::to_string(initialRound);
        info["maxRound"] = std::to_string(maxRound);

        return info;
    }
};

#endif // RESOURCE_H 