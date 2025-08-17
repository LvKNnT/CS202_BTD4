#ifndef REVERSE_MODE_H
#define REVERSE_MODE_H

#include "../Mode.h"

class ReverseModePlayer : public Mode {
private:
    Round currentRound;    

public:
    ReverseModePlayer() = default;
    ReverseModePlayer(const ReverseModePlayer& other) = default;
    ReverseModePlayer& operator=(const ReverseModePlayer& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool canPlayNextRound(bool isClear) const override;
};

#endif // REVERSE_MODE_H