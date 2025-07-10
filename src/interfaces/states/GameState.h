#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "State.h"

class GameState : public State {
public:
    GameState();
    void draw() const override;
    void update(Event::Type event) override;
    void handleInput() override;

private:
    static const int maxTowerTypes = 12;
    int curTowerType;
    std::shared_ptr<PanelElement> chooseTowerButton[maxTowerTypes];
    std::shared_ptr<PanelElement> nextTowerButton;
    std::shared_ptr<PanelElement> previousTowerButton;
    std::shared_ptr<PanelElement> movableTowerTexture;

    // Text
    std::shared_ptr<PanelElement> towerName;
    std::shared_ptr<PanelElement> towerDetail;
    std::shared_ptr<PanelElement> towerCost;
    std::shared_ptr<PanelElement> cantAffordTower;
    std::shared_ptr<PanelElement> round;
    std::shared_ptr<PanelElement> mode;
    std::shared_ptr<PanelElement> hp;
    std::shared_ptr<PanelElement> cash;
};

#endif // GAME_STATE_H