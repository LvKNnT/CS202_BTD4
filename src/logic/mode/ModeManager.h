#ifndef MODE_MANAGER_H
#define MODE_MANAGER_H

#include "ModeSpawner.h"
#include "RoundManager.h"

class ModeManager {
    friend class LogicManager;

public:
    ModeManager() = default;
    ~ModeManager() = default;

    // Initialize the mode manager
    void setMode(ModeType modeType);

    // Methods of current mode
    void playRound(int roundNumber);
    std::vector<std::pair<BloonType, BloonProperties>> getEnemies();
    int getRoundReward();
    bool setAutoPlay(bool autoPlay);
    bool canPlayNextRound(bool isClear) const;

    // save/load
    void save(const std::string& filePath) const;
    void load(const std::string& filePath);
    
private:
    ModeSpawner modeSpawner; 
    ModeType currentModeType;
    std::unique_ptr<Mode> currentMode;
    std::unique_ptr<RoundManager> roundManager = std::make_unique<RoundManager>();
};

#endif // MODE_MANAGER_H