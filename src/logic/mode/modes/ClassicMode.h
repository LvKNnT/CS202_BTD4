#ifndef CLASSIC_MODE_H
#define CLASSIC_MODE_H

#include "../Mode.h"

class ClassicMode : public Mode {
private:
    Round currentRound;    

public:
    ClassicMode() = default;
    ClassicMode(const ClassicMode& other) = default;
    ClassicMode& operator=(const ClassicMode& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool setAutoPlay(bool autoPlay) override;
    bool canPlayNextRound(bool isClear) const override;
};

#endif // CLASSIC_MODE_H