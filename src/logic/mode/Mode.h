#ifndef MODE_H
#define MODE_H

// This is for each game mode handling their enemy pattern

#include <memory>
#include <vector>
#include "../enemy/Enemy.h"
#include "Round.h"
#include "RoundManager.h"

class Mode {
    friend class LogicManager;
    friend class ModeSpawner;

public:
    Mode() = default;
    virtual std::unique_ptr<Mode> clone() const = 0;
    virtual ~Mode() = default;

    virtual void playRound(const RoundManager& roundManager, int roundNumber) = 0;
    virtual std::vector<std::pair<BloonType, BloonProperties> > getEnemies(const RoundManager& roundManager) = 0;
    virtual int getRoundReward() = 0;

    virtual bool setAutoPlay(bool autoPlay) = 0;
    virtual bool canPlayNextRound(bool isClear) const = 0;

protected:
    float timer = 0.0f;
    int currentRoundNumber = 0;
};

#endif // MODE_H