#ifndef CLASSIC_MODE_H
#define CLASSIC_MODE_H

#include "../Mode.h"

class ClassicModePlayer : public Mode {
private:
    Round currentRound;    

public:
    ClassicModePlayer() = default;
    ClassicModePlayer(const ClassicModePlayer& other) = default;
    ClassicModePlayer& operator=(const ClassicModePlayer& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool canPlayNextRound(bool isClear) const override;
};

#endif // CLASSIC_MODE_H