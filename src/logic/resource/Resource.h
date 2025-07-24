#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>

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
};

#endif // RESOURCE_H 