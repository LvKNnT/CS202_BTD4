#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"
#include "../../logic/tower/TowerUnits.h"

class GameState : public State {
public:
    GameState();
    void draw() const override;
    void update(Event::Type event) override;
    void handleInput() override;

private:
    int curPriority = 0; // testing
    static const int maxTowerTypes = 12;
    int curTowerType;
    std::shared_ptr<PanelElement> chooseTowerButton[maxTowerTypes];
    std::shared_ptr<PanelElement> towerCost[maxTowerTypes];
    std::shared_ptr<PanelElement> towerInfoButton[maxTowerTypes];
    std::shared_ptr<PanelElement> nextTowerButton;
    std::shared_ptr<PanelElement> previousTowerButton;
    std::shared_ptr<PanelElement> movableTowerTexture;

    // Text

    std::shared_ptr<PanelElement> round;
    std::shared_ptr<PanelElement> mode;
    std::shared_ptr<PanelElement> cash;
    std::shared_ptr<PanelElement> lives;
    std::shared_ptr<PanelElement> maxRound;
    
    // Tower Detail
    // std::unique_ptr<Panel> towerDetailPanel;
    // std::shared_ptr<PanelElement> towerPop;
    // std::shared_ptr<PanelElement> towerDetail;
    // std::shared_ptr<PanelElement> towerCost;
    
    // Tower 
    std::unique_ptr<Panel> towerPanel;
    
    std::shared_ptr<PanelElement> towerName;
    std::shared_ptr<PanelElement> priorityTitle;
    std::shared_ptr<PanelElement> towerTex;
    std::shared_ptr<PanelElement> upgradeTex[3];
    std::shared_ptr<PanelElement> upgradeTitle[3];
    std::shared_ptr<PanelElement> upgradeInfoButton[3];
    std::shared_ptr<PanelElement> nextUpgradeCost[3];
    std::shared_ptr<PanelElement> nextUpgradeButton[3];
    std::shared_ptr<PanelElement> nextUpgradeTitle[3];
    std::shared_ptr<PanelElement> nextUpgradeInfoButton[3];

    std::shared_ptr<PanelElement> sellButton;
    std::shared_ptr<PanelElement> sellCost;
    std::shared_ptr<PanelElement> infoTextbox;

    // Functions
    void setPriority(TargetPriority type);
};

#endif // GAME_STATE_H