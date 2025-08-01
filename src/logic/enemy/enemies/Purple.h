#ifndef PURPLE_H
#define PURPLE_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Purple : public Enemy {
public:
    Purple(Vector2 position = {0.0f, 0.0f});
    std::unique_ptr<Enemy> clone() const override;
    ~Purple() override = default;

    // Override all methods from Enemy
    void loadTexture() override;
    
    bool hit(int damage) override;
    void draw() const override;
    void die() override;

    // Override all methods from GameObject
    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;

    // Purple bloon does not need rotation, but we need to implement it
    void setRotation(float rotation) override;
    void setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) override; // Purple bloon has no special debuff handling
    void setModifies(const EnemyModifies& modifies) override;
    void setProperties(const BloonProperties& properties) override;

private:

};

#endif // PURPLE_H