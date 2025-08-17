#ifndef ICE_MONKEY_H
#define ICE_MONKEY_H

#include "../../Tower.h"

class IceMonkey : public Tower {
public:
    IceMonkey(Vector2 position = {0.0f, 0.0f});
    IceMonkey(const IceMonkey& other);
    ~IceMonkey() override = default;

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
    bool isPlaceable(Point::Type pointType) const override; 

    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
};

#endif // ICE_MONKEY_H