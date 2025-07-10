#ifndef ZEBRA_H
#define ZEBRA_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Zebra : public Enemy {
public:
    Zebra(Vector2 position = {0.0f, 0.0f});
    std::unique_ptr<Enemy> clone() const override;
    ~Zebra() override = default;

    // Override all methods from Enemy
    void loadTexture() override;
    
    bool hit(int damage) override;
    void draw() const override;
    void die() override;

    // Override all methods from GameObject
    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;

    // Zebra bloon does not need rotation, but we need to implement it
    void setRotation(float rotation) override;
    void setModifies(const EnemyModifies& modifies) override;

private:

};

#endif // ZEBRA_H