#ifndef RED_H
#define RED_H

#include "../../core/Game.h"
#include "Enemy.h"

class Red : public Enemy {
public:
    Red(Vector2 position);
    ~Red() override;

    // Override all methods from Enemy
    bool hit(int damage) override;
    void draw() const override;
    void die() override; 
    std::unique_ptr<Enemy> clone() const override;

    // Override all methods from GameObject
    Rectangle getBoundingBox(float& x, float& y, float& width, float& height) const override;
    bool isActive() const override;
    void setActive(bool active) override;

private:

};

#endif // RED_H