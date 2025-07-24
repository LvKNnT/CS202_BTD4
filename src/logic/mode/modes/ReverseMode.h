#ifndef REVERSE_MODE_H
#define REVERSE_MODE_H

#include "../Mode.h"

class ReverseMode : public Mode {
private:
    Round currentRound;    

public:
    ReverseMode() = default;
    ReverseMode(const ReverseMode& other) = default;
    ReverseMode& operator=(const ReverseMode& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool setAutoPlay(bool autoPlay) override;
    bool canPlayNextRound(bool isClear) const override;
};

#endif // REVERSE_MODE_H