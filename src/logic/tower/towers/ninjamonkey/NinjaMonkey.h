#ifndef NINJAMONKEY_H
#define NINJAMONKEY_H

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
};

#endif // NINJAMONKEY_H