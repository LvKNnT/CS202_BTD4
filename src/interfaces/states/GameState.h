#ifndef GAME_STATE_H
#define GAME_STATE_H

#include<vector>
#include <string>

#include "State.h"
#include "../../logic/tower/TowerUnits.h"
#include "../../logic/LogicInfo.h"

class GameState : public State, public ISubject {
public:
    GameState();
    void draw() const override;
    void update(Event::Type event) override;
    void handleInput() override;    

    // ISubject
    void attach(std::shared_ptr<IObserver> observer) override;
    void detach(std::shared_ptr<IObserver> observer) override;
    void notify(Event::Type event) override;
private:
    TowerType clickedTowerType = TowerType::None;
    static const int maxTowerTypes = 12;
    int curTowerType;
    std::shared_ptr<PanelElement> chooseTowerButton[maxTowerTypes];
    std::shared_ptr<PanelElement> towerCost[maxTowerTypes];
    std::shared_ptr<PanelElement> towerInfoButton[maxTowerTypes];
    std::shared_ptr<PanelElement> nextTowerButton;
    std::shared_ptr<PanelElement> previousTowerButton;

    // Text
    std::shared_ptr<PanelElement> round;
    std::shared_ptr<PanelElement> mode;
    std::shared_ptr<PanelElement> cash;
    std::shared_ptr<PanelElement> lives;
    std::shared_ptr<PanelElement> maxRound;
    
    // Round info
    std::unique_ptr<Panel> roundPanel;
    std::shared_ptr<PanelElement> roundInfo;
    std::shared_ptr<PanelElement> roundTitle;
    // Tower 
    std::unique_ptr<Panel> towerPanel;
    
    std::shared_ptr<PanelElement> towerName;
    std::shared_ptr<PanelElement> towerPopCount;
    std::shared_ptr<PanelElement> priorityTitle;
    std::shared_ptr<PanelElement> towerTex;
    std::shared_ptr<PanelElement> upgradeContainer[3];
    std::shared_ptr<PanelElement> nextUpgradeContainer[3];
    std::shared_ptr<PanelElement> redNextUpgradeContainer[3];
    std::shared_ptr<PanelElement> upgradeButton[3];
    std::shared_ptr<PanelElement> upgradeTitle[3];
    std::shared_ptr<PanelElement> upgradeInfoButton[3];
    std::shared_ptr<PanelElement> nextUpgradeCost[3];
    std::shared_ptr<PanelElement> nextUpgradeButton[3];
    std::shared_ptr<PanelElement> nextUpgradeTitle[3];
    std::shared_ptr<PanelElement> nextUpgradeInfoButton[3];

    std::shared_ptr<PanelElement> sellPrice;
    std::shared_ptr<PanelElement> skillButton;
    std::shared_ptr<PanelElement> skillInfoTextbox;
    std::shared_ptr<PanelElement> buttonInfoTextbox;
    std::shared_ptr<PanelElement> upgradeInfoTextbox;

    // Functions
    void pickTower();
    void unpickTower();
    TowerType getTowerType(int i) const;
    void gameOver();
};

#endif // GAME_STATE_H