#ifndef NINJAMONKEY_H
#define NINJAMONKEY_H

#include <unordered_map>

#include "../../Tower.h"


class NinjaMonkey : public Tower {
public:
    NinjaMonkey(Vector2 position = {0.0f, 0.0f});
    NinjaMonkey(const NinjaMonkey& other);
    ~NinjaMonkey() override = default;

    std::unique_ptr<Tower> clone() const override;
    
    // Override all methods from Tower
    void loadTexture() override;

    void draw() const override;
    void drawRange() const override; 
    void drawPut() const override;
    void update() override;
    void setRotation(float rotation) override;
    void setModifies(const TowerModifies& modifies) override;
    LogicInfo getInfo() override;

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;

// For Shinobi Tactics upgrade
private:
    const static int MAXShinobiStack = 20;
    int shinobiStack = 0;
    bool hasShinobiTactics = false;
    std::unordered_map<int, bool> appliedShinobiTactics;

public:
    void addShinobiStatck();
    void delShinobiStack();
    void activateShinobiTactics();
    bool getHasShinobiTactics();
    bool addApplideShinobiTactics(int towerId);
};

#endif // NINJAMONKEY_H