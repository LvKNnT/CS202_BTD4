#ifndef APOPALYPSE_MODE_H
#define APOPALYPSE_MODE_H

#include "../Mode.h"
#include <vector>

class ApopalypseModePlayer : public Mode {
private:
    Round currentRound;

public:
    ApopalypseModePlayer() = default;
    ApopalypseModePlayer(const ApopalypseModePlayer& other) = default;
    ApopalypseModePlayer& operator=(const ApopalypseModePlayer& other) = default;

    std::unique_ptr<Mode> clone() const override;

    void playRound(const RoundManager& roundManager, int roundNumber) override;
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies(const RoundManager& roundManager) override;
    int getRoundReward() override;

    bool setAutoPlay(bool autoPlay) override;
    bool canPlayNextRound(bool isClear) const override;
};

#endif // APOPALYPSE_MODE_H