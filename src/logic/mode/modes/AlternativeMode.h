#ifndef ALTERNATIVE_MODE_H
#define ALTERNATIVE_MODE_H

#include "../Mode.h"

class AlternativeMode : public Mode {
private:
    Round currentRound;    

public:
    AlternativeMode() = default;
    AlternativeMode(const AlternativeMode& other) = default;
    AlternativeMode& operator=(const AlternativeMode& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool setAutoPlay(bool autoPlay) override;
    bool canPlayNextRound(bool isClear) const override;
};

#endif // ALTERNATIVE_MODE_H