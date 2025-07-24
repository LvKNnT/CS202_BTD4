#ifndef BLUE_H
#define BLUE_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Blue : public Enemy {
public:
    Blue(Vector2 position = {0.0f, 0.0f});
    std::unique_ptr<Enemy> clone() const override;
    ~Blue() override = default;

    // Override all methods from Enemy
    void loadTexture() override;
    
    bool hit(int damage) override;
    void draw() const override;
    void die() override;

    // Override all methods from GameObject
    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;

    // Blue bloon does not need rotation, but we need to implement it
    void setRotation(float rotation) override;
    void setModifies(const EnemyModifies& modifies) override;
    void setProperties(const BloonProperties& properties) override;

private:

};

#endif // BLUE_H