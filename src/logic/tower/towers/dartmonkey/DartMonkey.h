#ifndef DARTMONKEY_H
#define DARTMONKEY_H

#include "../../Tower.h"

class DartMonkey : public Tower {
public:
    DartMonkey(Vector2 position = {0.0f, 0.0f});
    DartMonkey(const DartMonkey& other);
    ~DartMonkey() override = default;

    std::unique_ptr<Tower> clone() const override;
    
    // Override all methods from Tower
    void loadTexture() override;

    void draw() const override;
    void update() override;
    void setRotation(float rotation) override;
    void setModifies(const TowerModifies& modifies) override;
    void upgrade(const UpgradeUnits& upgradeUnits, int& currentCash) override;
    LogicInfo getInfo() override;

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
};

#endif // DARTMONKEY_H