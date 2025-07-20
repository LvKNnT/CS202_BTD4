#ifndef RESOURCE_H
#define RESOURCE_H

#include <memory>

class Resource {
public:
    int cash;
    int lives;
    int round;
    int maxRound;

    Resource(int initialCash = 0, int initialLives = 0, int initialRound = 0, int maxRounds = 0)
        : cash(initialCash), lives(initialLives), round(initialRound), maxRound(maxRounds) {};
    Resource(const Resource& other)
        : cash(other.cash), lives(other.lives), round(other.round) {}
    ~Resource() = default;

    Resource& operator=(const Resource& other) {
        if (this != &other) {
            cash = other.cash;
            lives = other.lives;
            round = other.round;
        }
        return *this;
    }
};

#endif // RESOURCE_H 