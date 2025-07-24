#ifndef ZOMG_H
#define ZOMG_H

#include "../../../core/Game.h"
#include "../Enemy.h"

class Zomg : public Enemy {
public:
    Zomg(Vector2 position = {0.0f, 0.0f});
    ~Zomg() override;

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
    void setRotation(float rotation) override;
    void setModifies(const EnemyModifies& modifies) override;
    void setProperties(const BloonProperties& properties) override;

private:

};
#endif // ZOMG_H
