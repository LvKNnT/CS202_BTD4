#ifndef BAD_H
#define BAD_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Bad : public Enemy {
public:
    Bad(Vector2 position = {0.0f, 0.0f});
    ~Bad() override;

    // Override all methods from Enemy
    void loadTexture() override;

    bool hit(int damage) override;
    void draw() const override;
    void die() override; 
    std::unique_ptr<Enemy> clone() const override;

    // Override all methods from GameObject
    Rectangle getBoundingBox() const override;
    bool isActive() const override;
    void setActive(bool active) override;
    void setDebuff(const BloonDebuff& normalDebuff, const BloonDebuff& moabDebuff) override;
    void setRotation(float rotation) override;
    void setModifies(const EnemyModifies& modifies) override;
    void setProperties(const BloonProperties& properties) override;

private:

};
#endif // BAD_H
